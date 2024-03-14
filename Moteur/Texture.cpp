#include "Texture.h"
#include "Engine.h"
Texture2D::Texture2D()
{
	Microsoft::WRL::ComPtr<ID3D12Resource> _Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> _UploadHeap = nullptr;
}

void Texture2D::LoadTexture(int index, std::string Name, std::wstring Filename)
{

	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();
	ID3D12DescriptorHeap* DXSrvHeap = Engine::Instance()->GetGraphics()->GetSrvHeap();
	UINT TypeHeap = DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	_sName = Name;
	_sFilename = Filename;
	HRESULT hr = DirectX::CreateDDSTextureFromFile12(DXDevice, DXCommandList, _sFilename.c_str(), _Resource, _UploadHeap);
	assert(hr == S_OK);
	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(DXSrvHeap->GetCPUDescriptorHandleForHeapStart());
	hDescriptor.Offset(index, TypeHeap);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = _Resource->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = _Resource->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	DXDevice->CreateShaderResourceView(_Resource.Get(), &srvDesc, hDescriptor);

	_md = CD3DX12_GPU_DESCRIPTOR_HANDLE(DXSrvHeap->GetGPUDescriptorHandleForHeapStart());
	_md.Offset(index , TypeHeap);


}
