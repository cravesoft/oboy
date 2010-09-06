#include "LinuxGLInterface.h"

#include <assert.h>
#include "OBoy/Mouse.h"
#include "OBoyLib/OBoyUtil.h"
#include "Environment.h"
#include <fstream>
#include <IL/il.h>
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

using namespace OBoy;

#define PROJECTION_Z_NEAR -50//0
#define PROJECTION_Z_FAR 1//1

#define CAM_Z PROJECTION_Z_FAR

#define DEFAULT_BPP 32

#include "OBoyLib/CrtDbgNew.h"
#if 0
void CALLBACK askScreenSize(int *pWidth, int *pHeight, void* userContext)
{
	LinuxEnvironment *env = dynamic_cast<LinuxEnvironment*>(Environment::instance());
	env->getDesiredScreenSize(pWidth,pHeight);
}

static int gAltDown = false;
static int gShiftDown = false;
static int gControlDown = false;

Keyboard::Key getKey(UINT nChar)
{
	switch (nChar)
	{
	case VK_BACK:
		return Keyboard::KEY_BACKSPACE;
	case VK_TAB:
		return Keyboard::KEY_TAB;
	case VK_RETURN:
		return Keyboard::KEY_RETURN;
	case VK_SHIFT:
		return Keyboard::KEY_SHIFT;
	case VK_CONTROL:
		return Keyboard::KEY_CONTROL;
	case VK_PAUSE:
		return Keyboard::KEY_PAUSE;
	case VK_ESCAPE:
		return Keyboard::KEY_ESCAPE;
	case VK_END:
		return Keyboard::KEY_END;
	case VK_HOME:
		return Keyboard::KEY_HOME;
	case VK_LEFT:
		return Keyboard::KEY_LEFT;
	case VK_UP:
		return Keyboard::KEY_UP;
	case VK_RIGHT:
		return Keyboard::KEY_RIGHT;
	case VK_DOWN:
		return Keyboard::KEY_DOWN;
	case VK_INSERT:
		return Keyboard::KEY_INSERT;
	case VK_DELETE:
		return Keyboard::KEY_DELETE;
	case VK_F1:
		return Keyboard::KEY_F1;
	case VK_F2:
		return Keyboard::KEY_F2;
	case VK_F3:
		return Keyboard::KEY_F3;
	case VK_F4:
		return Keyboard::KEY_F4;
	case VK_F5:
		return Keyboard::KEY_F5;
	case VK_F6:
		return Keyboard::KEY_F6;
	case VK_F7:
		return Keyboard::KEY_F7;
	case VK_F8:
		return Keyboard::KEY_F8;
	case VK_F9:
		return Keyboard::KEY_F9;
	case VK_F10:
		return Keyboard::KEY_F10;
	case VK_F11:
		return Keyboard::KEY_F11;
	case VK_F12:
		return Keyboard::KEY_F12;
	}

	return Keyboard::KEY_UNKNOWN;
}

int getKeyMods()
{
	int mods = Keyboard::KEYMOD_NONE;
	if (gAltDown) mods |= Keyboard::KEYMOD_ALT;
	if (gShiftDown) mods |= Keyboard::KEYMOD_SHIFT;
	if (gControlDown) mods |= Keyboard::KEYMOD_CTRL;
	return mods;
}

UINT gLastKeyDown;

void CALLBACK keyPressed(UINT nChar, bool keyDown, bool altDown, void* userContext)
{
	LinuxEnvironment *env = dynamic_cast<LinuxEnvironment*>(Environment::instance());
	env->processVirtualMouseEvents(nChar,keyDown);

	gAltDown = altDown;
	gShiftDown = DXUTIsKeyDown(VK_SHIFT);
	gControlDown = DXUTIsKeyDown(VK_CONTROL);

	Keyboard *kb = Environment::instance()->getKeyboard(0);
	if (kb!=NULL)
	{
		int mods = getKeyMods();
		Keyboard::Key key = getKey(nChar);
		if (key!=Keyboard::KEY_UNKNOWN)
		{
			nChar = 0;
		}

		if (keyDown)
		{
			// if this is a modified key or if it has no unicode equivalent:
			bool haveMods = mods!=Keyboard::KEYMOD_NONE;
			bool noUnicode = (nChar==0);
			if (haveMods || noUnicode)
			{
				kb->fireKeyDownEvent(nChar,key,(Keyboard::Modifiers)mods);
				gLastKeyDown = nChar;
//				envDebugLog("keyPressed: nChar=0x%x (%c)\n",nChar,nChar);
			}
		}
		else
		{
			kb->fireKeyUpEvent(nChar, key, (Keyboard::Modifiers)mods);
		}
	}

#ifdef _DEBUG
	if (gControlDown && gAltDown && nChar=='D' && keyDown)
	{
		Environment *env = Environment::instance();
		env->setDebugEnabled(!env->isDebugEnabled());
	}
#endif
}

void CALLBACK charPressed(wchar_t nChar, void* userContext)
{
	Keyboard *kb = Environment::instance()->getKeyboard(0);
	if (kb!=NULL)
	{
		int mods = getKeyMods();
		if (mods==Keyboard::KEYMOD_NONE && gLastKeyDown!=nChar)
		{
			kb->fireKeyDownEvent((wchar_t)nChar,Keyboard::KEY_UNKNOWN,(Keyboard::Modifiers)mods);
		}
	}
//	envDebugLog("charPressed: nChar=0x%x (%c)\n",nChar,nChar);
}

bool CALLBACK modifyDeviceSettings(DXUTDeviceSettings* deviceSettings, const D3DCAPS9* caps, void* userContext)
{
//	envDebugLog("modifyDeviceSettings\n");
    return true;
}

static bool gLastMouseLeftDown = false;
static bool gLastMouseRightDown = false;
static bool gLastMouseMiddleDown = false;
static int gLastMouseX = -1;
static int gLastMouseY = -1;
void CALLBACK mouseEvent(bool leftDown, bool rightDown, bool middleDown, bool side1Down, bool side2Down, int wheelDelta, int x, int y, void* userContext)
{
	// if this is a mouse move event:
	if (x!=gLastMouseX || y!=gLastMouseY)
	{
		gLastMouseX = x;
		gLastMouseY = y;
		Environment::instance()->getMouse(0)->fireMoveEvent((float)x,(float)y);
	}
	else if (gLastMouseLeftDown!=leftDown)
	{
		gLastMouseLeftDown = leftDown;
		if (leftDown)
		{
			Environment::instance()->getMouse(0)->fireDownEvent(Mouse::BUTTON_LEFT,1);
		}
		else
		{
			Environment::instance()->getMouse(0)->fireUpEvent(Mouse::BUTTON_LEFT);
		}
	}
  else if (gLastMouseRightDown!=rightDown)
	{
		gLastMouseRightDown = rightDown;
		if (rightDown)
		{
			Environment::instance()->getMouse(0)->fireDownEvent(Mouse::BUTTON_RIGHT,1);
		}
		else
		{
			Environment::instance()->getMouse(0)->fireUpEvent(Mouse::BUTTON_RIGHT);
		}
	}
  else if (gLastMouseMiddleDown!=middleDown)
	{
		gLastMouseMiddleDown = middleDown;
		if (middleDown)
		{
			Environment::instance()->getMouse(0)->fireDownEvent(Mouse::BUTTON_MIDDLE,1);
		}
		else
		{
			Environment::instance()->getMouse(0)->fireUpEvent(Mouse::BUTTON_MIDDLE);
		}
	}
	else if (wheelDelta!=0)
	{
		Environment::instance()->getMouse(0)->fireWheelEvent(wheelDelta);
	}
}

LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, bool* pbNoFurtherProcessing, void* pUserContext)
{
	switch (uMsg)
	{
	case WM_MOVE:
	case WM_MOVING:
	case WM_WINDOWPOSCHANGING:
	case WM_WINDOWPOSCHANGED:
	case WM_GETMINMAXINFO:
	case WM_NCPAINT:
	case WM_ERASEBKGND:
	case WM_PAINT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
	case WM_ACTIVATEAPP:
	case WM_NCACTIVATE:
	case WM_IME_SETCONTEXT:
	case WM_IME_NOTIFY:
	case WM_NCHITTEST:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
		break;
	case WM_SETCURSOR:
		break;
	case WM_ACTIVATE:
		/*
		switch (wParam)
		{
		case WA_INACTIVE:
			envDebugLog("window deactivated\n");
			break;
		case WA_ACTIVE:
		case WA_CLICKACTIVE:
			envDebugLog("window activated\n");
			break;
		}
		*/
		break;
	case WM_SETFOCUS:
		if (pUserContext!=NULL)
		{
			((Game*)pUserContext)->focusGained();
		}
		break;
	case WM_KILLFOCUS:
		if (pUserContext!=NULL)
		{
			((Game*)pUserContext)->focusLost();
		}
		break;
	case WM_QUIT:
		break;
	case WM_CLOSE:
		OBoy::Environment::instance()->stopMainLoop();
		break;
	case WM_SYSCOMMAND:
		/*
		if (wParam==HTLEFT ||
			wParam==HTRIGHT||
			wParam==HTTOP ||
			wParam==HTTOPLEFT||
			wParam==HTTOPRIGHT ||
			wParam==HTBOTTOM ||
			wParam==HTBOTTOMLEFT ||
			wParam==HTBOTTOMRIGHT)
		*/
		if (!OBoy::Environment::instance()->isWindowResizable())
		{
			if (wParam==0xf001 || // left
				wParam==0xf002 || // right
				wParam==0xf003 || // top
				wParam==0xf004 || // top left
				wParam==0xf005 || // top right
				wParam==0xf006 || // bottom
				wParam==0xf007 || // bottom left
				wParam==0xf008)   // bottom right
			{
				*pbNoFurtherProcessing = TRUE;
			}
		}
//		envDebugLog("WM_SYSCOMMAND: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	case WM_ENTERSIZEMOVE:
//		envDebugLog("WM_ENTERSIZEMOVE: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	case WM_NCLBUTTONDOWN:
		if (wParam==HTZOOM)
		{
			*pbNoFurtherProcessing = TRUE;
		}
		break;
	case WM_NCLBUTTONDBLCLK:
		*pbNoFurtherProcessing = TRUE;
//		envDebugLog("WM_NCLBUTTONDBLCLK: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	case WM_SIZING:
		*pbNoFurtherProcessing = TRUE;
//		envDebugLog("WM_SIZING: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	case WM_SIZE:
//		envDebugLog("WM_SIZE: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	case WM_NCCALCSIZE:
//		envDebugLog("WM_NCCALCSIZE: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	default:
//		envDebugLog("MsgProc: uMsg=0x%x wParam=0x%x lParam=0x%x\n",uMsg,wParam,lParam);
		break;
	}
    return 0;
}

HRESULT CALLBACK onCreateDevice(IDirect3DDevice9* d3dDevice, const D3DSURFACE_DESC* backBufferSurfaceDesc, void* userContext )
{
//	envDebugLog("onCreateDevice (windowed=%d w=%d h=%d)\n",DXUTIsWindowed(),backBufferSurfaceDesc->Width,backBufferSurfaceDesc->Height);
    return S_OK;
}

void CALLBACK onDestroyDevice(void* userContext )
{
//	envDebugLog("onDestroyDevice\n");
}

void CALLBACK onLostDevice(void* userContext)
{
//	envDebugLog("onLostDevice (windowed=%d)\n",DXUTIsWindowed());
	LinuxGLInterface *inter = (LinuxGLInterface*)userContext;
	inter->handleLostDevice();
//	DXUTGetD3D9Device()->Reset(&mPresentationParameters);
}

HRESULT CALLBACK onResetDevice(IDirect3DDevice9* d3dDevice, const D3DSURFACE_DESC* backBufferSurfaceDesc, void* userContext)
{
	assert(d3dDevice==DXUTGetD3D9Device());
//	envDebugLog("onResetDevice (windowed=%d w=%d h=%d)\n",DXUTIsWindowed(),backBufferSurfaceDesc->Width,backBufferSurfaceDesc->Height);
	LinuxGLInterface *inter = (LinuxGLInterface*)userContext;

	inter->handleResetDevice();
    return S_OK;
}
#endif
LinuxGLInterface::LinuxGLInterface(Game *game, int width, int height, const char *title, bool windowed, unsigned int refreshRate)
{
	// reset some members:
	mRendering = false;

	// remember the game:
	mGame = game;

  // initialize SDL's subsystems - in this case, only video:
  SDL_Init(SDL_INIT_VIDEO);

	// set up the cursor
  SDL_ShowCursor(SDL_DISABLE);

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
    flags |= SDL_FULLSCREEN;
    bitsPerPixel = DEFAULT_BPP;
	}
  else
  {
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    bitsPerPixel = info->vfmt->BitsPerPixel;
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

  // create device:
	mScreen = SDL_SetVideoMode(width, height, bitsPerPixel, flags);

  // initialize gl:
	initGL();

  // initialize Devil:
	initIL();

  // generate buffer object names to be
  // used for drawing subrects of images:
	glGenBuffers(1, &mImageVertices);
  glGenBuffers(1, &mImageIndices);

	// set the window title:
	mTitle = title;
	SDL_WM_SetCaption(mTitle.c_str(), NULL);

	// clearing params:
	mClearZ = PROJECTION_Z_FAR;
  mClearColor.red = 0;
  mClearColor.green = 0;
  mClearColor.blue = 0;
  mClearColor.alpha = 0;
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

  glClearColor(mClearColor.red, mClearColor.green, mClearColor.blue, mClearColor.alpha);

  glClearDepth(1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// let the rendering begin...
	float w = (float)getWidth();
	float h = (float)getHeight();
	float w2 = w/2;
	float h2 = h/2;

	GLUStextfile vertexSource;

	GLUStextfile fragmentSource;

	// load the source of the vertex shader.
	glusLoadTextFile("../shader/vertex.vs", &vertexSource);

	// load the source of the fragment shader.
	glusLoadTextFile("../shader/fragment.fs", &fragmentSource);

  // build and ...
	glusBuildProgram(&mProgram, (const GLUSchar**)&vertexSource.text, 0, (const GLUSchar**)&fragmentSource.text);

	// destroy the text resource
	glusDestroyTextFile(&vertexSource);

	// destroy the text resource
	glusDestroyTextFile(&fragmentSource);



  // set the viewport
  glViewport(0, 0, w, h);

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

	// set some default state stuff:
#if 0
  setCapability(GL_ALPHA_TEST, true);
  setAlphaRef(1);
  setAlphaFunc(?);
  setBlendFunc(GL_SRC_ALPHA,GL_SRC_ALPHA);
	setBlendFunc(GL_DST_ALPHA,GL_ONE_MINUS_DST_ALPHA);
  setCapability(GL_BLEND, true);
#endif
	return true;
}

void LinuxGLInterface::endScene()
{
	// reset the rendering flag:
	mRendering = false;
}

void LinuxGLInterface::drawImage(GLuint tex)
{
	// make sure beginScene was called:
	assert(mRendering);

  // activate array usage:
	glEnableVertexAttribArray(vertexPositionAttrib);
	glEnableVertexAttribArray(vertexColorAttrib);
  glEnableVertexAttribArray(texCoordAttrib);

  // bind to image's vertex buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glVertexAttribPointer(vertexPositionAttrib, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 8, (float *) NULL + (0)) ;
  glVertexAttribPointer(vertexColorAttrib, 3, GL_FLOAT, GL_FALSE, sizeof (float) * 8, (float *) NULL + (3)) ;
  glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, sizeof (float) * 8, (float *) NULL + (6)) ;

  // bind to image's index buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);

	// set texture:
  glBindTexture(GL_TEXTURE_2D, tex);
  assertSuccess("glBindTexture");

	// render from vertex buffer:
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  // deactivate array usage:
  glDisableVertexAttribArray (vertexPositionAttrib);
  glDisableVertexAttribArray (vertexColorAttrib);
  glDisableVertexAttribArray (texCoordAttrib);
}

void LinuxGLInterface::drawImage(LinuxImage *image, unsigned long color, float z)
{
	drawImage(image, color, z, 0, 0, image->getWidth(), image->getHeight());
}

void LinuxGLInterface::drawImage(LinuxImage *image, unsigned long color, float z, int x, int y, int w, int h)
{
	if (image->getTexture()==NULL)
	{
		envDebugLog("WARNING: trying to draw image with NULL texture (%s)\n",image->getPath().c_str());
		return;
	}
#if 0
	// update the subrect vertex buffer values:
  D3DSURFACE_DESC textureInfo;
	HRESULT hr = image->getTexture()->GetLevelDesc(0,&textureInfo);
	assert(!FAILED(hr));
#endif

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

  glColor vcolor = parseColor(color);

  BoyVertex vertexData[] = 
	{
		{minX, minY, z, vcolor.red, vcolor.green, vcolor.blue, minU, minV}, // top left
		{maxX, minY, z, vcolor.red, vcolor.green, vcolor.blue, maxU, minV}, // top right
		{minX, maxY, z, vcolor.red, vcolor.green, vcolor.blue, minU, maxV}, // bottom left
		{maxX, maxY, z, vcolor.red, vcolor.green, vcolor.blue, maxU, maxV}  // bottom right
	};

  GLuint indices[] = { 0, 1, 2, 3 };

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// draw the image:
	drawImage(image->getTexture());
}

void LinuxGLInterface::drawRect(int x, int y, int w, int h, float z, unsigned long color)
{
	float minX = (float)x;
	float minY = (float)y;
	float maxX = minX + w;
	float maxY = minY + h;

  glColor vcolor = parseColor(color);

	BoyVertex vertexData[] = 
	{
		{minX, minY, z, vcolor.red, vcolor.green, vcolor.blue, 0, 0}, // top left
		{maxX, minY, z, vcolor.red, vcolor.green, vcolor.blue, 0, 0}, // top right
		{minX, maxY, z, vcolor.red, vcolor.green, vcolor.blue, 0, 0}, // bottom left
		{maxX, maxY, z, vcolor.red, vcolor.green, vcolor.blue, 0, 0}  // bottom right
	};

  GLuint indices[] = { 0, 1, 2, 3 };

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// draw the image:
	drawImage(NULL);
}

void LinuxGLInterface::drawCircle(int x, int y, float radius, int delta, unsigned long color)
{
	// make sure beginScene was called:
	assert(mRendering);

  int numVertex = 360/delta+1;
  int angle = 0, idx = 0;

  BoyVertex *vertexData;
  GLuint *indices;

  vertexData = new BoyVertex[numVertex];

  indices = new GLuint[numVertex];

  glColor vcolor = parseColor(color);

  while (angle <= 360)
  {
	  vertexData[idx].x = (float)x + radius*cos(deg2rad(angle));
	  vertexData[idx].y = (float)y + radius*sin(deg2rad(angle));
	  vertexData[idx].z = 0;
	  vertexData[idx].red = vcolor.red;
    vertexData[idx].green = vcolor.green;
    vertexData[idx].blue = vcolor.blue;
    indices[idx] = idx;
    angle += delta;
    ++idx;
  }

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // bind to image's vertex buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), 0);
  glColorPointer(3, GL_FLOAT, 8 * sizeof(float), ((float*)NULL + (3)));

  // bind to image's index buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);

  // activate array usage:
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

	// render from vertex buffer:
  glDrawElements(GL_LINE_STRIP, numVertex, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  // deactivate array usage:
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);

  delete[] vertexData;

  delete[] indices;
}

void LinuxGLInterface::drawSphere(LinuxSphere *sphere, GLuint tex)
{
	// make sure beginScene was called:
	assert(mRendering);

	// set texture:
  glBindTexture(GL_TEXTURE_2D, tex);
  assertSuccess("glBindTexture");

  // copy the vertex data into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glBufferData(GL_ARRAY_BUFFER, sphere->mNumVertices*4*sizeof(float), sphere->mVertices, GL_STATIC_DRAW);

  // copy the normals into the buffer:
  glBindBuffer(GL_ARRAY_BUFFER, g_normals);
  glBufferData(GL_ARRAY_BUFFER, sphere->mNumVertices*3*sizeof(float), sphere->mNormals, GL_STATIC_DRAW);

  // copy the indices into the buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphere->mNumIndices*sizeof(unsigned int), sphere->mIndices, GL_STATIC_DRAW);

  // bind to image's vertex buffer:
  glBindBuffer(GL_ARRAY_BUFFER, mImageVertices);
  glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), 0);
  glColorPointer(3, GL_FLOAT, 8 * sizeof(float), ((float*)NULL + (3)));

  // bind to image's index buffer:
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mImageIndices);

  // activate array usage:
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);

	// render from vertex buffer:
  glDrawElements(GL_LINE_STRIP, numVertex, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  // deactivate array usage:
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
}

	// render from vertex buffer:
  glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
  assertSuccess("glDrawElements");

  // deactivate array usage:
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void LinuxGLInterface::drawSphere(LinuxSphere *sphere, DWORD color, float z)
{
  Image *img = sphere->getImage();

  if (img == NULL)
  {
  	// draw the sphere without texture:
    drawSphere(sphere, NULL);
    return;
  }

  LinuxImage *image = dynamic_cast<LinuxImage*>(img);
  // if texture not loaded
  if (image->getTexture()==NULL)
	{
    // draw the sphere without texture:
		drawSphere(sphere, NULL);
		return;
	}

	// draw the sphere with texture:
	drawSphere(sphere, image->getTexture());
}

void LinuxGLInterface::drawTriStrip(LinuxTriStrip *strip)
{
	// make sure beginScene was called:
	assert(mRendering);

	// create a vertex buffer:
	IDirect3DVertexBuffer9 *vb = createVertexBuffer(strip->mVertexCount);

	// lock the vertex buffer:
	void *vbData = NULL;
	HRESULT hr = vb->Lock(0, 0, &vbData, 0);
	handleError(hr);

	// copy the data into the buffer:
	int byteCount = sizeof(BoyVertex) * strip->mVertexCount;
	memcpy(vbData, strip->mVerts, byteCount);

	// unlock it:
	vb->Unlock();

	// bind to tristrip's vertex buffer:
	hr = DXUTGetD3D9Device()->SetStreamSource(0, vb, 0, sizeof(BoyVertex));
	if(FAILED(hr)) return;

	// set texture to NULL:
	hr = DXUTGetD3D9Device()->SetTexture(0,NULL);
	if(FAILED(hr)) return;

	// render from vertex buffer:
	hr = DXUTGetD3D9Device()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, strip->mVertexCount-2);
  if(FAILED(hr)) return;

	// release the vertex buffer:
	vb->Release();
}

void LinuxGLInterface::drawLineStrip(LinuxLineStrip *strip)
{
	// make sure beginScene was called:
	assert(mRendering);

	// create a vertex buffer:
	IDirect3DVertexBuffer9 *vb = createVertexBuffer(strip->mVertexCount);

	// lock the vertex buffer:
	void *vbData = NULL;
	HRESULT hr = vb->Lock(0, 0, &vbData, 0);
	handleError(hr);

	// copy the data into the buffer:
	int byteCount = sizeof(BoyVertex) * strip->mVertexCount;
	memcpy(vbData, strip->mVerts, byteCount);

	// unlock it:
	vb->Unlock();

	// bind to linestrip's vertex buffer:
	hr = DXUTGetD3D9Device()->SetStreamSource(0, vb, 0, sizeof(BoyVertex));
	if(FAILED(hr)) return;

	// set texture to NULL:
	hr = DXUTGetD3D9Device()->SetTexture(0,NULL);
	if(FAILED(hr)) return;

	// render from vertex buffer:
	hr = DXUTGetD3D9Device()->DrawPrimitive(D3DPT_LINESTRIP, 0, strip->mVertexCount-1);
  if(FAILED(hr)) return;

	// release the vertex buffer:
	vb->Release();
}

void LinuxGLInterface::drawLine(int x0, int y0, int x1, int y1, Color color)
{
  glColor vcolor = parseColor(color);

	BoyVertex verts[2];
	verts[0].x = (float)x0;
	verts[0].y = (float)y0;
	verts[0].z = 0;
	verts[0].u = 0;
	verts[0].v = 0;
	verts[0].red = vcolor.red;
  verts[0].green = vcolor.green;
  verts[0].blue = vcolor.blue;
	verts[1].x = (float)x1;
	verts[1].y = (float)y1;
	verts[1].z = 0;
	verts[1].u = 0;
	verts[1].v = 0;
	verts[1].red = vcolor.red;
  verts[1].green = vcolor.green;
  verts[1].blue = vcolor.blue;

	// make sure beginScene was called:
	assert(mRendering);

	// create a vertex buffer:
	IDirect3DVertexBuffer9 *vb = createVertexBuffer(2);

	// lock the vertex buffer:
	void *vbData = NULL;
	HRESULT hr = vb->Lock(0, 0, &vbData, 0);
	handleError(hr);

	// copy the data into the buffer:
	int byteCount = sizeof(BoyVertex) * 2;
	memcpy(vbData, verts, byteCount);

	// unlock it:
	vb->Unlock();

	// bind to tristrip's vertex buffer:
	hr = DXUTGetD3D9Device()->SetStreamSource(0, vb, 0, sizeof(BoyVertex));
	if(FAILED(hr)) return;

	// set texture to NULL:
	hr = DXUTGetD3D9Device()->SetTexture(0,NULL);
	if(FAILED(hr)) return;

	// render from vertex buffer:
	hr = DXUTGetD3D9Device()->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	if(FAILED(hr)) return;

	// release the vertex buffer:
	vb->Release();
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

IDirect3DVertexBuffer9 *LinuxGLInterface::createVertexBuffer(int numVerts)
{
	// create the vertex buffer:
	IDirect3DVertexBuffer9 *vb;
	int byteCount = sizeof(BoyVertex) * numVerts;
	HRESULT hr = DXUTGetD3D9Device()->CreateVertexBuffer(
		byteCount,
		D3DUSAGE_WRITEONLY,
		BOYFVF,
		D3DPOOL_MANAGED,
		&vb, 
		NULL);
	if(FAILED(hr)) return NULL;

	// return it:
	return vb;
}

void LinuxGLInterface::initGL()
{
	// init GLEW
  glewExperimental = GL_TRUE;
  glewInit();

  // only continue if OpenGL 3.2 is supported
	if (!glewIsSupported("GL_VERSION_3_2"))
	{
		printf("OpenGL 3.2 not supported.");
		return;
	}

#if 0
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &mMaxTextureSize);

	// set world / view matrices to identity:
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
#endif

	GLUStextfile vertexSource;

	GLUStextfile fragmentSource;

	// load the source of the vertex shader
	glusLoadTextFile("../shaders/Vertex.vs", &vertexSource);

	// load the source of the fragment shader
	glusLoadTextFile("../shaders/Fragment.fs", &fragmentSource);

	// build and ...
	glusBuildProgram(&mProgram, (const GLUSchar**)&vertexSource.text, 0, (const GLUSchar**)&fragmentSource.text);

  // destroy the text resource
	glusDestroyTextFile(&vertexSource);

	// destroy the text resource
	glusDestroyTextFile(&fragmentSource);

  mProjectionLocation = glGetUniformLocation(mProgram.program, "projectionMatrix");

	mModelViewLocation = glGetUniformLocation(mProgram.program, "modelViewMatrix");

	mTextureLocation = glGetUniformLocation(mProgram.program, "firstTexture");

	mVertexLocation = glGetAttribLocation(mProgram.program, "vertex");

	mNormalLocation = glGetAttribLocation(mProgram.program, "normal");

	mTexCoordLocation = glGetAttribLocation(mProgram.program, "texCoord");

  // install the program object as part of current rendering state
  glUseProgram(mProgram.program);

  // calculate the projection matrix and set it
  glusLoadIdentityf(mProjection);
  glUniformMatrix4fv(mProjectionLocation, 1, GL_FALSE, mProjection);

  // calculate the modelview matrix and set it
  glusLoadIdentityf(mModelView);
  glUniformMatrix4fv(mModelViewLocation, 1, GL_FALSE, mModelView);

  // turn off lighting:
  //glDisable(GL_LIGHTING);

	// set up texture blending parameters:
#if 0
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  hr = DXUTGetD3D9Device()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_TEXTURE);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_DIFFUSE);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
	if(FAILED(hr)) return;
	hr = DXUTGetD3D9Device()->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
	if(FAILED(hr)) return;
#endif
}

void LinuxGLInterface::initIL()
{
	// Devil initialization
	ilInit();

	// upper left corner
	ilOriginFunc(IL_ORIGIN_UPPER_LEFT);
	ilEnable(IL_ORIGIN_SET);

	ilEnable(IL_TYPE_SET);
	ilTypeFunc(IL_UNSIGNED_BYTE);
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

boold LinuxGLInterface::isEnabled(int state)
{
  bool enabled;
  enabled = glIsEnabled(state);
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
  bool enabled;
  glGetBooleanv(GL_DEPTH_WRITEMASK, &enabled);
  assertSuccess("glGetBooleanv");
  return enabled;
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

const GLubyte* string;
  if (verbose) {
    string = glGetString(GL_VENDOR);
    std::cout << "Vendor: " << string << std::endl;
    string = glGetString(GL_RENDERER);
    std::cout << "Renderer: " << string << std::endl;
    string = glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << string << std::endl;
    if (filtered_) {
      string = glGetString(GL_SHADING_LANGUAGE_VERSION);
      std::cout << "GLSL Version: " << string << std::endl;
    }
  }
  return OK;
}

void LinuxGLInterface::dumpInfo(std::ofstream &file)
{
  file << "Vendor: " << glGetString(GL_VENDOR) << "\n";
  file << "Vendor: " << glGetString(GL_VENDOR) << "\n";
  file << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
}

void LinuxGLInterface::handleLostDevice()
{
	mVertexBuffer->Release();
	ResourceManager *rm = Environment::instance()->getResourceManager();
	if (rm!=NULL)
	{
		printf("handleDeviceLost(): calling rm->destroyResources()... ");
		rm->destroyResources(false);
		printf("done\n");
	}
}

void LinuxGLInterface::handleResetDevice()
{
	// persist the fullscreen setting:
	OBoy::Environment *env = OBoy::Environment::instance();
	OBoy::PersistenceLayer *pl = env->getPersistenceLayer();
	bool fullscreen = env->isFullScreen();
	pl->putString("fullscreen",fullscreen?"true":"false",true);

	mVertexBuffer = createVertexBuffer(4);
	ResourceManager *rm = Environment::instance()->getResourceManager();
	if (rm!=NULL)
	{
		printf("handleResetDevice(): calling rm->initResources()... ");
		rm->initResources(false);
		printf("done\n");
	}
	initD3D();

	// notify the game of the device reset:
	mGame->windowResized(0,0,DXUTGetWindowWidth(),DXUTGetWindowHeight());
}
