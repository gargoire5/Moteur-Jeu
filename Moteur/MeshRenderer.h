#pragma once
#include "Component.h"
#include "Mesh.h"

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
	void RenderMesh();
private:
	Mesh* _pMeshToRender;
	std::unique_ptr<UploadBuffer<ObjectConstants>> mObjectCB = nullptr;
};

