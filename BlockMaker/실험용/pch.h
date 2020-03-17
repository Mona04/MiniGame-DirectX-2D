#ifndef PCH_H
#define PCH_H

//DEFINE
#define SAFE_DELETE(p) if(p){ delete p; p = nullptr;}

//FreeImage
#pragma comment(lib, "FreeImaged.lib")

//direct 
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>

//std
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <queue>
#include <mutex>
#include <functional>
#include <thread>

#include <assert.h>
#include <stack>
#include <cstddef>

#include "Util/FileStream.h"
#include "Util/FileSystem.h"
#include "Util/Timer.h"
#include "Util/Math_Helper.h"

#include "Data/Enum.h"
#endif PCH_H
