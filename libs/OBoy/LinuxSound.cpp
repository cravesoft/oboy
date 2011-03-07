#include "LinuxSound.h"

#include <assert.h>
#include "Environment.h"
#include "ResourceLoader.h"
#include "LinuxSoundPlayer.h"

using namespace OBoy;

#include "OBoyLib/CrtDbgNew.h"

LinuxSound::LinuxSound(ResourceLoader *loader, const std::string &path) : Sound(loader,path)
{
	mISoundSource = NULL;
	mISound = NULL;
	mFadeStartTime = -1;
	mFadeDuration = -1;
	mFadeVolume0 = -1;
	mFadeVolume1 = -1;
}

LinuxSound::~LinuxSound()
{
}

bool LinuxSound::init(bool includeSounds)
{
	if (includeSounds)
	{
		return mLoader->load(this);
	}
	else
	{
		return true;
	}
}

void LinuxSound::destroy(bool includeSounds)
{
	if (includeSounds)
	{
		SoundPlayer *sp = Environment::instance()->getSoundPlayer();
		if (mISound!=NULL)
		{
			sp->stopSound(this);			
		}
		if (mISoundSource!=NULL)
		{
			LinuxSoundPlayer *wsp = dynamic_cast<LinuxSoundPlayer*>(sp);
			irrklang::ISoundEngine *eng = wsp->getEngine();
			if (eng!=NULL)
			{
				eng->removeSoundSource(mISoundSource);
			}
		}
//		printf("LinuxSound::destroy() - setting isound to NULL (linuxsound=%p)\n",this);
		mISound = NULL;
		mISoundSource = NULL;
	}
}

void LinuxSound::reload()
{
	// do nothing, we don't want to reload sounds
}

void LinuxSound::setISoundSource(irrklang::ISoundSource *iss)
{
	assert(mISoundSource==NULL);
	mISoundSource = iss;
}

irrklang::ISoundSource *LinuxSound::getISoundSource()
{
	return mISoundSource;
}

void LinuxSound::setISound(irrklang::ISound *isound)
{
//	printf("LinuxSound::setISound() - linuxsound=%p isound=%p\n",this,isound);
	mISound = isound;
}

irrklang::ISound *LinuxSound::getISound()
{
	return mISound;
}

void LinuxSound::fade(float volume0, float volume1, float startTime, float duration)
{
	mFadeStartTime = startTime;
	mFadeDuration = duration;
	mFadeVolume0 = volume0;
	mFadeVolume1 = volume1;
}


