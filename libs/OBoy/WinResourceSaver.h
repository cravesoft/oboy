#pragma once

#include "oboylib/CrtDbgInc.h"

#include "ResourceSaver.h"

namespace oboy
{
	class WinD3DInterface;

	class WinResourceSaver : public ResourceSaver
	{
	public:

		WinResourceSaver(const std::string &language1, const std::string &language2, WinD3DInterface *sdld3dInterface);
		virtual ~WinResourceSaver();

		virtual bool save(Image *image);

	private:

		WinD3DInterface *mInterface;

	};
};
