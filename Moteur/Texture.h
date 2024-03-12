#pragma once
#include "Incl.h";
using Microsoft::WRL::ComPtr;
using namespace DirectX;
using namespace DirectX::PackedVector;

class Texture2D
{
public:
	Texture2D();
	void LoadTexture(int index, std::string Name, std::wstring Filename);
private:
	std::string _sName;
	std::wstring _sFilename;
	Microsoft::WRL::ComPtr<ID3D12Resource> _Resource;
	Microsoft::WRL::ComPtr<ID3D12Resource> _UploadHeap;
};

