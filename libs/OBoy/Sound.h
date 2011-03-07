#pragma once

#include "OBoyLib/CrtDbgInc.h"
#include "Resource.h"

namespace OBoy
{
	class Sound : public Resource
	{
	public:
		Sound(ResourceLoader *loader, const std::string &path) : Resource(loader, path) {}
		virtual ~Sound() {}
	};
}

