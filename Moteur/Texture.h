#pragma once
#include "Incl.h";
using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

class Texture2D
{
public:
	Texture2D();
	void LoadTexture(int index, std::string Name, std::wstring Filename, ID3D12GraphicsCommandList* CommandList, ID3D12Device* device, ID3D12DescriptorHeap* SrvHeap, UINT TypeHeap);
private:
	std::string _sName;
	std::wstring _sFilename;
	Microsoft::WRL::ComPtr<ID3D12Resource> _Resource;
	Microsoft::WRL::ComPtr<ID3D12Resource> _UploadHeap;
};

