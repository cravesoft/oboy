#pragma once

#include "Environment.h"
#include "Graphics.h"
#include <string>
#include <GL/glew.h>
#include <SDL.h>

namespace oboy
{
	struct BoyVertex
	{
		float x, y, z; // position
		float red, green, blue; // color
		float u, v; // texture coords
	};

	class Game;
	class LinuxImage;
	class LinuxTriStrip;
  class LinuxLineStrip;
  class LinuxSphere;
  class LinuxCube;
  class LinuxLines;

	class LinuxGLInterface
	{
	public:

		LinuxGLInterface(Game *game, int width, int height, const char *title, bool windowed, unsigned int refreshRate);
		virtual ~LinuxGLInterface();

		// window methods:
		int getWidth();
		int getHeight();
		bool isWindowed();
//		void toggleFullScreen(bool toggle);

		// rendering methods:
		bool beginScene();
		void endScene();
		void drawImage(LinuxImage *image, oboylib::Color color, float z);
		void drawImage(LinuxImage *image, oboylib::Color color, float z, int x, int y, int w, int h);
		void drawRect(int x, int y, int w, int h, float z, oboylib::Color color);
    void drawCircle(int x, int y, float radius, int delta, oboylib::Color color);
		void drawTriStrip(LinuxTriStrip *strip);
    void drawLineStrip(LinuxLineStrip *strip);
    void drawLines(LinuxLines *lines);
		void drawLine(int x0, int y0, int x1, int y1, oboylib::Color color);
    void drawSphere(LinuxSphere *sphere, oboylib::Color color, float z);
    void drawCube(LinuxCube *cube, oboylib::Color color, float z);

    // toggle screen mode
    void toggleFullScreen();

		// vertex buffer creation:
		//IDirect3DVertexBuffer9 *createVertexBuffer(int numVerts);

		// clearing:
		inline void setClearZ(float z) { mClearZ = z; }
    inline void setClearColor(oboylib::Color color) { mClearColor = color; }

		// gl state:
    void setCapability(int state, bool enabled);
    bool isEnabled(int state);
    void setDepthMask(bool enabled);
    bool isDepthMaskEnabled();
    void setDepthFunction(int zfunc);
    void setBlendFunc(int sfactor, int dfactor);
    void setAlphaRef(int ref);
    void setAlphaFunc(int func);

		// clipping:
		void setClipRect(int x, int y, int width, int height);

		// misc:
		void dumpInfo(std::ofstream &file);

    // input:
    
    void            handleMouseDown(int button);
    void            handleMouseUp(int button);
    void            handleKeyDown(SDL_keysym key);
    void            handleKeyUp(SDL_keysym key);
    void            injectInput();

	private:

    void initIL();
		void initGL();
		void assertSuccess(const char* funcName);
    int getKeyMods();
		//void printDisplayModes(D3DFORMAT format, bool windowed);

	private:

		std::string	  mTitle;

		oboy::Game   *mGame;

		bool					mRendering;

		GLuint        mImageVertices;
    GLuint        mImageIndices;

    SDL_Surface  *mScreen;

		float					mClearZ;
    oboylib::Color mClearColor;

    bool mWindowed;

		// hardware capabilities:
		GLint  mMaxTextureSize;
	};
}

