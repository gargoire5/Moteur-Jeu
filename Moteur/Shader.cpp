#include "Shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
	Purge();
}

void Shader::Initialize()
{

	DXDevice = Engine::Instance()->GetGraphics()->GetDevice();

	CD3DX12_ROOT_PARAMETER slotRootParameter[1];

	// Create a single descriptor table of CBVs.
	CD3DX12_DESCRIPTOR_RANGE cbvTable;
	cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	slotRootParameter[0].InitAsDescriptorTable(1, &cbvTable);

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	// create a root signature with a single slot which points to a descriptor range consisting of a single constant buffer
	HRESULT hr = D3D12SerializeRootSignature(&rootSigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &serializedRootSig, &errorBlob);

	if (errorBlob != nullptr)
	{
		::OutputDebugStringA((char*)errorBlob->GetBufferPointer());
	}
	assert(hr == S_OK && "error blob");
	assert(DXDevice->CreateRootSignature(0, serializedRootSig->GetBufferPointer(), serializedRootSig->GetBufferSize(), IID_PPV_ARGS(&_DXRootSignature)) == S_OK && "error create rootsignature");
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//--------------------Build Shader-----------------------------------------------------------------------------------------------------------------//
	_VertexShader = d3dUtil::CompileShader(L"../Moteur\\Shaders\\color.hlsl", nullptr, "VS", "vs_5_0");
	_PixelShader = d3dUtil::CompileShader(L"../Moteur\\Shaders\\color.hlsl", nullptr, "PS", "ps_5_0");

	_vInputLayout =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
	};
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//--------------------Build PSO-----------------------------------------------------------------------------------------------------------------//
	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { _vInputLayout.data(), (UINT)_vInputLayout.size() };
	psoDesc.pRootSignature = _DXRootSignature;
	psoDesc.VS =
	{
		reinterpret_cast<BYTE*>(_VertexShader->GetBufferPointer()),
		_VertexShader->GetBufferSize()
	};
	psoDesc.PS =
	{
		reinterpret_cast<BYTE*>(_PixelShader->GetBufferPointer()),
		_PixelShader->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.SampleDesc.Quality = 0;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	assert(DXDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_DXPSO)) == S_OK && "error create pso");

}

void Shader::Purge()
{
	if (serializedRootSig) {
		serializedRootSig->Release();
	}
	if (errorBlob) {
		errorBlob->Release();
	}
}

void Shader::Draw()
{


}
