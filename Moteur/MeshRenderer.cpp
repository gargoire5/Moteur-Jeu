#include "MeshRenderer.h"



MeshRenderer::MeshRenderer()
{
	_pMeshToRender = nullptr;
}

void MeshRenderer::SetMesh(Mesh* pMesh)
{
	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	_DXObjectCB = new UploadBuffer<ObjectConstants>(DXDevice, 1, true);
	_pTransform = new Transform();

	_pMeshToRender = pMesh;
}

void MeshRenderer::PreRender()
{
	_pShader->PreDraw();
}

void MeshRenderer::Render()
{
	_pShader->Draw(_pMeshToRender, _DXObjectCB);
}

void MeshRenderer::UpdateWorldPos()
{
	ObjectConstants objConstants;
	objConstants.WorldMatrix = _pTransform->matrix;
	_DXObjectCB->CopyData(0, objConstants);
}

void MeshRenderer::SetPosition(float x, float y, float z)
{
	_pTransform = new Transform();
	_pTransform->fPos = { x,y,z };
	_pTransform->qRot = { 0,0,0,0 };
	_pTransform->fRight = { 0,0,0 };
	_pTransform->fUp = { 0,0,0 };

}
