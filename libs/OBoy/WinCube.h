#pragma once

#include "d3d9.h"
#include "Cube.h"
#include "WinD3DInterface.h"

namespace OBoy
{
	class WinCube : public Cube
	{
	public:

		WinCube(float halfExtent);
		virtual ~WinCube();

		virtual void setColor(OBoyLib::Color color);

    virtual bool build();

	public:

    ID3DXMesh *mCubeMesh;

	};
};
