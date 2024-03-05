#include "Mesh.h"
#include "Engine.h"
#include "Graphics.h"

Mesh::Mesh()
{}

void Mesh::UpLoadMesh(std::array<Vertex, 8> vertices, std::array<std::uint16_t, 36> indices)
{
	_iVbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	_iIbByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();

	_DXVertexBufferGPU = d3dUtil::CreateDefaultBuffer(DXDevice, DXCommandList, vertices.data(), _iVbByteSize, _DXVertexBufferUploader);
	_DXIndexBufferGPU = d3dUtil::CreateDefaultBuffer(DXDevice, DXCommandList, indices.data(), _iIbByteSize, _DXIndexBufferUploader);

	_iVertexByteStride = sizeof(Vertex);
	_iVertexBufferByteSize = _iVbByteSize;
	_DXIndexFormat = DXGI_FORMAT_R16_UINT;
	_iIndexBufferByteSize = _iIbByteSize;
	
	_iIndexCount = (UINT)indices.size();
}

D3D12_VERTEX_BUFFER_VIEW Mesh::VertexBufferView()const
{
	D3D12_VERTEX_BUFFER_VIEW vbv;
	vbv.BufferLocation = _DXVertexBufferGPU->GetGPUVirtualAddress();
	vbv.StrideInBytes = _iVertexByteStride;
	vbv.SizeInBytes = _iVertexBufferByteSize;

	return vbv;
}

D3D12_INDEX_BUFFER_VIEW Mesh::IndexBufferView()const
{
	D3D12_INDEX_BUFFER_VIEW ibv;
	ibv.BufferLocation = _DXIndexBufferGPU->GetGPUVirtualAddress();
	ibv.Format = _DXIndexFormat;
	ibv.SizeInBytes = _iIndexBufferByteSize;

	return ibv;
}