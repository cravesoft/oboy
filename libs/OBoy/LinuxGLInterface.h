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

  typedef struct glColor
  {
    float red;
    float green;
    float blue;
    float alpha;
  } glColor;

  inline glColor parseColor(const oboy::Color color)
  {
    glColor col;
    col.red = ((color & 0x00ff0000) >> 16) / 256.0;
    col.green = ((color & 0x0000ff00) >> 8) / 256.0;
    col.blue = (color & 0x000000ff) / 256.0;
    col.alpha = ((color & 0xff000000) >> 24) / 256.0;
    return col;
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
		void drawImage(LinuxImage *image, Color color, float z);
		void drawImage(LinuxImage *image, Color color, float z, int x, int y, int w, int h);
		void drawRect(int x, int y, int w, int h, float z, Color color);
    void drawCircle(int x, int y, float radius, int delta, Color color);
		void drawTriStrip(LinuxTriStrip *strip);
    void drawLineStrip(LinuxLineStrip *strip);
    void drawLines(LinuxLines *lines);
		void drawLine(int x0, int y0, int x1, int y1, Color color);
    void drawSphere(LinuxSphere *sphere, Color color, float z);
    void drawCube(LinuxCube *cube, Color color, float z);

    // toggle screen mode
    void toggleFullScreen();

		// vertex buffer creation:
		//IDirect3DVertexBuffer9 *createVertexBuffer(int numVerts);

		// clearing:
		inline void setClearZ(float z) { mClearZ = z; }
    inline void setClearColor(oboy::Color color) { mClearColor = parseColor(color); }

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
		glColor				mClearColor;

    bool mWindowed;

		// hardware capabilities:
		GLint  mMaxTextureSize;
	};
}

