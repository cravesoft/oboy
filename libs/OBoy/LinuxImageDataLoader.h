#pragma once

#include <SDL/SDL.h>
#include <string>

namespace OBoy
{
  // struct representing some image data
  struct ImageData
  {
	  // actual data
	  unsigned char *pixels;
	  // width (in pixels) of the image
	  unsigned int width;
	  // height (in pixels) of the image
	  unsigned int height;
    // alpha channel
    unsigned char *alpha;
  };

	class LinuxImageDataLoader
	{
	public:

    LinuxImageDataLoader();
    ~LinuxImageDataLoader();

		// loads an image from memory
	  // the caller is responsible for calling destroyImage to delete ImageData::data
  	ImageData loadImageData(const char *data, unsigned int size);
	
    // loads an image from a file
		// the caller is responsible for calling destroyImage to delete ImageData::data
  	ImageData loadImageData(const std::string &filename);

    void destroyImageData();

  private:

    ImageData loadImageData(SDL_Surface *surface);
    SDL_Surface *mPixels;
    SDL_Surface *mAlpha;

	};
};