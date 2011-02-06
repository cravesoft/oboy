#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include "oboylib/Vector2.h"
#include "oboylib/Vector3.h"

namespace oboy
{
	class LinuxShape
	{
	public:

    LinuxShape() { mIndexBufferId = 0; mVertexBufferId = 0; };
    virtual ~LinuxShape() { destroy(); };

    void destroy();

    virtual void draw() = 0;

    bool build();

  protected:

    void draw(GLuint tex, GLenum mode);

	protected:

    std::vector<oboylib::Vector3>	mVertices;
    std::vector<GLubyte> mColors;
	  std::vector<oboylib::Vector3>	mNormals;
	  std::vector<oboylib::Vector3>	mTangents;
	  std::vector<oboylib::Vector2>	mTexCoords;
    std::vector<unsigned int>	mIndices;

	  GLsizeiptr mSizeVertices;
	  GLsizeiptr mSizeNormals;
    GLsizeiptr mSizeColors;
	  GLsizeiptr mSizeTexCoords;
	  GLsizeiptr mSizeTangents;
    GLsizeiptr mSizeIndices;

    GLuint mVertexBufferId;
    GLuint mIndexBufferId;

	};
};