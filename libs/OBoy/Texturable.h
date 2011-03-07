#pragma once

#include "OBoyLib/CrtDbgInc.h"

namespace OBoy
{
  class Image;

	/*
	 * an interface for texturable shapes
	 */
	class Texturable
	{
	public:
		Texturable() { mTexture = NULL; }
		virtual ~Texturable() {};

    inline void setTexture(Image *texture) { mTexture = texture; };
    inline Image *getTexture() const { return mTexture; };

  private:

    Image *mTexture;

	};
}
