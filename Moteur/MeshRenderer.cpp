#include "MeshRenderer.h"
#include "Camera.h"
#include "Engine.h"
#include "Entity.h"


MeshRenderer::MeshRenderer()
{
	_pMeshToRender = nullptr;
}

void MeshRenderer::SetMesh(Mesh* pMesh)
{
	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	_DXObjectCB = new UploadBuffer<ObjectConstants>(DXDevice, 1, true);

	_pMeshToRender = pMesh;
}

void MeshRenderer::PreRender()
{
	_pShader->PreDraw();
}

void MeshRenderer::Render()
{
	UploadBuffer<CamConstants>* ConstCamBuffer = _pEntity->GetCurrCam()->GetConstBufferCam();
	_pShader->Draw(_pMeshToRender, _DXObjectCB, ConstCamBuffer, _pTexture);
}

void MeshRenderer::Update()
{
	ObjectConstants objConstants;
	XMStoreFloat4x4(&objConstants.WorldMatrix, XMMatrixTranspose(XMLoadFloat4x4(&_pEntity->GetTransform()->matrix)));
	_DXObjectCB->CopyData(0, objConstants);
}

void MeshRenderer::SetTexture2D(Texture2D* pTexture)
{
	_pTexture = pTexture;
}



