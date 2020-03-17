#include "stdafx.h"
#include "ToolScript.h"
#include "../ImGui/TextEditor.h"

const std::string ToolScript::BaseScriptCode =
"class NewScript\n\
{\n\
\tNewScript(Actor @inActor)\n\
\t{\n\
\t}\n\
\n\
\tvoid Start()\n\
\t{\n\
\t}\n\
\n\
\tvoid Update()\n\
\t{\n\
\t}\n\
}";

namespace _TextEdit
{
	TextEditor editor;
	TextEditor::ErrorMarkers markers;
}

void ToolScript::Initialize(Context* context)
{
	this->context = context;
	this->path = "";
	this->isVisible = false;
	SetScriptLanguage(ScriptLanguage::AngelScript);
}

void ToolScript::Render()
{
	if (!isVisible)
		return;

	TextEditor::Coordinates cursorPos = _TextEdit::editor.GetCursorPosition();

	ImGui::SetWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
	ImGui::Begin("ScriptTool", &isVisible, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar);
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New")) CreateNewScript();
				if (ImGui::MenuItem("Open")) {}
				if (ImGui::MenuItem("Save")) {}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				bool isReadOnly = _TextEdit::editor.IsReadOnly();
				if (ImGui::MenuItem("ReadOnly Mode", nullptr, &isReadOnly))  // 누르면 반전
					_TextEdit::editor.SetReadOnly(isReadOnly);

				ImGui::Separator();

				if (ImGui::MenuItem("Undo", "Ctrl + Z", nullptr, !isReadOnly && _TextEdit::editor.CanUndo()))
					_TextEdit::editor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl + Y", nullptr, !isReadOnly && _TextEdit::editor.CanRedo()))
					_TextEdit::editor.Redo();
				if (ImGui::MenuItem("Copy", "Ctrl + C", nullptr, !isReadOnly && _TextEdit::editor.CanRedo()))
					_TextEdit::editor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl + X", nullptr, !isReadOnly && _TextEdit::editor.CanRedo()))
					_TextEdit::editor.Cut();
				if (ImGui::MenuItem("Paste", "Ctrl + V", nullptr, !isReadOnly && _TextEdit::editor.CanRedo()))
					_TextEdit::editor.Paste();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !isReadOnly && _TextEdit::editor.CanRedo()))
					_TextEdit::editor.Delete();

				ImGui::Separator();

				if (ImGui::MenuItem("Select All", "Ctrl + A", nullptr, !isReadOnly && _TextEdit::editor.CanRedo()))
					_TextEdit::editor.SelectAll();

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark"))
					_TextEdit::editor.SetPalette(_TextEdit::editor.GetDarkPalette());
				if (ImGui::MenuItem("Light"))
					_TextEdit::editor.SetPalette(_TextEdit::editor.GetLightPalette());
				if (ImGui::MenuItem("Retro Blue"))
					_TextEdit::editor.SetPalette(_TextEdit::editor.GetRetroBluePalette());

				ImGui::EndMenu();
			}

			ImGui::Text("%6d/%-6d %6d lines | %s | %s | %s | %s",
				cursorPos.mLine + 1,
				cursorPos.mColumn + 1,
				_TextEdit::editor.GetTotalLines(),
				_TextEdit::editor.IsOverwrite() ? "Ovr" : "Ins",
				_TextEdit::editor.CanUndo() ? "*" : "",
				_TextEdit::editor.GetLanguageDefinition().mName.c_str(),
				path.c_str()
			);

			ImGui::EndMenuBar();
		}
		_TextEdit::editor.Render("Script Tool");
	}
	ImGui::End();
}

void ToolScript::SetScript(const std::string& path)
{
	this->path;

	std::ifstream in(path);
	if (in.good())
	{
		std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
		_TextEdit::editor.SetText(str);
	}
}

void ToolScript::SetScriptLanguage(const ScriptLanguage& language)
{
	switch (language)
	{
	case ScriptLanguage::C:
		_TextEdit::editor.SetLanguageDefinition(TextEditor::LanguageDefinition::C());
		break;
	case ScriptLanguage::CPlusPlus:
		_TextEdit::editor.SetLanguageDefinition(TextEditor::LanguageDefinition::CPlusPlus());
		break;
	case ScriptLanguage::AngelScript:
		_TextEdit::editor.SetLanguageDefinition(TextEditor::LanguageDefinition::AngelScript());
		break;
	case ScriptLanguage::HLSL:
		_TextEdit::editor.SetLanguageDefinition(TextEditor::LanguageDefinition::HLSL());
		break;
	}

	auto language2 = TextEditor::LanguageDefinition::CPlusPlus();
	{
	    static const char* ppnames[] =
	    {
	        "NULL",
	        "PM_REMOVE",
	        "ZeroMemory",
	        "DXGI_SWAP_EFFECT_DISCARD",
	        "D3D_FEATURE_LEVEL",
	        "D3D_DRIVER_TYPE_HARDWARE",
	        "WINAPI",
	        "D3D11_SDK_VERSION",
	        "assert"
	    };
	
	    static const char* ppvalues[] =
	    {
	        "#define NULL ((void*)0)",
	        "#define PM_REMOVE (0x0001)",
	        "Microsoft's own memory zapper function\n(which is a macro actually)\nvoid ZeroMemory(\n\t[in] PVOID  Destination,\n\t[in] SIZE_T Length\n); ",
	        "enum DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD = 0",
	        "enum D3D_FEATURE_LEVEL",
	        "enum D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE  = ( D3D_DRIVER_TYPE_UNKNOWN + 1 )",
	        "#define WINAPI __stdcall",
	        "#define D3D11_SDK_VERSION (7)",
	        " #define assert(expression) (void)(                                                  \n"
	        "    (!!(expression)) ||                                                              \n"
	        "    (_wassert(_CRT_WIDE(#expression), _CRT_WIDE(__FILE__), (unsigned)(__LINE__)), 0) \n"
	        " )"
	    };
	
	    for (int i = 0; i < ARRAYSIZE(ppnames); i++)
	    {
	        TextEditor::Identifier id;
	        id.mDeclaration = ppvalues[i];
	        language2.mPreprocIdentifiers.insert(std::make_pair(std::string(ppnames[i]), id));
	    }
	
	    static const char* identifiers[] =
	    {
	        "HWND", "HRESULT", "LPRESULT","D3D11_RENDER_TARGET_VIEW_DESC", "DXGI_SWAP_CHAIN_DESC","MSG","LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
	        "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
	        "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
	        "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "TextEditor"
	    };
	
	    static const char* idecls[] =
	    {
	        "typedef HWND_* HWND", "typedef long HRESULT", "typedef long* LPRESULT", "struct D3D11_RENDER_TARGET_VIEW_DESC", "struct DXGI_SWAP_CHAIN_DESC",
	        "typedef tagMSG MSG\n * Message structure","typedef LONG_PTR LRESULT","WPARAM", "LPARAM","UINT","LPVOID",
	        "ID3D11Device", "ID3D11DeviceContext", "ID3D11Buffer", "ID3D11Buffer", "ID3D10Blob", "ID3D11VertexShader", "ID3D11InputLayout", "ID3D11Buffer",
	        "ID3D10Blob", "ID3D11PixelShader", "ID3D11SamplerState", "ID3D11ShaderResourceView", "ID3D11RasterizerState", "ID3D11BlendState", "ID3D11DepthStencilState",
	        "IDXGISwapChain", "ID3D11RenderTargetView", "ID3D11Texture2D", "class TextEditor"
	    };
	
	    for (int i = 0; i < ARRAYSIZE(identifiers); i++)
	    {
	        TextEditor::Identifier id;
	        id.mDeclaration = std::string(idecls[i]);
	        language2.mIdentifiers.insert(std::make_pair(std::string(identifiers[i]), id));
	    }
	}
	_TextEdit::editor.SetLanguageDefinition(language2);
	
	_TextEdit::markers.insert(std::make_pair(6, "ERRORRRRRRRRRRRRRRRRRRRRRRRRR!!!"));
	_TextEdit::markers.insert(std::make_pair(12, "dasfadfadfasdfdddddddddddddd!!!"));
	_TextEdit::editor.SetErrorMarkers(_TextEdit::markers);
}

void ToolScript::CreateNewScript()
{
	std::string path = "../../_Assets/Script/NewScript.as";

	std::ofstream out;
	out.open(path, std::ios::out);
	if (out.fail())
		return;

	out << BaseScriptCode;
	out.flush();
	out.close();

	SetScript(path);
}
