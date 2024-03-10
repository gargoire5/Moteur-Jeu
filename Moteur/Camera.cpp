#include "Engine.h"
#include "Camera.h"

void Camera::Init()
{
	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	_DXCamCB = new UploadBuffer<CamConstants>(DXDevice, 1, true);

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, static_cast<float>(1280) / 720, 1.0f, 1000.0f);
	XMStoreFloat4x4(&_mProj, P);
}

void Camera::Update()
{
	XMMATRIX mView = XMLoadFloat4x4(&_pEntity->GetTransform()->matrix);
	XMMATRIX mProj = XMLoadFloat4x4(&_mProj);
	XMMATRIX mViewProj = mView * mProj;

	CamConstants CamConstants;
	XMStoreFloat4x4(&CamConstants.ViewProj, XMMatrixTranspose(mViewProj));
	_DXCamCB->CopyData(0, CamConstants);
}

UploadBuffer<CamConstants>* Camera::GetConstBufferCam()
{
	return _DXCamCB;
}

XMFLOAT4X4* Camera::GetProj()
{
	return &_mProj;
}

void Camera::PreRender()
{
	_pShader->PreDraw();
}
void Camera::Render()
{
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();

	D3D12_GPU_VIRTUAL_ADDRESS GpuAddr = _DXCamCB->GetVirtualAddr();

	DXCommandList->SetGraphicsRootConstantBufferView(1, GpuAddr);
}
