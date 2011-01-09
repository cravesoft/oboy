#pragma once

#include "oboylib/CrtDbgInc.h"

#include "irrKlang.h"
#include "ResourceLoader.h"

namespace oboy
{
	class LinuxGLInterface;

	class LinuxResourceLoader : public ResourceLoader
	{
	public:

		LinuxResourceLoader(const std::string &language1, const std::string &language2);
		virtual ~LinuxResourceLoader();

		virtual bool load(Image *image);
		virtual bool load(Sound *sound);
		virtual Image *createImage(const std::string &filename);
		virtual Sound *createSound(const std::string &filename);

	private:

		irrklang::ISoundSource *tryLoad(const std::string &filename);

	};
};
