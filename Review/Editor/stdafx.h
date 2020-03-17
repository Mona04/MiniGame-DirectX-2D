#pragma once

//Framework
#include "Framework.h"
#pragma comment(lib, "Framework.lib")

#include "Framework/Core/Window.h"

//ImGui 
#include "ImGui/Source/imgui.h"
#include "ImGui/Source/imgui_internal.h"
#include "./ImGui/Source/imgui_stdlib.h"

#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include "ImGui/ImGuizmo.h"

//Helper
#include "Helper/IconProvider.h"
#include "Helper/ExtraHelper.h"
#include "Helper/DragAndDrop.h"
#include "Helper/Widget_Helper.h"

//Tool
#include "Tool/ToolScript.h"