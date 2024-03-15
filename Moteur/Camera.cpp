#include "Engine.h"
#include "Camera.h"
#include "Entity.h"

void Camera::Init()
{
	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	_DXCamCB = new UploadBuffer<CamConstants>(DXDevice, 1, true);

	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, 1280.0f/720.0f, 1.0f, 1000.0f);
	XMStoreFloat4x4(&_mProj, P);
}

void Camera::Update()
{
	XMMATRIX mView = XMLoadFloat4x4(&_pEntity->GetTransform()->matrix);
	mView = XMMatrixInverse(nullptr, mView);

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

