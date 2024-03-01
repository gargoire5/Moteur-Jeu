#include "Graphics.h"

Graphics::Graphics()
{
	_fWindowWidth = 100.f;
	_fWindowHeight = 100.f;
}

void Graphics::InitWindow(HINSTANCE hInstance)
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"Window";
	RegisterClassEx(&windowClass);

	_hWindow = CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, nullptr, nullptr, hInstance, NULL);
	ShowWindow(_hWindow, SW_NORMAL);
}

void Graphics::InitDX()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#if defined(DEBUG) || defined(_DEBUG) 
	// Enable the D3D12 debug layer.
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		ID3D12Debug* debugController;
		assert(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))== S_OK && "error create debugInterface");
		debugController->EnableDebugLayer();
	}
#endif

	assert(CreateDXGIFactory1(IID_PPV_ARGS(&_DXFactory))==S_OK && "error create Factory");
	HRESULT hardwareResult = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_DXDevice));

	if (FAILED(hardwareResult))
	{
		IDXGIAdapter* pWarpAdapter;
		assert(_DXFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)) == S_OK && "EnumWarpAdapter error");
		assert(D3D12CreateDevice(pWarpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_DXDevice)) == S_OK && "create divice error");
	}

	assert(_DXDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_DXFence)) == S_OK && "create fence error");

	_iRtvDescriptorSize = _DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	_iDsvDescriptorSize = _DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

	_DXQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_DXQualityLevels.SampleCount = 4;
	_DXQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	_DXQualityLevels.NumQualityLevels = 0;
	_DXDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &_DXQualityLevels, sizeof(_DXQualityLevels));
	assert(_DXQualityLevels.NumQualityLevels > 0 && "Unexpected MSAA quality level.");

	_DXCommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	_DXCommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	assert(_DXDevice->CreateCommandQueue(&_DXCommandQueueDesc, IID_PPV_ARGS(&_DXCommandQueue)) == S_OK && "create Command Queue error");
	assert(_DXDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_DXCommandAllocator)) == S_OK && "create Command Allocator error");
	assert(_DXDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _DXCommandAllocator, nullptr, IID_PPV_ARGS(&_DXCommandList)) == S_OK && "create Command List error");
	_DXCommandList->Close(); //close = etat

	_DXSwapChainDESC.BufferDesc.Width = 1280;
	_DXSwapChainDESC.BufferDesc.Height = 720;
	_DXSwapChainDESC.BufferDesc.RefreshRate.Denominator = 1;
	_DXSwapChainDESC.BufferDesc.RefreshRate.Numerator = 60;
	_DXSwapChainDESC.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_DXSwapChainDESC.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	_DXSwapChainDESC.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	_DXSwapChainDESC.SampleDesc.Count = 1;
	_DXSwapChainDESC.SampleDesc.Quality = 0;
	_DXSwapChainDESC.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	_DXSwapChainDESC.BufferCount = 2;
	_DXSwapChainDESC.OutputWindow = _hWindow;
	_DXSwapChainDESC.Windowed = true;
	_DXSwapChainDESC.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	_DXSwapChainDESC.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; _DXSwapChainDESC;

	assert(_DXFactory->CreateSwapChain(_DXCommandQueue, &_DXSwapChainDESC, &_DXSwapChain) == S_OK && "create swap chain error");

	_DXRtvHeapDesc.NumDescriptors = 2;
	_DXRtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	_DXRtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	_DXRtvHeapDesc.NodeMask = 0;
	assert(_DXDevice->CreateDescriptorHeap(&_DXRtvHeapDesc, IID_PPV_ARGS(&_DXRtvHeapDescriptor)) == S_OK && "create rtvDescriptorHeap error");

	_DXDsvHeapDesc.NumDescriptors = 1;
	_DXDsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	_DXDsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	_DXDsvHeapDesc.NodeMask = 0;
	assert(_DXDevice->CreateDescriptorHeap(&_DXDsvHeapDesc, IID_PPV_ARGS(&_DXDsvHeapDescriptor)) == S_OK && "create dsvDescriptorHeap error");

	_DXSwapChain->ResizeBuffers(2, 1280, 720, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	_DXSwapChain->GetBuffer(0, IID_PPV_ARGS(&_DXSwapChainBuffer[0]));
	_DXSwapChain->GetBuffer(1, IID_PPV_ARGS(&_DXSwapChainBuffer[1]));
	_DXDevice->CreateRenderTargetView(_DXSwapChainBuffer[_iCurrBackBuffer], nullptr, _DXRtvHeapDescriptor->GetCPUDescriptorHandleForHeapStart());

	_DXDepthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	_DXDepthStencilDesc.Alignment = 0;
	_DXDepthStencilDesc.Width = 1280;
	_DXDepthStencilDesc.Height = 720;
	_DXDepthStencilDesc.DepthOrArraySize = 1;
	_DXDepthStencilDesc.MipLevels = 1;
	_DXDepthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;
	_DXDepthStencilDesc.SampleDesc.Count = 1;
	_DXDepthStencilDesc.SampleDesc.Quality = 0;
	_DXDepthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	_DXDepthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	_DXOptClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	_DXOptClear.DepthStencil.Depth = 1.0f;
	_DXOptClear.DepthStencil.Stencil = 0;

	assert(_DXDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),D3D12_HEAP_FLAG_NONE,&_DXDepthStencilDesc,D3D12_RESOURCE_STATE_COMMON,&_DXOptClear,IID_PPV_ARGS(&_DXDepthStencilBuffer)) == S_OK && "error CreateCommittedResource");
	_DXDevice->CreateDepthStencilView(_DXDepthStencilBuffer, nullptr, _DXDsvHeapDescriptor->GetCPUDescriptorHandleForHeapStart());
	_DXCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_DXDepthStencilBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	_DXViewPort.TopLeftX = 0.0f;
	_DXViewPort.TopLeftY = 0.0f;
	_DXViewPort.Width = 1280;
	_DXViewPort.Height = 720;
	_DXViewPort.MinDepth = 0.0f;
	_DXViewPort.MaxDepth = 1.0f;	
	_DXCommandList->RSSetViewports(1, &_DXViewPort);

	_ScissorRect = { 0, 0, 1280 / 2, 720 / 2 };
	_DXCommandList->RSSetScissorRects(1, &_ScissorRect);
}

LRESULT CALLBACK Graphics::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Save the DXSample* passed in to CreateWindow.
		LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
	}
	return 0;

	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

void Graphics::Draw()
{

}