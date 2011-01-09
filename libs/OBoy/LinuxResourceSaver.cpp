#include "LinuxResourceSaver.h"

#include <assert.h>
#include "Environment.h"
#include "LinuxGLInterface.h"
#include "LinuxImage.h"

using namespace oboy;

#include "oboylib/CrtDbgNew.h"

LinuxResourceSaver::LinuxResourceSaver(const std::string &language1, 
									 const std::string &language2,
                   LinuxGLInterface *sdlglInterface)
									 : ResourceSaver(language1,language2)
{
  mInterface = sdlglInterface;
}

LinuxResourceSaver::~LinuxResourceSaver()
{
}

bool LinuxResourceSaver::save(Image *image)
{
  LinuxImage *img = dynamic_cast<LinuxImage*>(image);

	// try to find a localized version:
	std::string fname = img->getPath()+"."+mLanguage1+".png";
	FILE *f = fopen(fname.c_str(),"wb");
	if (f==NULL)
	{
		if (mLanguage2.size()>0)
		{
			// try backup language:
			fname = img->getPath()+"."+mLanguage2+".png";
			f = fopen(fname.c_str(),"wb");
			if (f==NULL)
			{
				fname = img->getPath()+".png";
			}
			else
			{
				fclose(f);
			}
		}
		else
		{
			fname = img->getPath()+".png";
		}
	}
	else
	{
		fclose(f);
	}

  // TODO

	return false;
}