#pragma once

#include <GL/glew.h>
#include <string>
#include <vector>
#include "OBoyLib/Vector2.h"
#include "OBoyLib/Vector3.h"

namespace OBoy
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

    std::vector<OBoyLib::Vector3>	mVertices;
    std::vector<GLubyte> mColors;
	  std::vector<OBoyLib::Vector3>	mNormals;
	  std::vector<OBoyLib::Vector3>	mTangents;
	  std::vector<OBoyLib::Vector2>	mTexCoords;
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