#pragma once
#include  "Incl.h"

class Mesh;
class Texture2D;

class Shader
{
public:
	Shader();
	~Shader();

	void Initialize();
	void Purge();
	void PreDraw();
	void Draw(Mesh* pMeshToRender, Buffer* pBufferObj, Buffer* pBufferCam, Texture2D* pTexture);
	std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> GetStaticSamplers();
private:
	ID3DBlob* serializedRootSig = nullptr;
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* _VertexShader = nullptr;
	ID3DBlob* _PixelShader = nullptr;
	ID3D12RootSignature* _DXRootSignature = nullptr;
	ID3D12PipelineState* _DXPSO = nullptr;
	
	std::vector<D3D12_INPUT_ELEMENT_DESC> _vInputLayout;
};