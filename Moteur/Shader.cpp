#include "Engine.h"
#include "Shader.h"
#include "Graphics.h"
#include "Texture.h"

Shader::Shader()
{

}

Shader::~Shader()
{
	Purge();
}

void Shader::Initialize()
{

	ID3D12Device* DXDevice = Engine::Instance()->GetGraphics()->GetDevice();
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();
	ID3D12DescriptorHeap* DXSrvHeap = Engine::Instance()->GetGraphics()->GetCbvHeap();

	Texture2D* texture = new Texture2D();
	std::string name = "bricks";
	std::wstring filename = L"../texture/bricks.dds";
	UINT TypeHeap = DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	texture->LoadTexture(TabTex.size(), name, filename, DXCommandList, DXDevice, DXSrvHeap, TypeHeap);
	TabTex.push_back(*texture);

	CD3DX12_DESCRIPTOR_RANGE texTable;
	texTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0);


	CD3DX12_ROOT_PARAMETER slotRootParameter[3];

	auto staticSamplers = GetStaticSamplers();

	// Create a single descriptor table of CBVs.
	//CD3DX12_DESCRIPTOR_RANGE cbvTable;
	//cbvTable.Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 1, 0);
	slotRootParameter[0].InitAsDescriptorTable(1, &texTable, D3D12_SHADER_VISIBILITY_PIXEL);
	slotRootParameter[1].InitAsConstantBufferView(0);
	slotRootParameter[2].InitAsConstantBufferView(1);

	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(3, slotRootParameter, (UINT)staticSamplers.size(), staticSamplers.data(),
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
		//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
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
	HRESULT hrr = DXDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&_DXPSO));
	assert( hrr== S_OK && "error create pso");

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

void Shader::PreDraw()
{
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();
	DXCommandList->SetGraphicsRootSignature(_DXRootSignature);
}

void Shader::Draw(Mesh* pMeshToRender, Buffer* pBufferObj, Buffer* pBufferCam)
{
	ID3D12GraphicsCommandList* DXCommandList = Engine::Instance()->GetGraphics()->GetCommandList();

	
	ID3D12RootSignature* pRootSignature = _DXRootSignature;

	ID3D12DescriptorHeap* _DXSrvHeap = Engine::Instance()->GetGraphics()->GetCbvHeap();
	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(_DXSrvHeap->GetGPUDescriptorHandleForHeapStart());

	//DXCommandList->SetGraphicsRootConstantBufferView(1, pBuffer->GetVirtualAddr());

	DXCommandList->SetPipelineState(_DXPSO);

	DXCommandList->IASetVertexBuffers(0, 1, &pMeshToRender->VertexBufferView());
	DXCommandList->IASetIndexBuffer(&pMeshToRender->IndexBufferView());
	DXCommandList->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//DXCommandList->SetGraphicsRootSignature(pRootSignature);//?
	DXCommandList->SetGraphicsRootDescriptorTable(0, tex);
	DXCommandList->SetGraphicsRootConstantBufferView(1, pBufferObj->GetVirtualAddr());
	DXCommandList->SetGraphicsRootConstantBufferView(2, pBufferCam->GetVirtualAddr());

	DXCommandList->DrawIndexedInstanced(pMeshToRender->_iIndexCount, 1, 0, 0, 0);
}

std::array<const CD3DX12_STATIC_SAMPLER_DESC, 6> Shader::GetStaticSamplers()
{
	// Applications usually only need a handful of samplers.  So just define them all up front
	// and keep them available as part of the root signature.  

	const CD3DX12_STATIC_SAMPLER_DESC pointWrap(
		0, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC pointClamp(
		1, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_POINT, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearWrap(
		2, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC linearClamp(
		3, // shaderRegister
		D3D12_FILTER_MIN_MAG_MIP_LINEAR, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP); // addressW

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicWrap(
		4, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_WRAP,  // addressW
		0.0f,                             // mipLODBias
		8);                               // maxAnisotropy

	const CD3DX12_STATIC_SAMPLER_DESC anisotropicClamp(
		5, // shaderRegister
		D3D12_FILTER_ANISOTROPIC, // filter
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressU
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressV
		D3D12_TEXTURE_ADDRESS_MODE_CLAMP,  // addressW
		0.0f,                              // mipLODBias
		8);                                // maxAnisotropy

	return {
		pointWrap, pointClamp,
		linearWrap, linearClamp,
		anisotropicWrap, anisotropicClamp };
}