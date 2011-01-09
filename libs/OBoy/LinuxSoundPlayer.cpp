#include "LinuxSoundPlayer.h"

#include <algorithm>
#include <assert.h>
#include "Environment.h"
#include "irrKlang.h"
#include "ResourceManager.h"
#include "LinuxSound.h"

using namespace oboy;

#include "oboylib/CrtDbgNew.h"

LinuxSoundPlayer::LinuxSoundPlayer()
{
	mSoundEngine = irrklang::createIrrKlangDevice();
//	assert(mSoundEngine!=NULL);
}

LinuxSoundPlayer::~LinuxSoundPlayer()
{
	if (mSoundEngine==NULL)
	{
		return;
	}
	mSoundEngine->drop();
}

void LinuxSoundPlayer::playSound(Sound *sound, float volume, bool loop)
{
	if (mSoundEngine==NULL)
	{
		return;
	}
	if (sound==NULL)
	{
		assert(false);
		return;
	}

//	envDebugLog("[LinuxSoundPlayer] playSound(%p) volume=%0.2d loop=%d\n",sound,volume,loop);
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);
	irrklang::ISoundSource *src = snd->getISoundSource();

	if (src==NULL)
	{
		assert(false);
		return;
	}

	// play the sound:
	irrklang::ISound *iSound = mSoundEngine->play2D(
		src, // sound source
		loop, // loop sound
		true); // start paused
	assert(iSound!=NULL);

	irrklang::ISound *prev = snd->getISound();
	if (prev!=NULL && !prev->isFinished())
	{
		prev->stop();
	}
	snd->setISound(iSound);

	// set volume for this sound:
	iSound->setVolume(volume);

	// play it:
	iSound->setIsPaused(false);
}

void LinuxSoundPlayer::playSoundChain(std::vector<Sound*> &sounds, bool loopLastSound)
{
	// we're assuming there's more than one sound here:
	assert(sounds.size()>1);

	// create and remember the chain:
	SoundChain *chain = new SoundChain();
	chain->loopLastSound = loopLastSound;
	chain->sounds = sounds;
	mSoundChains.push_back(chain);

	// start playing the first sound:
	playSound(chain->sounds[0]);
}

void LinuxSoundPlayer::stopSound(Sound *sound)
{
	if (!isPlaying(sound))
	{
		return;
	}

	// stop playing it:
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);
	irrklang::ISound *isound = snd->getISound();
	if (isound!=NULL)
	{
//		envDebugLog("##### stopping sound: linuxsound=%p isound=%p\n",snd,snd->getISound());
		isound->stop();
		isound->drop();
		snd->setISound(NULL);
	}
}

void LinuxSoundPlayer::stopAllSounds()
{
	if (mSoundEngine==NULL)
	{
		return;
	}
	mSoundEngine->stopAllSounds();
}

void LinuxSoundPlayer::setVolume(Sound *sound, float volume)
{
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);
	if (snd!=NULL)
	{
		irrklang::ISound *isnd = snd->getISound();
		if (isnd!=NULL)
		{
			isnd->setVolume(volume);
		}
	}
}

void LinuxSoundPlayer::fadeIn(Sound *sound, float duration, bool loop)
{
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);
	float now = Environment::instance()->getTime();
	snd->fade(0,1,now,duration);
	playSound(snd,0,loop);
	mFadingSounds.push_back(snd);
//	envDebugLog("##### fading sound IN: %x (%0.2f ms)\n",snd->getHandle(),duration*1000);
}

void LinuxSoundPlayer::fadeOut(Sound *sound, float duration)
{
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);
//	envDebugLog("##### fading sound OUT: sound=%p isound=%p (%0.2f ms)\n",snd,snd->getISound(),duration*1000);
	irrklang::ISound *isnd = snd->getISound();
	if (isnd!=NULL && !isnd->isFinished())
	{
		float now = Environment::instance()->getTime();
		snd->fade(isnd->getVolume(),0,now,duration);
		mFadingSounds.push_back(snd);
	}
}

void LinuxSoundPlayer::tick()
{
	// update sound engine:
	if (mSoundEngine!=NULL)
	{
		mSoundEngine->update();
	}

	// iterate over all sound chains:
	int numChains = (int)mSoundChains.size();
	for (int i=numChains-1 ; i>=0 ; i--)
	{
		// get the chain:
		SoundChain *chain = mSoundChains[i];

		// if the first sound in the chain is done playing:
		if (!isPlaying(chain->sounds[0]))
		{
			// remove it:
			chain->sounds.erase(chain->sounds.begin());

			// if there are no more sounds in this chain:
			if (chain->sounds.size()==0)
			{
				// get rid of it:
				mSoundChains.erase(mSoundChains.begin()+i);
				delete chain;
			}
			else
			{
				// get the next sound:
				Sound *sound = chain->sounds[0];

				// if this is the last sound and we should loop it:
				if (chain->sounds.size()==1 && chain->loopLastSound)
				{
					// loop the sound:
					playSound(sound,1,true);

					// get rid of this sound chain:
					mSoundChains.erase(mSoundChains.begin()+i);
					delete chain;
				}
				else
				{
					// play the next sound:
					playSound(sound);
				}
			}
		}
	}

	// iterate over all fading sounds:
	int numFades = (int)mFadingSounds.size();
	for (int i=numFades-1 ; i>=0 ; i--)
	{
		LinuxSound *snd = mFadingSounds[i];

		float currentTime = Environment::instance()->getTime();
		float fadeStartTime = snd->getFadeStartTime();
		float fadeDuration = snd->getFadeDuration();
		float v0 = snd->getFadeVolume0();
		float v1 = snd->getFadeVolume1();
		float progress = (currentTime - fadeStartTime) / fadeDuration;
		// if we're still fading:
		if (progress<1)
		{
			// fade:
			float volume = v0 + (v1-v0) * progress;
			if (snd->getISound()!=NULL)
			{
				snd->getISound()->setVolume(volume);
			}
		}
		else
		{
			// we're done fading this sound:
			mFadingSounds.erase(mFadingSounds.begin()+i);

			// set final volume:
			if (snd->getISound()!=NULL)
			{
				snd->getISound()->setVolume(v1);
			}

			// if we're fading out:
			if (v1==0)
			{
				// stop the sound:
				stopSound(snd);
			}
		}
	}
}

bool LinuxSoundPlayer::isPlaying(Sound *sound)
{
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);
	if (snd->getISound()==NULL)
	{
		return false;
	}
	return !snd->getISound()->isFinished();
}

void LinuxSoundPlayer::setMasterVolume(float volume)
{
	if (mSoundEngine==NULL)
	{
		return;
	}
	mSoundEngine->setSoundVolume(volume);
}

float LinuxSoundPlayer::getMasterVolume()
{
	if (mSoundEngine==NULL)
	{
		return 0.0f;
	}
	return mSoundEngine->getSoundVolume();
}
