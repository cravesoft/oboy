#pragma once

#include "OBoyLib/CrtDbgInc.h"

#include "ResourceSaver.h"

namespace OBoy
{
	class LinuxGLInterface;

	class LinuxResourceSaver : public ResourceSaver
	{
	public:

		LinuxResourceSaver(const std::string &language1, const std::string &language2, LinuxGLInterface *sdlglInterface);
		virtual ~LinuxResourceSaver();

		virtual bool save(Image *image);

	private:

		LinuxGLInterface *mInterface;

	};
};
