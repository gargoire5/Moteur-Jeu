#pragma once
#include "Component.h"
#include "Incl.h"

using namespace DirectX;

class Mesh : public Component
{
protected:

	struct Vertex //1 point 
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

	struct VertexTriangles // 3points = un triangle
	{
		Vertex v1;
		Vertex v2;
		Vertex v3;
	};

	// App resources.
	D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

public:

	void Init();
	void setComponent(ID3D12Device* meshDevice);
};