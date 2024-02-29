#pragma once
#include "Incl.h"
class Graphics
{
public:
	Graphics();
	void InitWindow(HINSTANCE hInstance);
	void InitDX();
	
private:
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	float _fWindowWidth;
	float _fWindowHeight;

	HWND _hWindow;

	IDXGIFactory4* _DXFactory;
	ID3D12Device* _DXDevice;

	ID3D12Fence* _DXFence;
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
	ID3D12Resource* _DXSwapChainBuffer[2];

	D3D12_RESOURCE_DESC _DXDepthStencilDesc;
	D3D12_CLEAR_VALUE _DXOptClear;
	ID3D12Resource* _DXDepthStencilBuffer;

	D3D12_VIEWPORT _DXViewPort;
	tagRECT _ScissorRect;	
};

