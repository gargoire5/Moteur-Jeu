#pragma once
#include "Incl.h"
#include "Engine.h"
#include "Component.h"
#include "Mesh.h"
#include "Shader.h"

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
	//void SetTexture(Texture* pMesh);
	void PreRender()override;
	void Render()override;
	void Update();
	void SetTexture2D(Texture2D* pTexture);
	~MeshRenderer();

private:
	Mesh* _pMeshToRender;
	//Texture*;
	UploadBuffer<ObjectConstants>* _DXObjectCB = nullptr;
	Texture2D* _pTexture;
};