#include "WinSphere.h"

#include "DXUT.h"
#include <assert.h>

using namespace OBoy;

#include "OBoyLib/CrtDbgNew.h"

WinSphere::WinSphere(float radius, int numSlices, int numStacks) : Sphere(radius, numSlices, numStacks)
{
  ID3DXMesh *tempSphereMesh;

	// create a mesh containing a sphere:
  HRESULT hr = D3DXCreateSphere(DXUTGetD3D9Device(), radius, numSlices, numStacks, &tempSphereMesh, NULL);
  if(FAILED(hr)) return;

  hr = tempSphereMesh->CloneMeshFVF(0, MESHFVF, DXUTGetD3D9Device(), &mSphereMesh);

  // finished with the original mesh, release it
  tempSphereMesh->Release();

  // lock the vertex buffer
  MeshVertex *verts;
  if (SUCCEEDED(mSphereMesh->LockVertexBuffer(0,(void **) &verts)))
  {
    // get vertex count
    int numVerts = mSphereMesh->GetNumVertices();

    // loop through the vertices
    for (int i=0; i<numVerts; i++)
    {
      // calculate texture coordinates
      verts->u=asinf(verts->nx)/D3DX_PI+0.5f;
      verts->v=asinf(verts->ny)/D3DX_PI+0.5f;
      // set color to white
      verts->color=0xffffffff;

      // go to next vertex
      verts++;
    }

    // unlock the vertex buffer
    mSphereMesh->UnlockVertexBuffer();
  }
}

WinSphere::~WinSphere()
{
  // release the mesh object:
	mSphereMesh->Release();
}

void WinSphere::setColor(Color color)
{
  ID3DXMesh *tempSphereMesh;

  mSphereMesh->CloneMeshFVF( 0, MESHFVF, DXUTGetD3D9Device(), &tempSphereMesh );

  // release the previous sphere mesh
  mSphereMesh->Release();

  // create a vertex buffer:
  IDirect3DVertexBuffer9 *vb;
  HRESULT hr = tempSphereMesh->GetVertexBuffer(&vb);
  if(FAILED(hr)) return;

  int vertexCount = tempSphereMesh->GetNumVertices();

	// lock the vertex buffer:
  MeshVertex *verts;
  hr = vb->Lock(0, 0, (void**)&verts, 0);
	if(FAILED(hr)) return;

	for (int i=0 ; i<vertexCount ; i++)
		verts[i].color = (D3DCOLOR)color;

	// unlock it:
	vb->Unlock();

  // release the vertex buffer:
  vb->Release();

  tempSphereMesh->CloneMeshFVF( 0, MESHFVF, DXUTGetD3D9Device(), &mSphereMesh );

  // release the temporary mesh
  tempSphereMesh->Release();
}
