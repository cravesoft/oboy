#include "LinuxImageDataLoader.h"
#include "Environment.h"
#include "OBoyLib/OBoyUtil.h"
#include <SDL/SDL_image.h>
#include <iostream>

using namespace OBoy;

LinuxImageDataLoader::LinuxImageDataLoader()
{
}

LinuxImageDataLoader::~LinuxImageDataLoader()
{
}

ImageData LinuxImageDataLoader::loadImageData(const char *data, unsigned int size)
{
	SDL_Surface *surface = IMG_Load_RW(SDL_RWFromConstMem(data, size), 1);

	return loadImageData(surface);
}

ImageData LinuxImageDataLoader::loadImageData(const std::string &path)
{
	SDL_Surface *surface = IMG_Load(path.c_str());

  return loadImageData(surface);
}

ImageData LinuxImageDataLoader::loadImageData(SDL_Surface *surface)
{
  int w = findNextHigherPowerOf2(surface->w);
  int h = findNextHigherPowerOf2(surface->h);
  Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif
  mPixels = SDL_DisplayFormatAlpha(surface);
  SDL_SetAlpha(surface, 0, SDL_ALPHA_TRANSPARENT);
  mAlpha = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, bmask, gmask, rmask, amask);

  ImageData image;
	image.width = surface->w;
	image.height = surface->h;
  image.pixels = (unsigned char *)mPixels->pixels;
  image.alpha = (unsigned char *)mAlpha->pixels;

  return image;
}

void LinuxImageDataLoader::destroyImageData()
{
  SDL_FreeSurface(mPixels);
  SDL_FreeSurface(mAlpha);
}