#include "Graphics.h"
#include "Engine.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Timer.h"
#include "Input.h"
#include "Texture.h"
#include "Script.h"

using namespace DirectX;
Graphics::Graphics()
{
	_fWindowWidth = 100.f;
	_fWindowHeight = 100.f;
}

void Graphics::InitWindow()
{
	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowProc;
	windowClass.hInstance = GetModuleHandle(NULL);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName = L"Window";
	RegisterClassEx(&windowClass);

	_hWindow = CreateWindow(windowClass.lpszClassName, L"Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, _iWindowWidth, _iWindowHeight, nullptr, nullptr, GetModuleHandle(NULL), NULL);
	ShowWindow(_hWindow, SW_NORMAL);
}

void Graphics::InitDX()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

//#if defined(DEBUG) || defined(_DEBUG) 
//	// Enable the D3D12 debug layer.
//	{
//		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//		ID3D12Debug* debugController;
// 		assert(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))== S_OK && "error create debugInterface");
//		debugController->EnableDebugLayer();
//	}
//#endif

	//---------------Create Device/Factory----------------------------------------------------------------------------------------------------------------------//
	assert(CreateDXGIFactory1(IID_PPV_ARGS(&_DXFactory))==S_OK && "error create Factory");
	HRESULT hardwareResult = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_DXDevice));

	if (FAILED(hardwareResult))
	{
		IDXGIAdapter* pWarpAdapter;
		assert(_DXFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter)) == S_OK && "EnumWarpAdapter error");
		assert(D3D12CreateDevice(pWarpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&_DXDevice)) == S_OK && "create divice error");
	}
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//----------------Create Fence - GetDescriptor size---------------------------------------------------------------------------------------------------------------------//

	assert(_DXDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&_DXFence)) == S_OK && "create fence error");

	_iRtvDescriptorSize = _DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	_iDsvDescriptorSize = _DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	_iCbvSrvDescriptorSize = _DXDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//-----------------Define MSAA Quality--------------------------------------------------------------------------------------------------------------------//
	_DXQualityLevels.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	_DXQualityLevels.SampleCount = 4;
	_DXQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	_DXQualityLevels.NumQualityLevels = 0;
	_DXDevice->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &_DXQualityLevels, sizeof(_DXQualityLevels));
	assert(_DXQualityLevels.NumQualityLevels > 0 && "Unexpected MSAA quality level.");
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//----------------Create Commands System---------------------------------------------------------------------------------------------------------------------//
	_DXCommandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	_DXCommandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	assert(_DXDevice->CreateCommandQueue(&_DXCommandQueueDesc, IID_PPV_ARGS(&_DXCommandQueue)) == S_OK && "create Command Queue error");
	assert(_DXDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&_DXCommandAllocator)) == S_OK && "create Command Allocator error");
	assert(_DXDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _DXCommandAllocator, nullptr, IID_PPV_ARGS(&_DXCommandList)) == S_OK && "create Command List error");
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//-----------------Create SwapChain--------------------------------------------------------------------------------------------------------------------//
	_DXSwapChainDESC.BufferDesc.Width = _iWindowWidth;
	_DXSwapChainDESC.BufferDesc.Height = _iWindowHeight;
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
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//------------------Create Back and Front Buffers-------------------------------------------------------------------------------------------------------------------//
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

	_DXSwapChain->ResizeBuffers(2, _iWindowWidth, _iWindowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
	_DXSwapChain->GetBuffer(0, IID_PPV_ARGS(&_DXSwapChainBuffer[0]));
	_DXSwapChain->GetBuffer(1, IID_PPV_ARGS(&_DXSwapChainBuffer[1]));
	_DXDevice->CreateRenderTargetView(_DXSwapChainBuffer[_iCurrBackBuffer], nullptr, _DXRtvHeapDescriptor->GetCPUDescriptorHandleForHeapStart());
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//------------------Create Depth Buffer-------------------------------------------------------------------------------------------------------------------//
	_DXDepthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	_DXDepthStencilDesc.Alignment = 0;
	_DXDepthStencilDesc.Width = _iWindowWidth;
	_DXDepthStencilDesc.Height = _iWindowHeight;
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

	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.Texture2D.MipSlice = 0;

	assert(_DXDevice->CreateCommittedResource(&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),D3D12_HEAP_FLAG_NONE,&_DXDepthStencilDesc,D3D12_RESOURCE_STATE_COMMON,&_DXOptClear,IID_PPV_ARGS(&_DXDepthStencilBuffer)) == S_OK && "error CreateCommittedResource");
	_DXDevice->CreateDepthStencilView(_DXDepthStencilBuffer, &dsvDesc, _DXDsvHeapDescriptor->GetCPUDescriptorHandleForHeapStart());
	_DXCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_DXDepthStencilBuffer, D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//--------------------Create ViewPort---------------------------------------------------------------------------------------------------------------//
	_DXViewPort.TopLeftX = 0.0f;
	_DXViewPort.TopLeftY = 0.0f;
	_DXViewPort.Width = _iWindowWidth;
	_DXViewPort.Height = _iWindowHeight;
	_DXViewPort.MinDepth = 0.0f;
	_DXViewPort.MaxDepth = 1.0f;	
	_DXCommandList->RSSetViewports(1, &_DXViewPort);

	_DXScissorRect = { 0, 0, _iWindowWidth / 2, _iWindowHeight / 2 };
	_DXCommandList->RSSetScissorRects(1, &_DXScissorRect);
	_DXCommandList->RSSetScissorRects(1, &_DXScissorRect);
	_DXCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { _DXCommandList };
	_DXCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	//-------------------------------------------------------------------------------------------------------------------------------------//
	//-----------------Create CbvHeap--------------------------------------------------------------------------------------------------------------------//	
	//-----------------Create CbvHeap--------------------------------------------------------------------------------------------------------------------//	
	//_DXCbvHeapDesc.NumDescriptors = 1;
	//_DXCbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	//_DXCbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	//_DXCbvHeapDesc.NodeMask = 0;
	//_DXDevice->CreateDescriptorHeap(&_DXCbvHeapDesc, IID_PPV_ARGS(&_DXCbvHeap));

	_ObjectCB = std::make_unique<UploadBuffer<ObjectConstants>>(_DXDevice, 1, true);

	//-----------------Create SrvHeap--------------------------------------------------------------------------------------------------------------------//

	_DXSrvHeapDesc.NumDescriptors = 100;
	_DXSrvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	_DXSrvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	_DXSrvHeapDesc.NodeMask = 0;
	ThrowIfFailed(_DXDevice->CreateDescriptorHeap(&_DXSrvHeapDesc, IID_PPV_ARGS(&_DXSrvHeap)));

	//-------------------------------------------------------------------------------------------------------------------------------------//
	//------------------Shader Calling-------------------------------------------------------------------------------------------------------------------//
	_pShader = new Shader();
	_pShader->Initialize();
	//-------------------------------------------------------------------------------------------------------------------------------------//

	HRESULT hr = _DXCommandAllocator->Reset();
	_DXCommandList->Reset(_DXCommandAllocator, nullptr);

	Texture2D* RockTexture = new Texture2D();
	std::string name = "rock";
	std::wstring filename = L"../texture/rock.dds";
	RockTexture->LoadTexture(TabTex.size(), name, filename);
	TabTex.push_back(RockTexture);

	Texture2D* IronTexture = new Texture2D();
	name = "grass";
	//filename = L"../texture/iron.dds";
	filename = L"../texture/laser.dds";
	IronTexture->LoadTexture(TabTex.size(), name, filename);
	TabTex.push_back(IronTexture);

	_DXCommandList->Close();
	_DXCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);
	FlushCommandQueue();
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
ID3D12Resource* Graphics::GetCurrentBackBuffer()const
{
	return _DXSwapChainBuffer[_iCurrBackBuffer];
}
D3D12_CPU_DESCRIPTOR_HANDLE Graphics::GetCurrentBackBufferView()const
{
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		_DXRtvHeapDescriptor->GetCPUDescriptorHandleForHeapStart(),
		_iCurrBackBuffer,
		_iRtvDescriptorSize);
}
D3D12_CPU_DESCRIPTOR_HANDLE Graphics::GetDepthStencilView()const
{
	return _DXDsvHeapDescriptor->GetCPUDescriptorHandleForHeapStart();
}

Shader* Graphics::GetShader()
{
	return _pShader;
}

ID3D12CommandQueue* Graphics::GetCommandQueue()
{
	return _DXCommandQueue;
}

ID3D12CommandAllocator* Graphics::GetCommandAllocator()
{
	return _DXCommandAllocator;
}

Texture2D* Graphics::GetTextureList(int i)
{
	return TabTex[i];
}

ID3D12Device* Graphics::GetDevice()
{
	return _DXDevice;
}

void Graphics::Draw()
{
	// Reuse the memory associated with command recording.
	// We can only reset when the associated command lists have finished execution on the GPU.
	HRESULT hr = _DXCommandAllocator->Reset();
	assert(hr == S_OK && "Reset CommandAllocator error");

	// A command list can be reset after it has been added to the command queue via ExecuteCommandList.
	// Reusing the command list reuses memory.
	assert(_DXCommandList->Reset(_DXCommandAllocator, _DXPSO) == S_OK && "Reset CommandList");

	_DXCommandList->RSSetViewports(1, &_DXViewPort);
	_DXCommandList->RSSetScissorRects(1, &_DXScissorRect);

	// Indicate a state transition on the resource usage.
	_DXCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBuffer(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET));

	// Clear the back buffer and depth buffer.
	_DXCommandList->ClearRenderTargetView(GetCurrentBackBufferView(), DirectX::Colors::Black, 0, nullptr);
	_DXCommandList->ClearDepthStencilView(GetDepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	// Specify the buffers we are going to render to.
	_DXCommandList->OMSetRenderTargets(1, &GetCurrentBackBufferView(), true, &GetDepthStencilView());

	ID3D12DescriptorHeap* descriptorHeaps[] = { _DXSrvHeap };
	_DXCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();

	for (int i = 0; i < pEntityManager->GetEntityList().size(); i++)
	{
		std::vector<Component*> vCompoList = pEntityManager->GetEntityList()[i]->GetComponentsList();
		for (Component* pComponent : vCompoList)
		{
			pComponent->PreRender();
			pComponent->Render();
		}
	}

	// Indicate a state transition on the resource usage.
	_DXCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(GetCurrentBackBuffer(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));

	// Done recording commands.
	assert(_DXCommandList->Close() == S_OK && "error close commmand list");

	// Add the command list to the queue for execution.
	ID3D12CommandList* cmdsLists[] = { _DXCommandList };
	_DXCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// swap the back and front buffers
	assert(_DXSwapChain->Present(0, 0) == S_OK && "error present buffer");
	_iCurrBackBuffer = (_iCurrBackBuffer + 1) % _iBufferCount;

	// Wait until frame commands are complete.  This waiting is inefficient and is
	// done for simplicity.  Later we will show how to organize our rendering code
	// so we do not have to wait per frame.
	FlushCommandQueue();
}

void Graphics::FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	_iCurrentFence++;

	// Add an instruction to the command queue to set a new fence point.  Because we 
	// are on the GPU timeline, the new fence point won't be set until the GPU finishes
	// processing all the commands prior to this Signal().
	assert(_DXCommandQueue->Signal(_DXFence, _iCurrentFence) == S_OK && "error signal fence");

	// Wait until the GPU has completed commands up to this fence point.
	if (_DXFence->GetCompletedValue() < _iCurrentFence)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

		// Fire event when GPU hits current fence.  
		assert(_DXFence->SetEventOnCompletion(_iCurrentFence, eventHandle) == S_OK && "error setEventCompletion");

		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

POINT Graphics::GetWindowSize()
{
	POINT WindowPos;
	WindowPos.x = _iWindowWidth;
	WindowPos.y = _iWindowHeight;
	return WindowPos;
}

void Graphics::OnResize()
{
	assert(_DXDevice);
	assert(_DXSwapChain);
	assert(_DXCommandAllocator);

	// Flush before changing any resources.
	FlushCommandQueue();

	_DXCommandList->Reset(_DXCommandAllocator, nullptr);

	// Release the previous resources we will be recreating.
	for (int i = 0; i < _iBufferCount; ++i)
	{
		_DXSwapChainBuffer[i]->Release();
		_DXSwapChainBuffer[i] = nullptr;
	}
		
	_DXDepthStencilBuffer->Release();
	_DXDepthStencilBuffer = nullptr;

	// Resize the swap chain.
	assert(_DXSwapChain->ResizeBuffers(
		_iBufferCount,
		_iWindowWidth, _iWindowHeight,
		DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH) == S_OK && "error resize swapchain");

	_iCurrBackBuffer = 0;

	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(_DXRtvHeapDescriptor->GetCPUDescriptorHandleForHeapStart());
	for (UINT i = 0; i < _iBufferCount; i++)
	{
		assert(_DXSwapChain->GetBuffer(i, IID_PPV_ARGS(&_DXSwapChainBuffer[i])) == S_OK && "error getbuffer");
		_DXDevice->CreateRenderTargetView(_DXSwapChainBuffer[i], nullptr, rtvHeapHandle);
		rtvHeapHandle.Offset(1, _iRtvDescriptorSize);
	}

	// Create the depth/stencil buffer and view.
	D3D12_RESOURCE_DESC depthStencilDesc;
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = _iWindowWidth;
	depthStencilDesc.Height = _iWindowHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;

	// Correction 11/12/2016: SSAO chapter requires an SRV to the depth buffer to read from 
	// the depth buffer.  Therefore, because we need to create two views to the same resource:
	//   1. SRV format: DXGI_FORMAT_R24_UNORM_X8_TYPELESS
	//   2. DSV Format: DXGI_FORMAT_D24_UNORM_S8_UINT
	// we need to create the depth buffer resource with a typeless format.  
	depthStencilDesc.Format = DXGI_FORMAT_R24G8_TYPELESS;

	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	D3D12_CLEAR_VALUE optClear;
	optClear.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;
	assert(_DXDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_COMMON,
		&optClear,
		IID_PPV_ARGS(&_DXDepthStencilBuffer))==S_OK && "error create DSBuffer");

	// Create descriptor to mip level 0 of entire resource using the format of the resource.
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc;
	dsvDesc.Flags = D3D12_DSV_FLAG_NONE;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.Texture2D.MipSlice = 0;
	_DXDevice->CreateDepthStencilView(_DXDepthStencilBuffer, &dsvDesc, _DXDsvHeapDescriptor->GetCPUDescriptorHandleForHeapStart());

	// Transition the resource from its initial state to be used as a depth buffer.
	_DXCommandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(_DXDepthStencilBuffer,D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_DEPTH_WRITE));

	// Execute the resize commands.
	_DXCommandList->Close();
	ID3D12CommandList* cmdsLists[] = { _DXCommandList };
	_DXCommandQueue->ExecuteCommandLists(_countof(cmdsLists), cmdsLists);

	// Wait until resize is complete.
	FlushCommandQueue();

	// Update the viewport transform to cover the client area.
	_DXViewPort.TopLeftX = 0;
	_DXViewPort.TopLeftY = 0;
	_DXViewPort.Width = static_cast<float>(_iWindowWidth);
	_DXViewPort.Height = static_cast<float>(_iWindowHeight);
	_DXViewPort.MinDepth = 0.0f;
	_DXViewPort.MaxDepth = 1.0f;

	_DXScissorRect = { 0, 0, _iWindowWidth, _iWindowHeight };

	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();
	XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * MathHelper::Pi, static_cast<float>(_iWindowWidth) / _iWindowHeight, 1.0f, 1000.0f);
	for (int i = 0; i < pEntityManager->GetEntityList().size(); i++)
	{
		std::vector<Component*> vCompoList = pEntityManager->GetEntityList()[i]->GetComponentsList();
		for (Component* pComponent : vCompoList)
		{
			if (pComponent->GetID() == Camera::ID)
			{
				XMStoreFloat4x4(dynamic_cast<Camera*>(pComponent)->GetProj(),P);
			}
		}
	}
}

void Graphics::Update()
{
	Engine::Instance()->GetInput()->Update();
	Engine::Instance()->GetTimer()->Tick();

	EntityManager* pEntityManager = Engine::Instance()->GetEntityManager();

	for (Script* script : Engine::Instance()->GetScriptList())
	{
		script->Update();
	}
	
	for (Entity* pEntity : pEntityManager->GetEntityList())
	{
		pEntity->GetTransform()->Update_WorldMatrix();
		std::vector<Component*> vCompoList = pEntity->GetComponentsList();

		for (Component* pComponent : vCompoList)
		{
			pComponent->Update();
		}
	}
}

ID3D12GraphicsCommandList* Graphics::GetCommandList()
{
	return _DXCommandList;
}
ID3D12DescriptorHeap* Graphics::GetSrvHeap()
{
	return _DXSrvHeap;
}


