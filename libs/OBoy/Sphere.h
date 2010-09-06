#pragma once

#include "OBoyLib/CrtDbgInc.h"
#include "Graphics.h"

namespace OBoy
{
  class Image;

	class Sphere
	{
	public:

    Sphere(float radius, int numSlices, int numStacks) : mImage(NULL) {}
		virtual ~Sphere() {}

		virtual void setColor(Color color) = 0;

    inline void setImage(Image *image) { mImage = image; };
    inline Image *getImage() const { return mImage; };

  private:

    Image *mImage;
	};
}
