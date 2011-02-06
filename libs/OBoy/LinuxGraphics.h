#pragma once

#include "oboylib/Rect.h"
#include "Graphics.h"
#include "TriStrip.h"
#include "LineStrip.h"
#include "Lines.h"
#include <GL/glew.h>
#include <stack>

namespace oboy
{
	class GraphicsState;
	class LinuxGLInterface;

	class LinuxGraphics : public Graphics
	{
	public:

		LinuxGraphics(LinuxGLInterface *platformInterface);
		virtual ~LinuxGraphics();

		virtual void drawImage(Image *img);
		virtual void drawImage(Image *img, int subrectX, int subrectY, int subrectW, int subrectH);

		virtual void drawLine(int x0, int y0, int x1, int y1);
    virtual void drawRect(int x0, int y0, int w, int h);
		virtual void fillRect(int x0, int y0, int w, int h);
    virtual void drawCircle(int x, int y, float radius, int delta);
		virtual void drawTriStrip(TriStrip *strip);
    virtual void drawLineStrip(LineStrip *strip);
    virtual void drawLines(Lines *lines);
    virtual void drawSphere(Sphere *sphere);
    virtual void drawCube(Cube *cube);

		virtual void scale(float x, float y);
		virtual void rotate(float angle);
		virtual void rotate(float xangle, float yangle, float zangle);
		virtual void translate(float x, float y);
		virtual void preScale(float x, float y);
		virtual void preRotate(float angle);
		virtual void preTranslate(float x, float y);

		virtual void pushTransform();
		virtual void popTransform();
		virtual int getTransformStackSize();

    void setLineWidth(float width);

		virtual void setAlpha(float alpha);
		virtual void setColor(oboylib::Color color);
		virtual void setColorizationEnabled(bool enabled);

		virtual void setZTestEnabled(bool enabled);
		virtual bool isZTestEnabled();
		virtual void setZWriteEnabled(bool enabled);
		virtual bool isZWriteEnabled();
		virtual void setZFunction(CompareFunc func);
		virtual void setZ(float z);
		virtual float getZ();

		virtual void setAlphaTestEnabled(bool enabled);
		virtual bool isAlphaTestEnabled();
		virtual void setAlphaReferenceValue(int val);
		virtual void setAlphaFunction(CompareFunc func);

		virtual void setDrawMode(DrawMode mode);

		virtual void setClipRect(int x, int y, int width, int height);

		virtual int getWidth();
		virtual int getHeight();

		virtual void setClearZ(float z);
		virtual void setClearColor(oboylib::Color color);

		void dumpInfo(std::ofstream &file);

	private:

		oboylib::Color mColor;
		bool mColorizationEnabled;

		float mZ;

    GLuint mTransformStackSize;

		LinuxGLInterface *mInterface;

	};
};

