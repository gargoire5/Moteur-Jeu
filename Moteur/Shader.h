#pragma once
#include  "Incl.h"
#include "Engine.h"

class Shader
{

public:
	Shader();
	~Shader();

	void Initialize();
	void Purge();
	void Draw(Mesh* pMeshToRender, Buffer* pBuffer);

private:
	ID3DBlob* serializedRootSig = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* _VertexShader = nullptr;
	ID3DBlob* _PixelShader = nullptr;
	ID3D12RootSignature* _DXRootSignature = nullptr;
	ID3D12PipelineState* _DXPSO = nullptr;

	std::vector<D3D12_INPUT_ELEMENT_DESC> _vInputLayout;
};