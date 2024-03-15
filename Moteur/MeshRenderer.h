#pragma once
#include "Incl.h"
#include "Shader.h"
#include "Component.h"

class Mesh;

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
	void PreRender()override;
	void Render()override;
	void Update();
	void SetTexture2D(Texture2D* pTexture);

private:
	Mesh* _pMeshToRender;
	UploadBuffer<ObjectConstants>* _DXObjectCB = nullptr;
	Texture2D* _pTexture;
};