#include "LinuxImage.h"

#include <assert.h>
#include "ResourceLoader.h"

using namespace OBoy;

#include "OBoyLib/CrtDbgNew.h"

LinuxImage::LinuxImage(ResourceLoader *loader, const std::string &path) : Image(loader,path)
{
	mWidth = -1;
	mHeight = -1;
  mUseMipmap = false;
}

LinuxImage::~LinuxImage()
{
	assert(mTexture == NULL);
}

int LinuxImage::getWidth()
{
	return mWidth;
}

int LinuxImage::getHeight()
{
	return mHeight;
}

bool LinuxImage::init(bool includeSounds)
{
	return mLoader->load(this);
}

void LinuxImage::destroy(bool includeSounds)
{
	if (glIsTexture(mTexture))
	{
    glDeleteTextures(1, &mTexture);
	}
}

void LinuxImage::setSize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

void LinuxImage::setTexture(GLuint tex, bool isScaled)
{
	mTexture = tex;
	mIsTextureScaled = isScaled;
}
