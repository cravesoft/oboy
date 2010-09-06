#include "LinuxResourceLoader.h"

#include <assert.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/glus.h>
#include "Environment.h"
#include "LinuxImage.h"
#include "LinuxGLInterface.h"
#include "LinuxSound.h"
#include "LinuxSoundPlayer.h"

using namespace OBoy;

#include "OBoyLib/CrtDbgNew.h"

LinuxResourceLoader::LinuxResourceLoader(const std::string &language1, 
									 const std::string &language2) 
									 : ResourceLoader(language1,language2)
{
}

LinuxResourceLoader::~LinuxResourceLoader()
{
}

Image *LinuxResourceLoader::createImage(const std::string &filename)
{
	return new LinuxImage(this,filename);
}

Sound *LinuxResourceLoader::createSound(const std::string &filename)
{
	return new LinuxSound(this,filename);
}

bool LinuxResourceLoader::load(Image *image)
{
	LinuxImage *img = dynamic_cast<LinuxImage*>(image);

	// try to find a localized version:
  GLUSpngimage pngimage;
  GLuint tex;
	std::string fname = img->getPath()+"."+mLanguage1+".png";
	FILE *f = fopen(fname.c_str(),"rb");
	if (f==NULL)
	{
		if (mLanguage2.size()>0)
		{
			// try backup language:
			fname = img->getPath()+"."+mLanguage2+".png";
			f = fopen(fname.c_str(),"rb");
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

  // load the image
  GLUSboolean success = glusLoadPngImage(fname.c_str(), &pngimage);

	if (!success)
	{
		envDebugLog("could not load texture: %s.png\n",img->getPath().c_str());
	}

  // create a new name for the texture
  glGenTextures(1, &tex);

	glBindTexture(GL_TEXTURE_2D, tex);
	
  glTexImage2D(GL_TEXTURE_2D, 0, pngimage.format, pngimage.width, pngimage.height, 0, pngimage.format, GL_UNSIGNED_BYTE, pngimage.data);

  glusDestroyPngImage(&pngimage);

	if (img->useMipmap())
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // TODO: get scaled parameter

  // set the texture:
	img->setTexture(tex, false);

	// remember the original image size:
	img->setSize(pngimage.width, pngimage.height);

  return true;
}

bool LinuxResourceLoader::load(Sound *sound)
{
	LinuxSound *snd = dynamic_cast<LinuxSound*>(sound);

	irrklang::ISoundSource *iss = tryLoad(snd->getPath()+"."+mLanguage1+".ogg"); // localized
	if (iss == NULL)
	{
		if (mLanguage2.size()>0)
		{
			iss = tryLoad(snd->getPath()+"."+mLanguage2+".ogg"); // localized
			if (iss == NULL)
			{
				iss = tryLoad(snd->getPath()+".ogg"); // default with ogg extension
			}
		}
		else
		{
			iss = tryLoad(snd->getPath()+".ogg"); // default with ogg extension
		}
	}

	if (iss == NULL)
	{
		envDebugLog("error loading sound '%s'\n",snd->getPath().c_str());
	}
//	assert(iss!=NULL);

	// store the sound source in the sound object:
	snd->setISoundSource(iss);

	if (iss!=NULL)
	{
		// make sure it's loaded:
		void *data = iss->getSampleData();
		if (data==NULL)
		{
			assert(false);
		}

		return true;
	}
	else
	{
		return false;
	}
}

irrklang::ISoundSource *LinuxResourceLoader::tryLoad(const std::string &filename)
{
	SoundPlayer *sp = Environment::instance()->getSoundPlayer();
	LinuxSoundPlayer *player = dynamic_cast<LinuxSoundPlayer*>(sp);
	irrklang::ISoundEngine *engine = player->getEngine();
	if (engine==NULL)
	{
		return NULL;
	}

	// if this file is already loaded:
	irrklang::ISoundSource *iss = engine->getSoundSource(filename.c_str(),false);
	if (iss!=NULL)
	{
		return iss;
	}

	// let's try to load it:
	iss = engine->addSoundSourceFromFile(
		filename.c_str(), // filename
		irrklang::ESM_NO_STREAMING, // no streaming
		false); // no preload
	iss->setForcedStreamingThreshold(-1);
	unsigned int len = iss->getPlayLength();
	if (len==0xffffffff)
	{
		engine->removeSoundSource(iss);
		return NULL;
	}

	return iss;
}
