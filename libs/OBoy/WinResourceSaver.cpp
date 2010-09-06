#include "WinResourceSaver.h"

#include <assert.h>
#include "Environment.h"
#include "WinD3DInterface.h"
#include "WinImage.h"

using namespace OBoy;

#include "OBoyLib/CrtDbgNew.h"

WinResourceSaver::WinResourceSaver(const std::string &language1, 
									 const std::string &language2,
                   WinD3DInterface *sdld3dInterface)
									 : ResourceSaver(language1,language2)
{
  mInterface = sdld3dInterface;
}

WinResourceSaver::~WinResourceSaver()
{
}

bool WinResourceSaver::save(Image *image)
{
  WinImage *img = dynamic_cast<WinImage*>(image);

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

	IDirect3DTexture9 *tex = img->getTexture();

	if (tex==NULL)
	{
		envDebugLog("could not save texture: %s.png\n",img->getPath().c_str());
	}

	// save the texture:
	if (tex!=NULL)
	{
    return mInterface->saveTexture(tex, fname.c_str());
	}

	return false;
}