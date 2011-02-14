#include "LinuxGraphics.h"

#include <assert.h>
#include "oboylib/OBoyUtil.h"
#include "LinuxImage.h"
#include "LinuxGLInterface.h"
#include "LinuxTriStrip.h"
#include "LinuxLineStrip.h"
#include "LinuxSphere.h"
#include "LinuxCube.h"
#include "LinuxLines.h"

using namespace oboy;

#include "oboylib/CrtDbgNew.h"

LinuxGraphics::LinuxGraphics(LinuxGLInterface *platformInterface)
{
	mInterface = platformInterface;
  /*glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();*/
  mColor = oboylib::Color();
	mColorizationEnabled = false;
  mTransformStackSize = 0;
	mZ = 0;
}

LinuxGraphics::~LinuxGraphics()
{
}

void LinuxGraphics::drawImage(Image *img)
{
	mInterface->drawImage(
		dynamic_cast<LinuxImage*>(img), 
    mColorizationEnabled ? mColor : oboylib::Color(oboylib::Color::White),
		mZ);
}

void LinuxGraphics::drawImage(Image *img, int subrectX, int subrectY, int subrectW, int subrectH)
{
	mInterface->drawImage(
		dynamic_cast<LinuxImage*>(img), 
		mColorizationEnabled ? mColor : oboylib::Color(oboylib::Color::White),
		mZ,
		subrectX,
		subrectY,
		subrectW,
		subrectH);
}

void LinuxGraphics::drawLine(int x0, int y0, int x1, int y1)
{
	mInterface->drawLine(x0,y0,x1,y1,mColor);
}

void LinuxGraphics::drawCircle(int x, int y, float radius, int delta)
{
	mInterface->drawCircle(x,y,radius,delta,mColor);
}

void LinuxGraphics::drawSphere(Sphere *sphere)
{
	mInterface->drawSphere(
		dynamic_cast<LinuxSphere*>(sphere), 
		mColorizationEnabled ? mColor : oboylib::Color(),
		mZ);
}

void LinuxGraphics::drawCube(Cube *cube)
{
	mInterface->drawCube(
		dynamic_cast<LinuxCube*>(cube), 
		mColorizationEnabled ? mColor : oboylib::Color(),
		mZ);
}

void LinuxGraphics::fillRect(int x0, int y0, int w, int h)
{
	pushTransform();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
		mInterface->drawRect(x0,y0,w,h,mZ,mColor);
	popTransform();
}

void LinuxGraphics::drawRect(int x0, int y0, int w, int h)
{
	mInterface->drawRect(x0,y0,w,h,mZ,mColor);
}

void LinuxGraphics::scale(float x, float y)
{
  glScalef(x, y, 1);
}

void LinuxGraphics::rotate(float angle)
{
  glRotatef(-angle, 0, 0, 1);
}

void LinuxGraphics::rotate(float xangle, float yangle, float zangle)
{
  glRotatef(-xangle, 1, 0, 0);
  glRotatef(-yangle, 0, 1, 0);
  glRotatef(-zangle, 0, 0, 1);
}

void LinuxGraphics::translate(float x, float y)
{
  glTranslatef(x, y, 0);
}

void LinuxGraphics::preScale(float x, float y)
{
  float xform[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, xform);
  glLoadIdentity();
  glScalef(x, y, 1.0f);
  glMultMatrixf(xform);
}

void LinuxGraphics::preRotate(float angle)
{
  float xform[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, xform);
  glLoadIdentity();
  glRotatef(-angle, 0, 0, 1);
  glMultMatrixf(xform);
}

void LinuxGraphics::preTranslate(float x, float y)
{
  float xform[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, xform);
  glLoadIdentity();
  glTranslatef(x, y, 0);
  glMultMatrixf(xform);
}

void LinuxGraphics::pushTransform()
{
  glPushMatrix();
  mTransformStackSize++;
#if 0
  glPushName(++mTransformStackSize);
#endif
}

void LinuxGraphics::popTransform()
{
  glPopMatrix();
  mTransformStackSize--;
#if 0
	glPopName();
#endif
}

int LinuxGraphics::getTransformStackSize()
{
	return mTransformStackSize;
}

void LinuxGraphics::setColor(oboylib::Color color)
{
	mColor = color;
}

void LinuxGraphics::setLineWidth(float width)
{
  glLineWidth(width);
}

void LinuxGraphics::setAlpha(float alpha)
{
#if 0
	mColor.argb &= 0x00ffffff;
	mColor |= ((int)(255.0f * alpha)) << 24;
#else
  mColor.setAlpha(alpha);
#endif
}

void LinuxGraphics::setColorizationEnabled(bool enabled)
{
	mColorizationEnabled = enabled;
}

void LinuxGraphics::setZTestEnabled(bool enabled)
{
	mInterface->setCapability(GL_DEPTH_TEST, enabled); 
}

bool LinuxGraphics::isZTestEnabled()
{
	return mInterface->isEnabled(GL_DEPTH_TEST);
}

void LinuxGraphics::setZWriteEnabled(bool enabled)
{
	mInterface->setDepthMask(enabled); 
}

bool LinuxGraphics::isZWriteEnabled()
{
	return mInterface->isDepthMaskEnabled(); 
}

void LinuxGraphics::setZ(float z)
{
	assert(z>=0 && z<=1);
	mZ = z;
}

float LinuxGraphics::getZ()
{
	return mZ;
}

void LinuxGraphics::setZFunction(CompareFunc func)
{
	GLenum zfunc;
	// TODO: this should be optimized... use a lookup array!
	switch(func)
	{
	case CMP_NEVER:
		zfunc = GL_NEVER;
		break;
	case CMP_LESS:
		zfunc = GL_LESS;
		break;
	case CMP_EQUAL:
		zfunc = GL_EQUAL;
		break;
	case CMP_LEQUAL:
		zfunc = GL_LEQUAL;
		break;
	case CMP_GREATER:
		zfunc = GL_GREATER;
		break;
	case CMP_NOTEQUAL:
		zfunc = GL_NOTEQUAL;
		break;
	case CMP_GEQUAL:
		zfunc = GL_GEQUAL;
		break;
	case CMP_ALWAYS:
		zfunc = GL_ALWAYS;
		break;
	default:
		assert(false);
	}

	mInterface->setDepthFunction(zfunc);
}

void LinuxGraphics::setDrawMode(DrawMode mode)
{
	switch (mode)
	{
	case DRAWMODE_NORMAL:
    mInterface->setBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		break;
	case DRAWMODE_ADDITIVE:
    mInterface->setBlendFunc(GL_SRC_ALPHA,GL_ONE);
		break;
	}
}

void LinuxGraphics::setAlphaTestEnabled(bool enabled)
{
	mInterface->setCapability(GL_ALPHA_TEST, enabled);
}

bool LinuxGraphics::isAlphaTestEnabled()
{
	return mInterface->isEnabled(GL_ALPHA_TEST); 
}

void LinuxGraphics::setAlphaReferenceValue(int val)
{
	mInterface->setAlphaRef(val);
}

void LinuxGraphics::setAlphaFunction(CompareFunc func)
{
	GLenum afunc;
	// TODO: this should be optimized... use a lookup array!
	switch(func)
	{
	case CMP_NEVER:
		afunc = GL_NEVER;
		break;
	case CMP_LESS:
		afunc = GL_LESS;
		break;
	case CMP_EQUAL:
		afunc = GL_EQUAL;
		break;
	case CMP_LEQUAL:
		afunc = GL_LEQUAL;
		break;
	case CMP_GREATER:
		afunc = GL_GREATER;
		break;
	case CMP_NOTEQUAL:
		afunc = GL_NOTEQUAL;
		break;
	case CMP_GEQUAL:
		afunc = GL_GEQUAL;
		break;
	case CMP_ALWAYS:
		afunc = GL_ALWAYS;
		break;
	default:
		assert(false);
	}

	mInterface->setAlphaFunc(afunc);
}

void LinuxGraphics::setClipRect(int x, int y, int width, int height)
{
	mInterface->setClipRect(x,y,width,height);
}

void LinuxGraphics::drawTriStrip(TriStrip *strip)
{
	LinuxTriStrip *s = dynamic_cast<LinuxTriStrip*>(strip);
  mInterface->drawTriStrip(s);
}

void LinuxGraphics::drawLineStrip(LineStrip *strip)
{
	LinuxLineStrip *s = dynamic_cast<LinuxLineStrip*>(strip);
  mInterface->drawLineStrip(s);
}

void LinuxGraphics::drawLines(Lines *lines)
{
	LinuxLines *s = dynamic_cast<LinuxLines*>(lines);
  mInterface->drawLines(s);
}

int LinuxGraphics::getWidth()
{
	return mInterface->getWidth();
}

int LinuxGraphics::getHeight()
{
	return mInterface->getHeight();
}

void LinuxGraphics::setClearZ(float z)
{
	mInterface->setClearZ(z);
}

void LinuxGraphics::setClearColor(oboylib::Color color)
{
	mInterface->setClearColor(color);
}

void LinuxGraphics::dumpInfo(std::ofstream &file)
{
	mInterface->dumpInfo(file);
}
