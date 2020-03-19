#pragma once
#pragma warning(disable : 4506)
#pragma warning(disable : 4005)


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             
#define NOMINMAX

//Macro Definition
#define SAFE_DELETE(p)			{if(p){ delete p; p = nullptr; }} 
#define SAFE_DELETE_ARRAY(p)	{if(p){ delete[] (p); (p) = nullptr; }}
#define SAFE_RELEASE(p)			{if(p){ p->Release(); p = nullptr; }}

typedef unsigned int uint;
typedef unsigned long ulong;
typedef struct int2 {
	int2(int x, int y)
	{
		this->x = x; 
		this->y = y;
	}
	int x;
	int y;
};

#define NULL_STRING "N/A"
#define FONT_NANUM "NanumGothicBold"

#undef BINARYMODE

//Direct X
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
//#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

//FMOD
#include <FMOD/fmod.hpp>
#include <FMOD/fmod_errors.h>
#pragma comment(lib, "fmod_vc.lib")

//FreeImage
#pragma comment(lib, "FreeImage.lib")

//FreeType
#pragma comment(lib, "freetype.lib")

//AngelScript
#ifdef NDEBUG
#pragma comment(lib, "angelscript_release.lib")
#else
#pragma comment(lib, "angelscript.lib")
#endif

//Window
#include <Windows.h>
#include <assert.h>

//STL
#include <functional>
#include <vector>
#include <chrono>
#include <map>
#include <deque>
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include <mutex>

//Utilit/
#include "Framework/Utility/FileStream.h"
#include "Framework/Utility/FileSystem.h"
#include "Framework/Utility/Math.h"
#include "Framework/Utility/Xml.h"
#include "Framework/Utility/GeometryGenerator.h"
#include "Framework/Utility/GUIDGenerator.h"
#include "Framework/Utility/Tree.h"

//Math
#include "Framework/Math/Vector2.h"
#include "Framework/Math/Vector3.h"
#include "Framework/Math/Vector4.h"
#include "Framework/Math/Quaternion.h"
#include "Framework/Math/Matrix.h"
#include "Framework/Math/Color4.h"

//Basic Struct
#include "Framework/Core/Window.h"
#include "Framework/Core/Setting.h"
#include "Framework/Core/Context.h"
#include "Framework/Core/EventSystem.h"

//Data
#include "Framework/Data/Data_Mob.h"
#include "Framework/Data/Data_Skill.h"
#include "Framework/Data/Data_Item.h"
#include "Framework/Data/Data_Field.h"
#include "Framework/Data/Data_Portal.h"
#include "Framework/Data/Data_Dialog.h"
#include "Framework/Data/Data_Inventory.h"
#include "Framework/Data/Data_Spawn.h"
#include "Framework/Data/Data_Save.h"

//Log
#include "Framework/Log/Log.h"

//Shader
#include "Framework/Shader/Shader.h"

//Subsystem
#include "Framework/Core/Subsystem/Function/Input.h"
#include "Framework/Core/Subsystem/Function/Thread.h"
#include "Framework/Core/Subsystem/Function/Timer.h"
#include "Framework/Core/Subsystem/Function/Audio.h"
#include "Framework/Core/Subsystem/Managers/ResourceManager.h"
#include "Framework/Core/Subsystem/Managers/SceneManager.h"
#include "Framework/Core/Subsystem/Managers/UIManager.h"
#include "Framework/Core/Subsystem/Managers/ScriptManager.h"
#include "Framework/Core/Subsystem/Managers/DataManager.h"
#include "Framework/Core/Subsystem/Managers/PhysicsManager.h"
#include "Framework/Core/Subsystem/Render/Renderer.h"
#include "Framework/Core/Subsystem/Render/Graphics.h"
#include "Framework/Core/Subsystem/InGame/DialogManager.h"
#include "Framework/Core/Subsystem/InGame/InventoryManager.h"
#include "Framework/Core/Subsystem/InGame/GameManager.h"
#include "Framework/Core/Subsystem/InGame/MouseManager.h"
#include "Framework/Core/Subsystem/InGame/MonsterManager.h"
#include "Framework/Core/Subsystem/Ingame/ExtraManager.h"

//D3D11
#include "Framework/Core/D3D11/BasicData/Config.h"
#include "Framework/Core/D3D11/BasicData/Vertex.h"
#include "Framework/Core/D3D11/BasicData/Geometry.h"
#include "Framework/Core/D3D11/IAStage/IndexBuffer.h"
#include "Framework/Core/D3D11/IAStage/InputLayout.h"
#include "Framework/Core/D3D11/IAStage/VertexBuffer.h"
#include "Framework/Core/D3D11/OMStage/BlendState.h"
#include "Framework/Core/D3D11/OMStage/DepthStencilState.h"
#include "Framework/Core/D3D11/OMStage/RenderTexture.h"
#include "Framework/Core/D3D11/RSStage/RasterizerState.h"
#include "Framework/Core/D3D11/ShaderStage/ConstantBuffer.h"
#include "Framework/Core/D3D11/ShaderStage/PixelShader.h"
#include "Framework/Core/D3D11/ShaderStage/VertexShader.h"
#include "Framework/Core/D3D11/ShaderStage/SamplerState.h"

//Resource
#include "Framework/Resource/Mesh.h"
#include "Framework/Resource/Material.h"
#include "Framework/Resource/Texture.h"
#include "Framework/Resource/Animation.h"
#include "Framework/Resource/AudioClip.h"
#include "Framework/Resource/Script.h"
#include "Framework/Resource/Importer/FontImporter.h"
#include "Framework/Resource/Importer/ImageImporter.h"

//SceneComponent
#include "Framework/Scene/Component/Collide/Boundbox.h"
#include "Framework/Scene/Component/Renderable.h"
#include "Framework/Scene/Component/Transform.h"
#include "Framework/Scene/Component/Animator.h"
#include "Framework/Scene/Component/AudioSource.h"
#include "Framework/Scene/Component/Scripter.h"
#include "Framework/Scene/Component/RigidBody.h"
#include "Framework/Scene/Component/Controller.h"

//Scene
#include "Framework/Scene/Camera.h"
#include "Framework/Scene/Actor.h"
#include "Framework/Scene/Scene.h"

//UI
#include "Framework/UI/Component/Component/UI_Component_Frame.h"
#include "Framework/UI/UIHelper/ProgressReport.h"
#include "Framework/UI/Component/ProgressBar.h"
#include "Framework/UI/Component/Box.h"
#include "Framework/UI/Component/Inventory.h"
#include "Framework/UI/Component/ToolTip.h"
#include "Framework/UI/Component/Evolution.h"
#include "Framework/UI/Component/SaveLoad.h"
#include "Framework/UI/Component/VerticalList.h"
#include "Framework/UI/UI.h"

//World
#include "Framework/World/WorldGenerator.h"




