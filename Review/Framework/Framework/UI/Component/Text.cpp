#include "Framework.h"
#include "Text.h"
#include "Framework/Resource/Importer/FontImporter.h"

Text::Text(Context* context)
	: IUIComponent(context)
	, text(L"")
{
	resourceManager = context->GetSubsystem<ResourceManager>();
}

Text::~Text()
{
}

void Text::Init()
{
	glyphs.fontSize = 15;
	glyphs.hintingType = HintingType::Light;
	glyphs.isForceAutoHint = false;
	glyphs.name = "test";
	glyphs.path = "../../_Assets/Font/NanumGothicBold.ttf";
	resourceManager->GetFontImporter()->LoadFromFile(glyphs);

	auto frame = AddFrame("Text");

	frame.first->SetMesh(NULL_STRING, std::to_string(frame.first->GetID()));
	frame.first->SetMaterial(NULL_STRING, std::to_string(frame.first->GetID()));
	frame.first->GetMaterial()->SetAlbedoColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	frame.second->SetPosition(D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	frame.second->SetScale(D3DXVECTOR3(0.003f, 0.006f, 0.0f));

	scripter->SetScript("Ex_Text.as", "Text", this);
}

void Text::Update()
{
	for (const auto& frame : frames)
	{
		frame.second.first->Update();
		frame.second.second->Update();
	}

	if (scripter)
		scripter->Update();
}

void Text::SetText(const std::wstring& var)
{
	text = var;
	auto frame = GetFrame("Text");
	Renderable* renderable = frame.first;
	Transform* transform = frame.second;

	resourceManager->GetFontImporter()->SetText(glyphs.name, text, renderable, transform);
	renderable->SetTexture(TextureType::Albedo, resourceManager->Load<Texture>(NULL_STRING, glyphs.name));
}

void Text::SetTextFromMultibyte(const std::string& var)
{
	text = FileSystem::ToWstring(var);
	SetText(text);
}
