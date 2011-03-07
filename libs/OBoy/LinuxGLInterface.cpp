#include "LinuxGLInterface.h"

#include <assert.h>
#include "OBoy/Mouse.h"
#include "OBoyLib/OBoyUtil.h"
#include "Environment.h"
#include <fstream>
#include "Game.h"
#include <iostream>
#include "Keyboard.h"
#include "PersistenceLayer.h"
#include "ResourceManager.h"
#include "LinuxEnvironment.h"
#include "LinuxImage.h"
#include "LinuxTriStrip.h"
#include "LinuxLineStrip.h"
#include "LinuxSphere.h"
#include "LinuxCube.h"
#include "LinuxLines.h"

using namespace OBoy;

#define PROJECTION_Z_NEAR -50//0
#define PROJECTION_Z_FAR 1//1

#define CAM_Z PROJECTION_Z_FAR

#define DEFAULT_BPP 32

#include "OBoyLib/CrtDbgNew.h"

LinuxGLInterface::LinuxGLInterface(Game *game, int width, int height, const char *title, bool windowed, unsigned int refreshRate)
{
	// reset some members:
	mRendering = false;

	// remember the game:
	mGame = game;

  // initialize SDL's subsystems - in this case, only video:
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    envDebugLog("ERROR: unable to initialize SDL\n",);
    return;
  }

  // activate unicode translation for SDL key events:
  SDL_EnableUNICODE(1);

  // enable key repeat for the text input widgets in CEGUI:
	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

  int flags = SDL_OPENGL | SDL_DOUBLEBUF;
  int bitsPerPixel;
  mWindowed = windowed;

  // find image format:
	if (mWindowed)
	{
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    bitsPerPixel = info->vfmt->BitsPerPixel;
	}
  else
  {
    flags |= SDL_FULLSCREEN;
    bitsPerPixel = DEFAULT_BPP;
  }

  switch (bitsPerPixel)
  {
  case 32: // 32-Bit
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    break;
  case 24: // 24-Bit
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    break;
  case 16: // 16-Bit
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 0);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    break;
  default: // other formats unsupported
    envDebugLog("WARNING: trying to use an unsupported image format\n",);
  }

  // set the size of the stencil buffer:
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  // create device:
	mScreen = SDL_SetVideoMode(width, height, bitsPerPixel, flags);
  if (mScreen == NULL)
  {
    envDebugLog("ERROR: unable to set videio mode\n",);
    return;
  }

  // initialize gl:
	initGL();

  // generate buffer object names to be
  // used for drawing subrects of images:
	glGenBuffers(1, &mImageVertices);
  assertSuccess("glGenBuffers");
  glGenBuffers(1, &mImageIndices);
  assertSuccess("glGenBuffers");

	// set the window title:
	mTitle = title;
	SDL_WM_SetCaption(mTitle.c_str(), NULL);

	// clearing params:
	mClearZ = PROJECTION_Z_FAR;
  mClearColor.argb = OBoyLib::Color::Black;
}

LinuxGLInterface::~LinuxGLInterface()
{
  // delete image buffer objects
  glDeleteBuffers(1, &mImageVertices);
  glDeleteBuffers(1, &mImageIndices);

  SDL_Quit();
}

int LinuxGLInterface::getWidth()
{
  const SDL_VideoInfo* info = SDL_GetVideoInfo();
  return info->current_w;
}

int LinuxGLInterface::getHeight()
{
	const SDL_VideoInfo* info = SDL_GetVideoInfo();
  return info->current_h;
}

bool LinuxGLInterface::isWindowed()
{
	return mWindowed;
}

bool LinuxGLInterface::beginScene()
{
	// set the rendering flag:
	mRendering = true;

  glClearColor(mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);

  glClearDepth(1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// let the rendering begin...
	float w = (float)getWidth();
	float h = (float)getHeight();
	float w2 = w/2;
	float h2 = h/2;

  // set the viewport
  //glViewport(0, 0, w, h);

  // load the projection transform matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // set the projection
  glOrtho((FLOAT)-w2,
          (FLOAT)w2,
          (FLOAT)-h2,
          (FLOAT)h2,
          (FLOAT)PROJECTION_Z_NEAR,
          (FLOAT)PROJECTION_Z_FAR);

  // load the modelview transform matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

	gluLookAt(w2, h2, -CAM_Z,	// the camera position
		        w2, h2,  0,		// the look-at position
		        0,  -1,  0);		// the up direction

	// set some default state stuff:
  setCapability(GL_BLEND, true);
  setCapability(GL_ALPHA_TEST, true);
  setAlphaRef(1);
  setBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  /*setBlendFunc(GL_SRC_ALPHA, GL_ONE);*/
#if 0
	DXUTGetD3D9Device()->SetRenderState(D3DRS_COLORVERTEX, true);
	DXUTGetD3D9Device()->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
#endif
	return true;
}

void LinuxGLInterface::endScene()
{
	// reset the rendering flag:
	mRendering = false;

  glFlush();

  // update the screen
  SDL_GL_SwapBuffers();
}

void LinuxGLInterface::drawImage(LinuxImage *image, OBoyLib::Color color, float z)
{
	drawImage(image, color, z, 0, 0, image->getWidth(), image->getHeight());
}

void LinuxGLInterface::drawImage(LinuxImage *image, OBoyLib::Color color, float z, int x, int y, int w, int h)
{
  // make sure beginScene was called:
  assert(mRendering);

	if (!image->getTexture())
	{
		envDebugLog("WARNING: trying to draw image with NULL texture (%s)\n",image->getPath().c_str());
		return;
	}
  
	float maxX = (float)w / 2.0f;
	float maxY = (float)h / 2.0f;
	float minX = -maxX;
	float minY = -maxY;

	float minU, minV, maxU, maxV;

#if 0
	if (image->isTextureScaled())
	{
#endif
		float imgW = (float)image->getWidth();
		float imgH = (float)image->getHeight();
		minU = x / imgW;
		minV = y / imgH;
		maxU = minU + w / imgW;
		maxV = minV + h / imgH;
#if 0
	}
	else
	{
		float texW = (float)textureInfo.Width;
		float texH = (float)textureInfo.Height;
		minU = x / texW;
		minV = y / texH;
		maxU = minU + w / texW;
		maxV = minV + h / texH;
	}
#endif

  GLfloat vertices[] = 
	{
    minX, minY, z, // bottom left
    maxX, minY, z, // top right
    minX, maxY, z, // top left
    maxX, maxY, z  // bottom right
	};

  GLubyte colors[] = 
	{
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a, 
    color.r, color.g, color.b, color.a
  };

  GLfloat texCoords[] =
  {
    minU, minV,
    maxU, minV, 
    minU, maxV, 
    maxU, maxV
  };

  GLuint indices[] = { 0, 1, 2, 3 };

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(colors)+sizeof(texCoords), 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(colors), colors);
  glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(colors), sizeof(texCoords), texCoords);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// make sure beginScene was called:
	assert(mRendering);

	glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

  // bind to image's vertex buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);

  // set vertices:
  glVertexPointer(3, GL_FLOAT, 0, 0);

  // set color values:
  glColorPointer(4, GL_UNSIGNED_BYTE, 0, (void*)(sizeof(vertices)));

  // set texture coordinates:
  glClientActiveTexture(GL_TEXTURE0);
  glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices)+sizeof(colors)));

  // bind to image's index buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);

	// set texture:
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, image->getTexture());

	// render from vertex buffer:
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableClientState(GL_VERTEX_ARRAY); 
  glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void LinuxGLInterface::drawRect(int x, int y, int w, int h, float z, OBoyLib::Color color)
{
  // make sure beginScene was called:
	assert(mRendering);

	float minX = (float)x;
	float minY = (float)y;
	float maxX = minX + w;
	float maxY = minY + h;

  GLuint vertexBuffer, indexBuffer;
  const int numVertex = 4;

  GLfloat vertices[] =
  {
    minX, minY, z,
    maxX, minY, z,
    minX, maxY, z,
    maxX, maxY, z
  };

  GLubyte colors[] =
  {
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a
  };

  GLuint indices[] = { 0, 1, 2, 3 };

  glGenBuffers(1, &vertexBuffer);

  int sizeVertices = 3*numVertex*sizeof(GLfloat);
  int sizeColors = 4*numVertex*sizeof(GLfloat);
  int sizeIndices = numVertex*sizeof(GLuint);

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeVertices+sizeColors, 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVertices, vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeVertices, sizeColors, colors);

  glGenBuffers(1, &indexBuffer);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  // set vertices:
  glVertexPointer(3, GL_FLOAT, 0, 0);

  // set color values:
  glColorPointer(4, GL_UNSIGNED_BYTE, 0, (void*)(sizeVertices));

  // render from vertex buffer:
  glDrawElements(GL_TRIANGLE_STRIP, numVertex, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableClientState(GL_VERTEX_ARRAY); 
  glDisableClientState(GL_COLOR_ARRAY);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);
}

void LinuxGLInterface::drawCircle(int x, int y, float radius, int delta, OBoyLib::Color color)
{
	// make sure beginScene was called:
	assert(mRendering);

  GLuint vertexBuffer, indexBuffer;
  int numVertex = 360/delta+1;
  int angle = 0, idx = 0;

  GLfloat *vertices = new GLfloat[3*numVertex];
  GLubyte *colors = new GLubyte[3*numVertex];
  GLuint *indices = new GLuint[numVertex];

  while (angle <= 360)
  {
	  vertices[3*idx+0] = (float)x + radius*cos(deg2rad(angle));
	  vertices[3*idx+1] = (float)y + radius*sin(deg2rad(angle));
	  vertices[3*idx+2] = 0;
	  colors[3*idx+0] = color.r;
    colors[3*idx+1] = color.g;
    colors[3*idx+2] = color.b;
    indices[idx] = idx;
    angle += delta;
    ++idx;
  }

  glGenBuffers(1, &vertexBuffer);

  int sizeVertices = 3*numVertex*sizeof(GLfloat);
  int sizeColors = 3*numVertex*sizeof(GLfloat);
  int sizeIndices = numVertex*sizeof(GLuint);

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeVertices+sizeColors, 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVertices, vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeVertices, sizeColors, colors);

  glGenBuffers(1, &indexBuffer);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  // set vertices:
  glVertexPointer(3, GL_FLOAT, 0, 0);

  // set color values:
  glColorPointer(3, GL_UNSIGNED_BYTE, 0, (void*)(sizeVertices));

  // render from vertex buffer:
  glDrawElements(GL_LINE_STRIP, numVertex, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableClientState(GL_VERTEX_ARRAY); 
  glDisableClientState(GL_COLOR_ARRAY);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);

  delete[] vertices;
  delete[] colors;
  delete[] indices;
}

void LinuxGLInterface::drawSphere(LinuxSphere *sphere, OBoyLib::Color color, float z)
{
  // make sure beginScene was called:
	assert(mRendering);

  // draw the sphere:
	sphere->draw();
}

void LinuxGLInterface::drawCube(LinuxCube *cube, OBoyLib::Color color, float z)
{
	// make sure beginScene was called:
	assert(mRendering);

	// draw the sphere:
	cube->draw();
}

void LinuxGLInterface::drawTriStrip(LinuxTriStrip *strip)
{
	// make sure beginScene was called:
	assert(mRendering);

  // draw the triangles strip:
  strip->draw();
}

void LinuxGLInterface::drawLineStrip(LinuxLineStrip *strip)
{
	// make sure beginScene was called:
	assert(mRendering);

  // draw the line strip:
  strip->draw();
}

void LinuxGLInterface::drawLines(LinuxLines *lines)
{
  	// make sure beginScene was called:
	assert(mRendering);

  // draw the line strip:
  lines->draw();
}

void LinuxGLInterface::drawLine(int x0, int y0, int x1, int y1, OBoyLib::Color color)
{
	// make sure beginScene was called:
	assert(mRendering);

  GLuint vertexBuffer, indexBuffer;
  const int numVertex = 2;

  GLfloat vertices[] =
  {
    x0, y0, 0,
    x1, y1, 0,
  };

  GLubyte colors[] =
  {
    color.r, color.g, color.b, color.a,
    color.r, color.g, color.b, color.a
  };

  GLuint indices[] = { 0, 1 };

  glGenBuffers(1, &vertexBuffer);

  int sizeVertices = 3*numVertex*sizeof(GLfloat);
  int sizeColors = 4*numVertex*sizeof(GLfloat);
  int sizeIndices = numVertex*sizeof(GLuint);

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeVertices+sizeColors, 0, GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeVertices, vertices);
  glBufferSubData(GL_ARRAY_BUFFER, sizeVertices, sizeColors, colors);

  glGenBuffers(1, &indexBuffer);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeIndices, indices, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

  // set vertices:
  glVertexPointer(3, GL_FLOAT, 0, 0);

  // set color values:
  glColorPointer(4, GL_UNSIGNED_BYTE, 0, (void*)(sizeVertices));

  // render from vertex buffer:
  glDrawElements(GL_LINES, numVertex, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDisableClientState(GL_VERTEX_ARRAY); 
  glDisableClientState(GL_COLOR_ARRAY);

  glDeleteBuffers(1, &vertexBuffer);
  glDeleteBuffers(1, &indexBuffer);
}

void LinuxGLInterface::assertSuccess(const char* funcName)
{
//#ifdef _DEBUG
  GLenum error;				
	error = glGetError();
  switch (error)
  {
  case GL_NO_ERROR:
	  break;
  case GL_INVALID_ENUM:
    envDebugLog("%s() caused GL_INVALID_ENUM\n",funcName);
	  break;
  case GL_INVALID_VALUE:
    envDebugLog("%s() caused GL_INVALID_VALUE\n",funcName);
	  break;
  case GL_INVALID_OPERATION:
    envDebugLog("%s() caused GL_INVALID_OPERATION\n",funcName);
	  break;
  case GL_STACK_OVERFLOW:
    envDebugLog("%s() caused GL_STACK_OVERFLOW\n",funcName);
	  break;
  case GL_STACK_UNDERFLOW:
    envDebugLog("%s() caused GL_STACK_UNDERFLOW\n",funcName);
	  break;
  case GL_OUT_OF_MEMORY:
    envDebugLog("%s() caused GL_OUT_OF_MEMORY\n",funcName);
	  break;
  case GL_TABLE_TOO_LARGE:
    envDebugLog("%s() caused GL_TABLE_TOO_LARGE\n",funcName);
	  break;
  }
//#endif
}

void LinuxGLInterface::toggleFullScreen()
{
  Uint32 flags;

  // save the current flags in case toggling fails
  flags = mScreen->flags;
  
  // toggle fullscreen mode
  mScreen = SDL_SetVideoMode(0, 0, 0, mScreen->flags ^ SDL_FULLSCREEN);

  // if toggle fullscreen failed, then switch back
  if (mScreen == NULL) mScreen = SDL_SetVideoMode(0, 0, 0, flags);

  // if you can't switch back for some reason, then epic fail
  if (mScreen == NULL) return;
}

void LinuxGLInterface::initGL()
{
	// init GLEW
  //glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    // Problem: glewInit failed, something is seriously wrong
    std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
    return;
  }

  if (!glewIsSupported("GL_VERSION_2_0")) {
    std::cerr << "OpenGL 2.0 not found, running at reduced mode" << std::endl;
  }
  else if (!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
    std::cerr << "GLSL unsupported" << std::endl;
    return;
  }
#if 0
  // only continue if OpenGL 3.2 is supported
	if (!glewIsSupported("GL_VERSION_3_2"))
	{
		printf("OpenGL 3.2 not supported.");
		return;
	}
#endif

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mMaxTextureSize);

	// set world / view matrices to identity:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // turn off lighting:
  glDisable(GL_LIGHTING);
}

void LinuxGLInterface::setCapability(int state, bool enabled)
{
  if (enabled)
  {
    glEnable(state);
    assertSuccess("glEnable");
  }
  else
  {
    glDisable(state);
	  assertSuccess("glDisable");
  }
}

bool LinuxGLInterface::isEnabled(int state)
{
  bool enabled = false;
  if (glIsEnabled(state))
    enabled = true;
  assertSuccess("glIsEnabled");
  return enabled;
}

void LinuxGLInterface::setDepthMask(bool enabled)
{
  glDepthMask(enabled);
  assertSuccess("glDepthMask");
}

bool LinuxGLInterface::isDepthMaskEnabled()
{
  GLboolean enabled;
  glGetBooleanv(GL_DEPTH_WRITEMASK, &enabled);
  assertSuccess("glGetBooleanv");
  return enabled ? true : false;
}

void LinuxGLInterface::setDepthFunction(int zfunc)
{
  glDepthFunc(zfunc);
  assertSuccess("glDepthFunc");
}

void LinuxGLInterface::setBlendFunc(int sfactor, int dfactor)
{
  glBlendFunc(sfactor, dfactor);
  assertSuccess("glBlendFunc");
}

void LinuxGLInterface::setAlphaRef(int ref)
{
  int func;
  glGetIntegerv(GL_ALPHA_TEST_FUNC, &func);
  assertSuccess("glGetIntegerv");
  glAlphaFunc(func, ref);
  assertSuccess("glAlphaFunc");
}

void LinuxGLInterface::setAlphaFunc(int func)
{
  int ref;
  glGetIntegerv(GL_ALPHA_TEST_REF, &ref);
  assertSuccess("glGetIntegerv");
  glAlphaFunc(func, ref);
  assertSuccess("glAlphaFunc");
}

void LinuxGLInterface::setClipRect(int x, int y, int width, int height)
{
  glScissor(x, y, width, height);
}

void LinuxGLInterface::dumpInfo(std::ofstream &file)
{
  file << "Vendor: " << glGetString(GL_VENDOR) << "\n";
  file << "Vendor: " << glGetString(GL_VENDOR) << "\n";
  file << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
}

static bool gLastMouseLeftDown = false;
static bool gLastMouseRightDown = false;
static bool gLastMouseMiddleDown = false;
void LinuxGLInterface::handleMouseDown(int button)
{
	switch (button)
  {
		case SDL_BUTTON_LEFT:
			if (gLastMouseLeftDown == false)
      {
        Environment::instance()->getMouse(0)->fireDownEvent(Mouse::BUTTON_LEFT,1);
        gLastMouseLeftDown = true;
      }
			break;
		case SDL_BUTTON_MIDDLE:
			if (gLastMouseMiddleDown == false)
      {
        Environment::instance()->getMouse(0)->fireDownEvent(Mouse::BUTTON_MIDDLE,1);
		    gLastMouseMiddleDown = true;
      }
			break;
		case SDL_BUTTON_RIGHT:
			if (gLastMouseRightDown == false)
      {
        Environment::instance()->getMouse(0)->fireDownEvent(Mouse::BUTTON_RIGHT,1);
		    gLastMouseRightDown = true;
      }
			break;
		case SDL_BUTTON_WHEELDOWN:
			Environment::instance()->getMouse(0)->fireWheelEvent(-1);
			break;
		case SDL_BUTTON_WHEELUP:
			Environment::instance()->getMouse(0)->fireWheelEvent(+1);
			break;
	}
}

void LinuxGLInterface::handleMouseUp(int button)
{
	switch (button)
  {
		case SDL_BUTTON_LEFT:
			if (gLastMouseLeftDown == true)
      {
        Environment::instance()->getMouse(0)->fireUpEvent(Mouse::BUTTON_LEFT);
        gLastMouseLeftDown = false;
	    }
			break;
		case SDL_BUTTON_MIDDLE:
			if (gLastMouseMiddleDown == true)
      {
        Environment::instance()->getMouse(0)->fireUpEvent(Mouse::BUTTON_MIDDLE);
        gLastMouseMiddleDown = false;
	    }
			break;
		case SDL_BUTTON_RIGHT:
      if (gLastMouseRightDown == true)
      {
        Environment::instance()->getMouse(0)->fireUpEvent(Mouse::BUTTON_RIGHT);
        gLastMouseRightDown = false;
	    }
			break;
	}
}

static int gAltDown = false;
static int gShiftDown = false;
static int gControlDown = false;
Keyboard::Key getKey(SDLKey keysym)
{
	switch (keysym)
	{
  case SDLK_LALT:
    gAltDown = !gAltDown;
	case SDLK_BACKSPACE:
		return Keyboard::KEY_BACKSPACE;
	case SDLK_TAB:
		return Keyboard::KEY_TAB;
	case SDLK_RETURN:
		return Keyboard::KEY_RETURN;
	case SDLK_LSHIFT:
    gShiftDown = !gShiftDown;
		return Keyboard::KEY_SHIFT;
	case SDLK_LCTRL:
    gControlDown = !gControlDown;
		return Keyboard::KEY_CONTROL;
  case SDLK_PAUSE:
		return Keyboard::KEY_PAUSE;
	case SDLK_ESCAPE:
		return Keyboard::KEY_ESCAPE;
	case SDLK_END:
		return Keyboard::KEY_END;
	case SDLK_HOME:
		return Keyboard::KEY_HOME;
	case SDLK_LEFT:
		return Keyboard::KEY_LEFT;
	case SDLK_UP:
		return Keyboard::KEY_UP;
	case SDLK_RIGHT:
		return Keyboard::KEY_RIGHT;
	case SDLK_DOWN:
		return Keyboard::KEY_DOWN;
	case SDLK_INSERT:
		return Keyboard::KEY_INSERT;
	case SDLK_DELETE:
		return Keyboard::KEY_DELETE;
	case SDLK_F1:
		return Keyboard::KEY_F1;
	case SDLK_F2:
		return Keyboard::KEY_F2;
	case SDLK_F3:
		return Keyboard::KEY_F3;
	case SDLK_F4:
		return Keyboard::KEY_F4;
	case SDLK_F5:
		return Keyboard::KEY_F5;
	case SDLK_F6:
		return Keyboard::KEY_F6;
	case SDLK_F7:
		return Keyboard::KEY_F7;
	case SDLK_F8:
		return Keyboard::KEY_F8;
	case SDLK_F9:
		return Keyboard::KEY_F9;
	case SDLK_F10:
		return Keyboard::KEY_F10;
	case SDLK_F11:
		return Keyboard::KEY_F11;
	case SDLK_F12:
		return Keyboard::KEY_F12;
	}

	return Keyboard::KEY_UNKNOWN;
}

int LinuxGLInterface::getKeyMods()
{
	int mods = Keyboard::KEYMOD_NONE;
	if (gAltDown) mods |= Keyboard::KEYMOD_ALT;
	if (gShiftDown) mods |= Keyboard::KEYMOD_SHIFT;
	if (gControlDown) mods |= Keyboard::KEYMOD_CTRL;
	return mods;
}

wchar_t gLastKeyDown;

void LinuxGLInterface::handleKeyDown(SDL_keysym keysym)
{
	Keyboard *kb = Environment::instance()->getKeyboard(0);
  wchar_t unicode = keysym.unicode & 0x7F;
	if (kb!=NULL)
	{
		Keyboard::Key key = getKey(keysym.sym);
		if (key!=Keyboard::KEY_UNKNOWN)
		{
			unicode = 0;
		}
    int mods = getKeyMods();
		kb->fireKeyDownEvent(unicode,key,(Keyboard::Modifiers)mods);
		gLastKeyDown = unicode;
    envDebugLog("keyDown: nChar=0x%x (%c)\n",unicode,unicode);
	}
#ifdef _DEBUG
	if (gControlDown && gAltDown && keysym.sym==SDLK_d)
	{
		Environment *env = Environment::instance();
		env->setDebugEnabled(!env->isDebugEnabled());
	}
#endif
}

void LinuxGLInterface::handleKeyUp(SDL_keysym keysym)
{
  Keyboard *kb = Environment::instance()->getKeyboard(0);
  wchar_t unicode = gLastKeyDown;
	if (kb!=NULL)
	{
		Keyboard::Key key = getKey(keysym.sym);
		if (key!=Keyboard::KEY_UNKNOWN)
		{
			unicode = 0;
		}
    int mods = getKeyMods();
		kb->fireKeyUpEvent(unicode,key,(Keyboard::Modifiers)mods);
    envDebugLog("keyUp: nChar=0x%x (%c)\n",unicode,unicode);
	}
}

void LinuxGLInterface::injectInput()
{
  // poll for events, and handle the ones we care about
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      // mouse motion handler
		  case SDL_MOUSEMOTION:
			  // inject the mouse position directly
        Environment::instance()->getMouse(0)->fireMoveEvent(static_cast<float>(e.motion.x),static_cast<float>(e.motion.y));
			  break;
      // mouse down handler
		  case SDL_MOUSEBUTTONDOWN:
			  // let a special function handle the mouse button down event
			  handleMouseDown(e.button.button);
			  break;
      // mouse up handler
		  case SDL_MOUSEBUTTONUP:
			  // let a special function handle the mouse button up event
			  handleMouseUp(e.button.button);
			  break;
      case SDL_KEYDOWN:
        handleKeyDown(e.key.keysym);
        break;
      case SDL_KEYUP:
        handleKeyUp(e.key.keysym);
        break;
      // WM quit event occured
		  case SDL_QUIT:
			  Environment::instance()->stopMainLoop();
			  break;
      case SDL_VIDEORESIZE:
			  //renderer_->setDisplaySize(CEGUI::Size(e.resize.w, e.resize.h));
			  break;
	  }
  }
}