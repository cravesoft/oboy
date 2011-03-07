#include "LinuxShape.h"
#include "Environment.h"

#include <assert.h>

using namespace OBoy;

void LinuxShape::destroy()
{
	glDeleteBuffers(1, &mVertexBufferId);
	mVertexBufferId = 0;
  glDeleteBuffers(1, &mIndexBufferId);
  mIndexBufferId = 0;

  mVertices.clear();
	mNormals.clear();
  mColors.clear();
	mTangents.clear();
	mTexCoords.clear();
}

bool LinuxShape::build()
{
  if (mVertexBufferId)
    glDeleteBuffers(1, &mVertexBufferId);
	glGenBuffers(1, &mVertexBufferId);
	assert(mVertexBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

	if (!mVertices.empty())
  {
		mSizeVertices = mVertices.size()*sizeof(OBoyLib::Vector3);
  }
	else
  {
    envDebugLog("no vertex data\n");
		return false;
	}

	if (!mNormals.empty()) 
		mSizeNormals	= mNormals.size()*sizeof(OBoyLib::Vector3);
  else
    mSizeNormals = 0;

	if (!mColors.empty()) 
		mSizeColors	= mColors.size()*sizeof(GLubyte);
  else
    mSizeColors = 0;

	if (!mTexCoords.empty()) 
		mSizeTexCoords = mTexCoords.size()*sizeof(OBoyLib::Vector2);
  else
    mSizeTexCoords = 0;
	
	if (!mTangents.empty())
		mSizeTangents = mTangents.size()*sizeof(OBoyLib::Vector3);
  else
    mSizeTangents = 0;
	
	// link the vertex buffer
	glBufferData(GL_ARRAY_BUFFER, mSizeVertices + mSizeNormals + mSizeColors + mSizeTexCoords + mSizeTangents, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER_ARB, 0,	mSizeVertices, (const GLvoid*)(&mVertices[0]));

  if (mNormals.size())
    glBufferSubData(GL_ARRAY_BUFFER_ARB, mSizeVertices,	mSizeNormals, (const GLvoid*)(&mNormals[0]));

  if (mColors.size())
    glBufferSubData(GL_ARRAY_BUFFER_ARB, mSizeVertices + mSizeNormals,	mSizeColors, (const GLvoid*)(&mColors[0]));

	if (mTexCoords.size())
		glBufferSubData(GL_ARRAY_BUFFER_ARB, mSizeVertices + mSizeNormals + mSizeColors, mSizeTexCoords, (const GLvoid*)(&mTexCoords[0]));

	if (mTangents.size())
		glBufferSubData(GL_ARRAY_BUFFER_ARB, mSizeVertices + mSizeNormals + mSizeColors + mSizeTexCoords,	mSizeTangents, (const GLvoid*)(&mTangents[0]));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

  if (!mIndices.empty())
  {
    if (mIndexBufferId)
      glDeleteBuffers(1, &mIndexBufferId);
	  glGenBuffers(1, &mIndexBufferId);
	  assert(mIndexBufferId);

    mSizeIndices = mIndices.size()*sizeof(int);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);

    // link the index buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mSizeIndices, (const GLvoid*)(&mIndices[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  return true;
}

void LinuxShape::draw(GLuint tex, GLenum mode)
{
	glEnableClientState(GL_VERTEX_ARRAY);
  
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);

	glVertexPointer(3, GL_FLOAT, 0, 0);
  
  // normals
	if(!mNormals.empty()) 
	{
    glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, (void*)(mSizeVertices));
	}

  // colors
	if(!mColors.empty()) 
	{
    glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, 0, (void*)(mSizeVertices+mSizeNormals));
	}

  // texture coordinates
	if (!mTexCoords.empty()) 
	{
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glClientActiveTexture(GL_TEXTURE0);
		glTexCoordPointer(2, GL_FLOAT, 0, (void*)(mSizeVertices+mSizeNormals+mSizeColors));
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
	}

	// tangents
	if (!mTangents.empty()) 
	{
		glClientActiveTexture(GL_TEXTURE1);
		glTexCoordPointer(3, GL_FLOAT, 0, (void*)(mSizeVertices+mSizeNormals+mSizeColors+mSizeTexCoords));
	}

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);

  glDrawElements(mode, (GLsizei)mIndices.size(), GL_UNSIGNED_INT, 0);

  glClientActiveTexture(GL_TEXTURE0);

  if (!mTexCoords.empty()) 
	{
    glBindTexture(GL_TEXTURE_2D,0);
	  glDisable(GL_TEXTURE_2D);
  }

	glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  if (!mTexCoords.empty()) 
	{
	  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  }
  if(!mColors.empty()) 
	{
    glDisableClientState(GL_COLOR_ARRAY);
  }
  if(!mNormals.empty()) 
	{
	  glDisableClientState(GL_NORMAL_ARRAY);
  }
  if (!mTexCoords.empty()) 
	{
	  glDisableClientState(GL_VERTEX_ARRAY); 
  }
}