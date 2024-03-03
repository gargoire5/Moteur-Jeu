#pragma once
#include "Incl.h"

struct ObjectConstants
{
	DirectX::XMFLOAT4X4 WorldViewProj = MathHelper::Identity4x4();
};

class Graphics
{
public:
	Graphics();
	void InitWindow();
	void InitDX();
	void OnResize();
	void Draw();

	ID3D12Resource* GetCurrentBackBuffer()const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetCurrentBackBufferView()const;
	D3D12_CPU_DESCRIPTOR_HANDLE GetDepthStencilView()const;

private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void FlushCommandQueue();

	float _fWindowWidth;
	float _fWindowHeight;

	HWND _hWindow;

	IDXGIFactory4* _DXFactory;
	ID3D12Device* _DXDevice;

	ID3D12Fence* _DXFence;
	UINT64 _iCurrentFence = 0;

	UINT _iRtvDescriptorSize;
	UINT _iDsvDescriptorSize;

	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS _DXQualityLevels;

	D3D12_COMMAND_QUEUE_DESC _DXCommandQueueDesc = {};
	ID3D12CommandQueue* _DXCommandQueue;
	ID3D12CommandAllocator* _DXCommandAllocator;
	ID3D12GraphicsCommandList* _DXCommandList;

	DXGI_SWAP_CHAIN_DESC _DXSwapChainDESC;
	IDXGISwapChain* _DXSwapChain;

	D3D12_DESCRIPTOR_HEAP_DESC _DXRtvHeapDesc;
	D3D12_DESCRIPTOR_HEAP_DESC _DXDsvHeapDesc;
	ID3D12DescriptorHeap* _DXRtvHeapDescriptor;
	ID3D12DescriptorHeap* _DXDsvHeapDescriptor;

	int _iCurrBackBuffer = 0;
	static const int _iBufferCount = 2;
	ID3D12Resource* _DXSwapChainBuffer[2];

	D3D12_RESOURCE_DESC _DXDepthStencilDesc;
	D3D12_CLEAR_VALUE _DXOptClear;
	ID3D12Resource* _DXDepthStencilBuffer;

	D3D12_VIEWPORT _DXViewPort;
	tagRECT _DXScissorRect;

	ID3D12PipelineState* _DXPSO = nullptr;

	ID3D12RootSignature* _DXRootSignature = nullptr;
	ID3D12DescriptorHeap* _DXCbvHeap = nullptr;
	UINT _iCbvSrvDescriptorSize;


	std::unique_ptr<UploadBuffer<ObjectConstants>> _ObjectCB = nullptr;

	ID3DBlob* _VertexShader = nullptr;
	ID3DBlob* _PixelShader = nullptr;

	std::vector<D3D12_INPUT_ELEMENT_DESC> _vInputLayout;

	int _iWindowWidth = 1280;
	int _iWindowHeight = 720;
};