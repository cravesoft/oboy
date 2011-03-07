#pragma once

#include "OBoyLib/Rect.h"
#include "OBoyLib/UStringStream.h"
#include "OBoyLib/Vector2.h"
#include "Resource.h"
#include "tinyxml/tinyxml.h"
#include <string>
#include <vector>

namespace OBoy
{
	class Graphics;
	class Image;

	struct FontChar
	{
		int width;
		OBoyLib::Rect subrect;
		OBoyLib::Vector2 offset;
		std::map<wchar_t,int> kearningValues;
	};

	class Font : public Resource
	{
	public:

		Font(ResourceLoader *loader, const std::string &path);
		virtual ~Font();

		// font construction:
		void addChar(wchar_t ch);
		bool hasChar(wchar_t ch);
		void setWidth(wchar_t ch, int width);
		void setSubrect(wchar_t ch, const OBoyLib::Rect &subrect);
		void setOffset(wchar_t ch, const OBoyLib::Vector2 &offset);
		void setKerning(wchar_t ch1, wchar_t ch2, int kvalue);

		// font access:
		int getHeight();
		int getStringWidth(const OBoy::UString &str);
		int getLineSpacing();

		float drawString(Graphics *g, const OBoy::UString &str, float scale=1);

	protected:

		// implementation of Resource:
		virtual bool init(bool includeSounds);
		virtual void destroy(bool includeSounds);

	private:

		// misc:
		/*void loadCharList(OBoy::UStringStream &fontStream, std::vector<wchar_t> &charList);
		void loadWidthList(OBoy::UStringStream &fontStream, std::vector<int> &widthList);
		void loadRectList(OBoy::UStringStream &fontStream, std::vector<OBoyLib::Rect> &rectList);
		void loadOffsetList(OBoy::UStringStream &fontStream, std::vector<OBoyLib::Vector2> &offsetList);
		void loadKerningPairs(OBoy::UStringStream &fontStream, std::vector<OBoy::UString> &kerningPairs);
		void loadKerningValues(OBoy::UStringStream &fontStream, std::vector<int> &kerningValues);*/
    bool Font::parseImageSetFile(const std::string &fileName);
    bool Font::parseFontFile(const std::string &fileName);

	private:

		Image *mImage;

		float mHeight;
		float mSpacing;
		float mLineSpacing;
		float mScale;

		std::map<wchar_t,FontChar*> mChars;
		
	};
}

