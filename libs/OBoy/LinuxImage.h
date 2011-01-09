#pragma once

#include "Image.h"
#include <GL/glew.h>

namespace oboy
{
	class LinuxImage : public Image
	{
	public:

		LinuxImage(ResourceLoader *loader, const std::string &path);
		virtual ~LinuxImage();

		void setSize(int width, int height);

		const std::string &getPath() { return mPath; }

		void setTexture(GLuint tex, bool isScaled);

		inline GLuint getTexture() { return mTexture; }

		inline bool isTextureScaled() { return mIsTextureScaled; }

    inline void setMipmap(bool value) { mUseMipmap = value; }

    inline bool useMipmap() { return mUseMipmap; }

		// implementation of Image:
		virtual int getWidth();
		virtual int getHeight();

	private:

		// implementation of Resource:
		virtual bool init(bool includeSounds);
		virtual void destroy(bool includeSounds);

	private:

    GLuint mTexture;

		int mWidth;
		int mHeight;

    bool mUseMipmap;
		bool mIsTextureScaled;
	};
};
