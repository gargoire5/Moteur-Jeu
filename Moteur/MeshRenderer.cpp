#include "MeshRenderer.h"
#include "Engine.h"
MeshRenderer::MeshRenderer()
{
	_pMeshToRender = nullptr;
}

void MeshRenderer::SetMesh(Mesh* pMesh)
{
	_pMeshToRender = pMesh;
}

void MeshRenderer::SetBuffer()
{
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();
	DXCommandList->IASetVertexBuffers(0, 1, &_pMeshToRender->VertexBufferView());
	DXCommandList->IASetIndexBuffer(&_pMeshToRender->IndexBufferView());
	DXCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void MeshRenderer::RenderMesh()
{
	ID3D12GraphicsCommandList* _DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();
	_DXCommandList->DrawIndexedInstanced( _pMeshToRender->_iIndexCount,1, 0, 0, 0);
}
