#pragma once

#include <string>

namespace oboy
{

	class CoherentNoise
	{
	public:

		CoherentNoise();
		virtual ~CoherentNoise();

    static void createSphereHeightMap(const std::string &path, const char *surface, int width, int height);
	};
}