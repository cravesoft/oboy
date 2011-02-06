#pragma once

#include "d3d9.h"
#include "Cube.h"
#include "WinD3DInterface.h"

namespace oboy
{
	class WinCube : public Cube
	{
	public:

		WinCube(float halfExtent);
		virtual ~WinCube();

		virtual void setColor(oboylib::Color color);

    virtual bool build();

	public:

    ID3DXMesh *mCubeMesh;

	};
};
