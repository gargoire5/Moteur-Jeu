#include "Mesh.h"

Mesh::Mesh()
{}

void Mesh::UpLoadMesh(ID3D12Device* DXDevice, ID3D12GraphicsCommandList* DXCommandList, std::array<Vertex, 8> vertices, std::array<std::uint16_t, 36> indices)
{
	_iVbByteSize = (UINT)vertices.size() * sizeof(Vertex);
	_iIbByteSize = (UINT)indices.size() * sizeof(std::uint16_t);

	D3DCreateBlob(_iVbByteSize, &_DXVertexBufferCPU);
	CopyMemory(_DXVertexBufferCPU->GetBufferPointer(), vertices.data(), _iVbByteSize);

	D3DCreateBlob(_iIbByteSize, &_DXIndexBufferCPU);
	CopyMemory(_DXIndexBufferCPU->GetBufferPointer(), indices.data(), _iIbByteSize);

	_DXVertexBufferGPU = d3dUtil::CreateDefaultBuffer(DXDevice, DXCommandList, vertices.data(), _iVbByteSize, _DXVertexBufferUploader);

	_DXIndexBufferGPU = d3dUtil::CreateDefaultBuffer(DXDevice, DXCommandList, indices.data(), _iIbByteSize, _DXIndexBufferUploader);

	_iVertexByteStride = sizeof(Vertex);
	_iVertexBufferByteSize = _iVbByteSize;
	_DXIndexFormat = DXGI_FORMAT_R16_UINT;
	_iIndexBufferByteSize = _iIbByteSize;

	SubmeshGeometry submesh;
	submesh.IndexCount = (UINT)indices.size();
	submesh.StartIndexLocation = 0;
	submesh.BaseVertexLocation = 0;

	_DrawArgs["c"] = submesh;
}