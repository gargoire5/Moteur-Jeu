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

	void UpLoadMesh(ID3D12Device* DXDevice, ID3D12GraphicsCommandList* DXCommandList, std::array<Vertex, 8> vertices, std::array<std::uint16_t, 36> indices);

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

	std::unordered_map<std::string, SubmeshGeometry> _DrawArgs;

private:
	UINT _iVbByteSize;
	UINT _iIbByteSize;
};

