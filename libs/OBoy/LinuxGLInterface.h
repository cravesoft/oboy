#pragma once

#include "Environment.h"
#include "Graphics.h"
#include <string>
#include <GL/glew.h>
#include <GL/glus.h>
#include <SDL.h>

namespace OBoy
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

  glColor parseColor(const OBoy::Color color)
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
		void drawImage(LinuxImage *image, DWORD color, float z);
		void drawImage(LinuxImage *image, DWORD color, float z, int x, int y, int w, int h);
		void drawRect(int x, int y, int w, int h, float z, DWORD color);
    void drawCircle(int x, int y, float radius, int delta, Color color);
		void drawTriStrip(LinuxTriStrip *strip);
    void drawLineStrip(LinuxLineStrip *strip);
		void drawLine(int x0, int y0, int x1, int y1, Color color);
    void drawSphere(LinuxSphere *image, DWORD color, float z);

    // toggle screen mode
    void toggleFullScreen();

		// vertex buffer creation:
		//IDirect3DVertexBuffer9 *createVertexBuffer(int numVerts);

		// clearing:
		inline void setClearZ(float z) { mClearZ = z; }
    inline void setClearColor(OBoy::Color color) { mClearColor = parseColor(color); }

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
		void handleLostDevice();
		void handleResetDevice();

	private:

    void initIL();
		void initGL();
		void assertSuccess(const char* funcName);
		void drawImage(GLuint tex);
    void drawSphere(LinuxSphere *sphere, GLuint tex);
		//void printDisplayModes(D3DFORMAT format, bool windowed);

	private:

		std::string				mTitle;

		OBoy::Game				*mGame;

		bool					mRendering;

    GLUSshaderprogram mProgram;

		GLuint        mImageVertices;
    GLuint        mImageIndices;
    GLuint        vertexPositionAttrib;
    GLuint        vertexColorAttrib;
    GLuint        texCoordAttrib;

    // location of the projection matrix in the shader program
    GLint mProjectionLocation;

    // location of the model view matrix in the shader program
    GLint mModelViewLocation;

    // location of the vertex in the shader program
    GLint mVertexLocation;

    // location of the normal in the shader program
    GLint mNormalLocation;

    SDL_Surface  *mScreen;

		float					mClearZ;
		glColor				mClearColor;

    bool mWindowed;

		// hardware capabilities:
		unsigned int  mMaxTextureSize;
	};
}

