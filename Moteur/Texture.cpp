#include "Texture.h"
Texture2D::Texture2D()
{
	Microsoft::WRL::ComPtr<ID3D12Resource> _Resource = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> _UploadHeap = nullptr;
}

void Texture2D::LoadTexture(int index, std::string Name, std::wstring Filename, ID3D12GraphicsCommandList* CommandList, ID3D12Device* device, ID3D12DescriptorHeap* SrvHeap, UINT TypeHeap)
{
	_sName = Name;
	_sFilename = Filename;
	ThrowIfFailed(DirectX::CreateDDSTextureFromFile12(device, CommandList, _sFilename.c_str(), _Resource, _UploadHeap));



	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(SrvHeap->GetCPUDescriptorHandleForHeapStart());
	hDescriptor.Offset(index, TypeHeap);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = _Resource->GetDesc().Format;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = _Resource->GetDesc().MipLevels;
	srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	device->CreateShaderResourceView(_Resource.Get(), &srvDesc, hDescriptor);

	//CD3DX12_GPU_DESCRIPTOR_HANDLE md(SrvHeap->GetGPUDescriptorHandleForHeapStart());
	//md.Offset(index , TypeHeap);

}
