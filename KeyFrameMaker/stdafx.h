#pragma once

typedef unsigned long uint;

//Direct X
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//FreeImage
#pragma comment(lib, "FreeImaged.lib")

#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

#define SAFE_DELETE(p) { if(p){ delete p; p = nullptr;}}

#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <functional>

#include <vector>
#include <string>
#include <cstddef>
#include <chrono>

#include "Core/Setting.h"
#include "Core/Context.h"

#include "Util/Log.h"
#include "Util/FileSystem.h"
#include "Util/FileStream.h"

#include "Core/Subsystem/ResourceManager.h"
