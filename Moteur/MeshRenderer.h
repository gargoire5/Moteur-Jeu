#pragma once
#include "Incl.h"
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"
#include "Graphics.h"

class MeshRenderer : public Component
{
public:
	static const int ID = 1;

public:
	MeshRenderer();
	virtual int GetID() {
		return ID;
	}
	void SetMesh(Mesh* pMesh);
	void RenderMesh(Shader* pShader);
	void UpdateWorldPos();
	void SetPosition(float x, float y, float z);
private:
	Mesh* _pMeshToRender;
	UploadBuffer<ObjectConstants>* _DXObjectCB = nullptr;
	Transform* _pTransform;
};

