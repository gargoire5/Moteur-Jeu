#pragma once
#include "Component.h"
#include "Incl.h"

using namespace DirectX;
struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};
class Mesh
{
public:
	Mesh();

	void UpLoadMesh(std::array<Vertex, 8> vertices, std::array<std::uint16_t, 36> indices);

	D3D12_VERTEX_BUFFER_VIEW Mesh::VertexBufferView()const;
	D3D12_INDEX_BUFFER_VIEW Mesh::IndexBufferView()const;

	ID3DBlob* _DXVertexBufferCPU = nullptr;
	ID3DBlob* _DXIndexBufferCPU = nullptr;

	ID3D12Resource* _DXVertexBufferGPU = nullptr;
	ID3D12Resource* _DXIndexBufferGPU = nullptr;

	ID3D12Resource* _DXVertexBufferUploader = nullptr;
	ID3D12Resource* _DXIndexBufferUploader = nullptr;

	// Data about the buffers.
	UINT _iVertexByteStride = 0;
	UINT _iVertexBufferByteSize = 0;
	DXGI_FORMAT _DXIndexFormat = DXGI_FORMAT_R16_UINT;
	UINT _iIndexBufferByteSize = 0;

	UINT _iIndexCount = 0;

private:
	UINT _iVbByteSize = 0;
	UINT _iIbByteSize = 0;
};

