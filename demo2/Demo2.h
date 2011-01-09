#pragma once

#include "Body.h"
#include "OBoy/Environment.h"
#include "OBoy/Font.h"
#include "OBoy/Game.h"
#include "OBoy/Graphics.h"
#include "OBoy/KeyboardListener.h"
#include "oboylib/OBoyUtil.h"
#include "oboylib/Vector2.h"
#include "Explosion.h"

class Demo2: public oboy::Game, public oboy::KeyboardListener
{
public:

	Demo2();
	virtual ~Demo2();

	// singleton:
	static Demo2 *instance();
	static void destroy();

	// implementation of Game:
	virtual void init();
	virtual void load();
	virtual void loadComplete();
	virtual void update(float dt);
	virtual void draw(oboy::Graphics *g);

	// implementation of KeyboardListener:
	virtual void keyUp(wchar_t unicode, oboy::Keyboard::Key key, oboy::Keyboard::Modifiers mods);
	virtual void keyDown(wchar_t unicode, oboy::Keyboard::Key key, oboy::Keyboard::Modifiers mods);

private:

	void death();
	void gameOver();
	void newGame();
	void nextLevel();

private:

	static Demo2 *gInstance;

	Body *mShip;
	std::vector<Body*> mAsteroids;
	std::vector<Body*> mBullets;
	std::vector<Explosion*> mExplosions;

	bool mThrust;
	bool mLeft;
	bool mRight;
	bool mGunArmed;

	int mLevel;
	int mLives;
	bool mLoadComplete;
	oboy::Image *mShipImage;
	oboy::Image *mThrustImage;
	oboy::Sound *mBoomSound;
	oboy::Sound *mFireSound;
	oboy::Sound *mThrustSound;
	oboy::Font *mFont;
	int mScore;
	bool mGameOver;
	float mLastRespawn;
	float mTimeOfDeath;
	int mDrawCount;
};
