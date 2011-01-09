#pragma once

#include "oboylib/CrtDbgInc.h"

#include "irrKlang.h"
#include <map>
#include "SoundPlayer.h"
#include <string>
#include <vector>

namespace oboy
{
	class LinuxSound;

	struct SoundChain
	{
		std::vector<Sound*> sounds;
		bool loopLastSound;
	};

	class LinuxSoundPlayer : public SoundPlayer
	{
	public:

		LinuxSoundPlayer();
		virtual ~LinuxSoundPlayer();

		inline irrklang::ISoundEngine *getEngine() { return mSoundEngine; }

		// implementation of SoundPlayer:
		virtual void playSound(Sound *sound, float volume=1, bool loop=false);
		virtual void playSoundChain(std::vector<Sound*> &soundss, bool loopLastSound=false);
		virtual void stopSound(Sound *sound);
		virtual void stopAllSounds();
		virtual void setVolume(Sound *sound, float volume);
		virtual void setMasterVolume(float volume);
		virtual float getMasterVolume();
		virtual void fadeIn(Sound *sound, float duration, bool loop);
		virtual void fadeOut(Sound *sound, float duration);
		virtual void tick();
		virtual bool isPlaying(Sound *sound);

	private:

		irrklang::ISoundEngine *mSoundEngine;

		std::vector<LinuxSound*> mFadingSounds;
		std::vector<SoundChain*> mSoundChains;

	};
}
