#pragma once
#include "Incl.h"
#include "Component.h"
#include "Shader.h"
#include "Graphics.h"

class Camera : public Component
{
public:
	static const int ID = 2;

	virtual int GetID() {
		return ID;
	}
	void Init();
	void UpdateCam();
	XMFLOAT4X4 GetProj();
	void RenderMesh();

	
private:
	XMFLOAT4X4 _mProj = MathHelper::Identity4x4();

	UploadBuffer<CamConstants>* _DXCamCB = nullptr;
	Transform* _pTransform;
};

