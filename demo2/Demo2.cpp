#include "Demo2.h"

#include <assert.h>
#include "Body.h"
#include "OBoy/Environment.h"
#include "OBoy/GamePad.h"
#include "OBoy/Graphics.h"
#include "OBoy/Mouse.h"
#include "OBoy/ResourceManager.h"
#include "OBoy/SoundPlayer.h"
#include <string>

#define SHIP_ROT_SPEED 200.0f
#define SHIP_ACCELERATION 30.0f
#define SHIP_MAX_SPEED 250.0f
#define SHIP_DAMPENING_FACTOR 1.0f
#define BULLET_SPEED 400.0f
#define MIN_ASTEROIDS 4
#define INVULNERABILITY_PERIOD 2.5f
#define RESPAWN_DELAY 1.0f

Demo2 *Demo2::gInstance = NULL;

Demo2::Demo2()
{
	mShip = NULL;
	mThrust = mLeft = mRight = false;
	mGunArmed = true;
	mLevel = 0;
	mLoadComplete = false;
	mLives = 3;
	mScore = 0;
	mGameOver = false;
	mDrawCount = 0;
	mLastRespawn = mTimeOfDeath = 0;
}

Demo2::~Demo2()
{
	// stop listening to the keyboard:
	OBoy::Environment::instance()->getKeyboard(0)->removeListener(this);
}

Demo2 *Demo2::instance()
{
	if (gInstance==NULL)
	{
		gInstance = new Demo2();
	}

	return gInstance;
}

void Demo2::destroy()
{
	// destroy the singleton:
	assert(gInstance!=NULL);
	delete gInstance;
	gInstance = NULL;
}

void Demo2::init()
{
}

void Demo2::load()
{
	// load the common resource group:
	OBoy::ResourceManager *rm = OBoy::Environment::instance()->getResourceManager();
	rm->parseResourceFile("res/resources.xml",NULL);
	rm->loadResourceGroup("common");
}

void Demo2::loadComplete()
{
	// start listening to the keyboard:
	OBoy::Environment::instance()->getKeyboard(0)->addListener(this);

	// set the load complete flag (this will trigger 
	// the start of the game in the update method):
	mLoadComplete = true;

	// fetch whatever resources we need:
	OBoy::ResourceManager *rm = OBoy::Environment::instance()->getResourceManager();
	mShipImage = rm->getImage("IMAGE_SHIP");
	mThrustImage = rm->getImage("IMAGE_THRUST");
	mFont = rm->getFont("FONT_MAIN");
	mBoomSound = rm->getSound("SOUND_BOOM");
	mFireSound = rm->getSound("SOUND_FIRE");
	mThrustSound = rm->getSound("SOUND_THRUST");
}

void Demo2::nextLevel()
{
	// increment level:
	mLevel++;

	// destroy ship if necessary:
	if (mShip!=NULL)
	{
		delete mShip;
	}

	// create new ship:
	mShip = new Body(SHIP);
	mLastRespawn = OBoy::Environment::instance()->getTime();

	// put ship in center of screen
	// create some asteroids:
	for (int i=0 ; i<MIN_ASTEROIDS+mLevel-1 ; i++)
	{
		mAsteroids.push_back(new Body(BIG_ASTEROID));
	}

	// destroy all bullets:
	while (mBullets.size()>0)
	{
		delete *(mBullets.begin());
		mBullets.erase(mBullets.begin());
	}
}

void Demo2::update(float dt)
{
	OBoy::Graphics *g = OBoy::Environment::instance()->getGraphics();
	float w = (float)g->getWidth();
	float h = (float)g->getHeight();

	if (mShip!=NULL)
	{
		// tick the ship:
		mShip->update(dt);

		// turn the ship:
		if (mLeft && !mRight)
		{
			mShip->mRotVel = SHIP_ROT_SPEED;
		}
		else if (mRight && !mLeft)
		{
			mShip->mRotVel = -SHIP_ROT_SPEED;
		}
		else
		{
			mShip->mRotVel = 0;
		}

		// accelerate:
		if (mThrust)
		{
			mShip->mVel += rotate(OBoyLib::Vector2(0,-SHIP_ACCELERATION), -deg2rad(mShip->mRot));
		}

		// cap velocity:
		if (mShip->mVel.magnitude()>SHIP_MAX_SPEED)
		{
			mShip->mVel = mShip->mVel.normalize() * SHIP_MAX_SPEED;
		}

		// dampen ship velocity:
		mShip->mVel *= (1-SHIP_DAMPENING_FACTOR*dt);
	}
	else if (!mGameOver && OBoy::Environment::instance()->getTime() > mTimeOfDeath + RESPAWN_DELAY)
	{
		// respawn:
		mShip = new Body(SHIP);
		mLastRespawn = OBoy::Environment::instance()->getTime();

		// if the thruster is on, play the sound:
		if (mThrust)
		{
			OBoy::Environment::instance()->getSoundPlayer()->playSound(mThrustSound);
		}
	}

	// tick the asteroids:
	for (int i=(int)mAsteroids.size()-1 ; i>=0 ; i--)
	{
		mAsteroids[i]->update(dt);

		// see if this asteroid collides with any bullets:
		for (int j=(int)mBullets.size()-1 ; j>=0 ; j--)
		{
			if (mAsteroids[i]->collidesWith(mBullets[j]))
			{
				// if this is a medium or large asteroid, add two new asteroids:
				BodyType type = mAsteroids[i]->mType;
				switch (type)
				{
				case BIG_ASTEROID:
					mAsteroids.push_back(new Body(MEDIUM_ASTEROID, mAsteroids[i]->mPos.x(), mAsteroids[i]->mPos.y()));
					mAsteroids.push_back(new Body(MEDIUM_ASTEROID, mAsteroids[i]->mPos.x(), mAsteroids[i]->mPos.y()));
					break;
				case MEDIUM_ASTEROID:
					mAsteroids.push_back(new Body(SMALL_ASTEROID, mAsteroids[i]->mPos.x(), mAsteroids[i]->mPos.y()));
					mAsteroids.push_back(new Body(SMALL_ASTEROID, mAsteroids[i]->mPos.x(), mAsteroids[i]->mPos.y()));
					break;
				case SMALL_ASTEROID:
					mExplosions.push_back(new Explosion(mAsteroids[i]->mPos.x(), mAsteroids[i]->mPos.y(), mAsteroids[i]->mRadius));
				}

				// mark the hit asteroid for death:
				mAsteroids[i]->mTimeOfDeath = -1;

				// mark the bullet for death:
				mBullets[j]->mTimeOfDeath = -1;

				// play a sound:
				OBoy::Environment::instance()->getSoundPlayer()->playSound(mBoomSound);

				// increment score:
				mScore++;
			}
		}

		// if the asteroid collides with the ship:
		if (mShip!=NULL && mAsteroids[i]->collidesWith(mShip))
		{
			// if we are not in the invulnerability period:
			if (OBoy::Environment::instance()->getTime()-mLastRespawn > INVULNERABILITY_PERIOD)
			{
				death();
			}
		}
	}

	// tick the explosions:
	for (int i=(int)mExplosions.size()-1 ; i>=0 ; i--)
	{
		mExplosions[i]->update(dt);
		if (mExplosions[i]->isOver())
		{
			mExplosions.erase(mExplosions.begin()+i);
		}
	}

	// remove dead asteroids:
	for (int i=(int)mAsteroids.size()-1 ; i>=0 ; i--)
	{
		if (mAsteroids[i]->mTimeOfDeath<0)
		{
			mAsteroids.erase(mAsteroids.begin()+i);
		}
	}

	// tick the bullets:
	float t = OBoy::Environment::instance()->getTime();
	for (int i=(int)mBullets.size()-1 ; i>=0 ; i--)
	{
		mBullets[i]->update(dt);
		if (t > mBullets[i]->mTimeOfDeath)
		{
			mBullets.erase(mBullets.begin()+i);
		}
	}

	// if there are no more asteroids and loading is complete:
	if (mAsteroids.size()==0 && mLoadComplete)
	{
		nextLevel();
	}
}

void Demo2::draw(OBoy::Graphics *g)
{
	mDrawCount++;

	if (mShip!=NULL)
	{
		bool invulnerable = OBoy::Environment::instance()->getTime()-mLastRespawn < INVULNERABILITY_PERIOD;

		// draw the ship:
		if  (!invulnerable || ((int)(OBoy::Environment::instance()->getTime()*1000))%100<50)
		{
			mShip->draw(g);

			// if the thrusters are on:
			if (mThrust)
			{
				// draw the thruster image:
				g->pushTransform();
#ifdef OBOY_PLATFORM_WIN32
					g->rotate(mShip->mRot);
					g->translate(mShip->mPos.x(),mShip->mPos.y());
#else
          g->translate(mShip->mPos.x(),mShip->mPos.y());
					g->rotate(mShip->mRot);
#endif
					g->drawImage(mThrustImage);
				g->popTransform();
				
			}
		}
	}

	// draw the asteroids:
	for (int i=0 ; i<(int)mAsteroids.size() ; i++)
	{
		mAsteroids[i]->draw(g);
	}

	// draw the bullets:
	for (int i=0 ; i<(int)mBullets.size() ; i++)
	{
		mBullets[i]->draw(g);
	}

	// draw the explosions:
	for (int i=0 ; i<(int)mExplosions.size() ; i++)
	{
		mExplosions[i]->draw(g);
	}

	if (mLoadComplete)
	{
		// draw lives:
		g->pushTransform();
		g->translate(50,100);
		for (int i=0 ; i<mLives ; i++)
		{
			g->drawImage(mShipImage);
			g->translate(50,0);
		}
		g->popTransform();

		// draw score:
		OBoy::UString score = OBoy::UString::format("%04d",mScore);
		g->setColorizationEnabled(true);
    g->setColor(OBoyLib::Color(OBoyLib::Color::White));
		g->pushTransform();
		g->translate(50,50);
		mFont->drawString(g,score,0.5f);
		g->popTransform();
		g->setColorizationEnabled(false);
	}

	// if the game is over:
	if (mGameOver)
	{
		OBoy::UString str1("GAME OVER");
		OBoy::UString str2("press ENTER to restart");
		float str2scale = 0.5f;
		float x1 = (OBoy::Environment::screenWidth() - mFont->getStringWidth(str1)) / 2.0f;
		float x2 = (OBoy::Environment::screenWidth() - mFont->getStringWidth(str2)*str2scale) / 2.0f;
		g->pushTransform();
			g->translate(x1, OBoy::Environment::screenHeight()/2.0f - 50.0f);
			mFont->drawString(g,str1);
		g->popTransform();
		g->pushTransform();
			g->translate(x2, OBoy::Environment::screenHeight()/2.0f + 50.0f);
			mFont->drawString(g,str2,str2scale);
		g->popTransform();
	}
}

void Demo2::keyUp(wchar_t unicode, OBoy::Keyboard::Key key, OBoy::Keyboard::Modifiers mods)
{
	switch (key)
	{
	case OBoy::Keyboard::KEY_LEFT:
		mLeft = false;
		break;
	case OBoy::Keyboard::KEY_RIGHT:
		mRight = false;
		break;
	case OBoy::Keyboard::KEY_UP:
		mThrust = false;
		OBoy::Environment::instance()->getSoundPlayer()->stopSound(mThrustSound);
		break;
	}

	// when spacebar is hit:
	if (unicode==' ')
	{
		// gun is armed again:
		mGunArmed = true;
	}
}

void Demo2::keyDown(wchar_t unicode, OBoy::Keyboard::Key key, OBoy::Keyboard::Modifiers mods)
{
	switch (key)
	{
	case OBoy::Keyboard::KEY_ESCAPE:
		// on escape, exit game:
		OBoy::Environment::instance()->stopMainLoop();
		break;
	case OBoy::Keyboard::KEY_LEFT:
		mLeft = true;
		break;
	case OBoy::Keyboard::KEY_RIGHT:
		mRight = true;
		break;
	case OBoy::Keyboard::KEY_UP:
		mThrust = true;
		OBoy::Environment::instance()->getSoundPlayer()->playSound(mThrustSound,1,true);
		break;
	case OBoy::Keyboard::KEY_RETURN:
		if (mGameOver)
		{
			newGame();
		}
	}

	// when spacebar is hit and the gun is armed:
	if (unicode==' ' && mGunArmed && !mGameOver && mShip!=NULL)
	{
		// add a bullet:
		OBoyLib::Vector2 vel = rotate(OBoyLib::Vector2(0.0f,-BULLET_SPEED),-deg2rad(mShip->mRot));
		mBullets.push_back(new Body(BULLET, mShip->mPos.x(), mShip->mPos.y(), vel.x(), vel.y()));

		// make a sound:
		OBoy::Environment::playSound("SOUND_FIRE");

		// gun is no longer armed:
		mGunArmed = false;
	}
}

void Demo2::death()
{
	// create an explosion:
	mExplosions.push_back(new Explosion(mShip->mPos.x(), mShip->mPos.y(), mShip->mRadius));
	mExplosions.push_back(new Explosion(mShip->mPos.x(), mShip->mPos.y(), mShip->mRadius));

	// destroy ship:
	delete mShip;
	mShip = NULL;

	// make sound:
	OBoy::Environment::instance()->getSoundPlayer()->playSound(mBoomSound);

	// stop thruster sound if it's playing:
	OBoy::Environment::instance()->getSoundPlayer()->stopSound(mThrustSound);

	// decrement lives and see if game is over:
	mLives--;
	if (mLives==0)
	{
		gameOver();
	}

	// mark time of death:
	mTimeOfDeath = OBoy::Environment::instance()->getTime();
}

void Demo2::gameOver()
{
	mGameOver = true;
}

void Demo2::newGame()
{
	mScore = 0;
	mLives = 3;
	mLevel = 0;
	mGameOver = false;
	nextLevel();
	while (mAsteroids.size()>0)
	{
		delete *(mAsteroids.begin());
		mAsteroids.erase(mAsteroids.begin());
	}
	while (mExplosions.size()>0)
	{
		delete *(mExplosions.begin());
		mExplosions.erase(mExplosions.begin());
	}
	while (mBullets.size()>0)
	{
		delete *(mBullets.begin());
		mBullets.erase(mBullets.begin());
	}
}