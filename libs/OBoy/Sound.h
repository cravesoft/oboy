#pragma once

#include "oboylib/CrtDbgInc.h"
#include "Resource.h"

namespace oboy
{
	class Sound : public Resource
	{
	public:
		Sound(ResourceLoader *loader, const std::string &path) : Resource(loader, path) {}
		virtual ~Sound() {}
	};
}

