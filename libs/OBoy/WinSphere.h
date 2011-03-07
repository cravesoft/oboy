#pragma once

#include "d3d9.h"
#include "Sphere.h"
#include "WinD3DInterface.h"

namespace OBoy
{
  #define MESHFVF D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1
  struct MeshVertex
  {
	  float x, y, z; // position
    float nx, ny, nz; // normal
	  DWORD color;
	  float u, v; // texture coords
  };

	class WinSphere : public Sphere
	{
	public:

		WinSphere(float radius, unsigned int numSlices, unsigned int numStacks);
		virtual ~WinSphere();

		virtual void setColor(OBoyLib::Color color);

    virtual bool build();

	public:

    ID3DXMesh *mSphereMesh;

	};
};
