#include "Mesh.h"
#include "Engine.h"
#include "Graphics.h"

Mesh::Mesh()
{
	
}

void Mesh::UpLoadMesh(Vertex* vertices, int vertexCount, std::uint16_t* indices, int indexCount)
{
	_pVertices = vertices;
	_pindices = indices;

	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();
	ID3D12CommandQueue* DXCommandQueue = Engine::Instance()->GetGraphics()->GetCommandQueue();
	ID3D12CommandAllocator* DXCommandAllocator = Engine::Instance()->GetGraphics()->GetCommandAllocator();

	HRESULT hr = DXCommandAllocator->Reset();
	assert(hr == S_OK && "Reset CommandAllocator error");

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	assert(DXCommandList->Reset(DXCommandAllocator, nullptr) == S_OK && "Reset CommandList");

	_iVbByteSize = (UINT)vertexCount * sizeof(Vertex);
	_iIbByteSize = (UINT)indexCount * sizeof(std::uint16_t);

	_DXVertexBufferGPU = d3dUtil::CreateDefaultBuffer(DXDevice, DXCommandList, vertices, _iVbByteSize, _DXVertexBufferUploader);
	_DXIndexBufferGPU = d3dUtil::CreateDefaultBuffer(DXDevice, DXCommandList, indices, _iIbByteSize, _DXIndexBufferUploader);

	_iVertexByteStride = sizeof(Vertex);
	_iVertexBufferByteSize = _iVbByteSize;
	_DXIndexFormat = DXGI_FORMAT_R16_UINT;
	_iIndexBufferByteSize = _iIbByteSize;
	
	_iIndexCount = (UINT)indexCount;
	_iVertexCount = (UINT)vertexCount;

	// Execute the resize commands.
	DXCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { DXCommandList };
	DXCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	Engine::Instance()->GetGraphics()->FlushCommandQueue();
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