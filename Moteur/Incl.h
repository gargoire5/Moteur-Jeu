#pragma once

// Link necessary d3d12 libraries.
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "winmm.lib")

#include <windows.h>

#include <dxgi1_6.h>
#include <d3d12.h>
#include <stdexcept>
#include <D3Dcompiler.h>
#include "Source/d3dx12.h"
#include <DirectXMath.h>
#include <DirectXColors.h>

#include <string>
#include <wrl.h>
#include <shellapi.h>
#include <iostream>
#include <vector>
#include <cassert>