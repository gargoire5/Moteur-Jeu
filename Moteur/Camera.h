#pragma once
#include "Incl.h"
#include "Component.h"

class Camera : public Component
{
public:
	static const int ID = 2;

	virtual int GetID() {
		return ID;
	}
	void Init();
	void Update()override;

	UploadBuffer<CamConstants>* GetConstBufferCam();
	XMFLOAT4X4* GetProj();

	float yaw = 0;
	float pitch = 0;

private:
	XMFLOAT4X4 _mProj = MathHelper::Identity4x4();
	UploadBuffer<CamConstants>* _DXCamCB = nullptr;

};

