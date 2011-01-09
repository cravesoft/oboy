#pragma once

#include "oboylib/Rect.h"
#include "oboylib/UStringStream.h"
#include "oboylib/Vector2.h"
#include "Resource.h"
#include "tinyxml/tinyxml.h"
#include <string>
#include <vector>

namespace oboy
{
	class Graphics;
	class Image;

	struct FontChar
	{
		int width;
		oboylib::Rect subrect;
		oboylib::Vector2 offset;
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
		void setSubrect(wchar_t ch, const oboylib::Rect &subrect);
		void setOffset(wchar_t ch, const oboylib::Vector2 &offset);
		void setKerning(wchar_t ch1, wchar_t ch2, int kvalue);

		// font access:
		int getHeight();
		int getStringWidth(const oboy::UString &str);
		int getLineSpacing();

		float drawString(Graphics *g, const oboy::UString &str, float scale=1);

	protected:

		// implementation of Resource:
		virtual bool init(bool includeSounds);
		virtual void destroy(bool includeSounds);

	private:

		// misc:
		/*void loadCharList(oboy::UStringStream &fontStream, std::vector<wchar_t> &charList);
		void loadWidthList(oboy::UStringStream &fontStream, std::vector<int> &widthList);
		void loadRectList(oboy::UStringStream &fontStream, std::vector<oboylib::Rect> &rectList);
		void loadOffsetList(oboy::UStringStream &fontStream, std::vector<oboylib::Vector2> &offsetList);
		void loadKerningPairs(oboy::UStringStream &fontStream, std::vector<oboy::UString> &kerningPairs);
		void loadKerningValues(oboy::UStringStream &fontStream, std::vector<int> &kerningValues);*/
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

