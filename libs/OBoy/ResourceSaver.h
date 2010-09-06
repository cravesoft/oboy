#pragma once

#include "OBoyLib/CrtDbgInc.h"

#include <string>

namespace OBoy
{
	class Image;

	class ResourceSaver
	{
	public:
		
		ResourceSaver(const std::string &language1, const std::string &language2) { mLanguage1 = language1; mLanguage2 = language2; }
		virtual ~ResourceSaver() {}

		virtual bool save(Image *image) = 0;

		std::string &getLanguage1() { return mLanguage1; }
		std::string &getLanguage2() { return mLanguage2; }

	protected:

		std::string mLanguage1;
		std::string mLanguage2;

	};
}

