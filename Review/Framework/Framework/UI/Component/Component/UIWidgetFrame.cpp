#include "Framework.h"
#include "UIWidgetFrame.h"

UIWidgetFrame::UIWidgetFrame(Context* context)
	: context(context)
	, transform(nullptr)
	, renderable(nullptr)
	, scripter(nullptr)
	, name("N\A")
	, isClicked(false)
{
	resourceManager = context->GetSubsystem<ResourceManager>();
	mouseManager = context->GetSubsystem<MouseManager>();

	transform = new Transform(context);
	renderable = new Renderable(context);
	scripter = new Scripter(context);
	animator = new Animator(context);

	uiBuffer = new ConstantBuffer(context);
	uiBuffer->Create<UIData>();
}

UIWidgetFrame::~UIWidgetFrame()
{
	SAFE_DELETE(transform);
	SAFE_DELETE(renderable);
	SAFE_DELETE(scripter);
	SAFE_DELETE(animator);
	SAFE_DELETE(uiBuffer);
}

void UIWidgetFrame::SaveToFile(FileStream& stream)
{
	stream.Write(this->name);
	stream.Write(useDefaultCovered);
	stream.Write(static_cast<uint>(renderable->GetTextures().size()));
	for (int i = 0; i < 4; i++)
	{
		if (renderable->HasTexture(static_cast<TextureType>(i)))
		{
			stream.Write(static_cast<uint>(i));
			stream.Write(renderable->GetTexture(static_cast<TextureType>(i))->GetResourcePath());
			stream.Write(renderable->GetTexture(static_cast<TextureType>(i))->GetResourceName());
		}
	}

	stream.Write(renderable->GetMesh()->GetResourcePath()); // meshPath
	stream.Write(renderable->GetMesh()->GetResourceName()); // meshName
	stream.Write(renderable->GetMaterial()->GetResourcePath());  // materialPath 
	stream.Write(renderable->GetMaterial()->GetResourcePath());  // materialName
	stream.Write(transform->GetPosition());  // position
	stream.Write(transform->GetScale());  // scale

	stream.Write(scripter->GetScript() ? scripter->GetScript()->GetResourcePath() : "N\A");  // script
	stream.Write(animator->GetAnimation() ? animator->GetAnimation()->GetResourcePath() : "N\A"); // animator
}

void UIWidgetFrame::LoadFromFile(FileStream& stream)
{
	std::string meshPath, meshName, materialPath, materialName, texturePath, textureName, scripterPath, animationPath;
	uint nTexture;
	TextureType textureType;
	Vector3 pos;
	Vector3 scale;

	stream.Read(this->name);
	stream.Read(useDefaultCovered);
	nTexture = stream.ReadUInt();
	for (int i = 0; i < nTexture; i++)
	{
		textureType = static_cast<TextureType>(stream.ReadUInt());
		stream.Read(texturePath);
		stream.Read(textureName);
		renderable->SetTexture(textureType, texturePath, textureName);
	}

	stream.Read(meshPath);
	stream.Read(meshName);
	stream.Read(materialPath);
	stream.Read(materialName);
	stream.Read(pos);
	stream.Read(scale);

	stream.Read(scripterPath);
	stream.Read(animationPath);

	renderable->SetMesh(meshPath, meshName);
	renderable->SetMaterial(materialPath, materialName);
	transform->SetPosition(pos);
	transform->SetScale(scale);
	if (scripterPath != "N\A")
		scripter->SetScript(scripterPath, scripterPath, this);
	if (animationPath != "N\A")
		animator->SetAnimation(animationPath, animationPath, renderable);
}

void UIWidgetFrame::Init_Default()
{
	renderable->SetMesh("UI_QUAD.mesh", std::to_string(renderable->GetID()));
	renderable->SetMaterial("UI_Default.material");
}

void UIWidgetFrame::Update()
{
	transform->Update();
	renderable->Update();
	scripter->Update();
	animator->Update();
	UpdateUIBuffer();
}

void UIWidgetFrame::UpdateUIBuffer(Camera* camera)
{
	if (!transform)
		return;

	Vector3 worldRay = mouseManager->GetMousePos();

	BoundBox boundBox;
	Vector3 pos = transform->GetPosition();
	Vector3 scale = transform->GetScale();
	if(this->text != L"N\A") // 시바 텍스트는 transform 에 따라서 가로세로 조절이 안댐
		scale.y *= 0.4f;
	Vector3 center = pos + Vector3(scale.x / 2.0f, -scale.y / 2.0f, 0.0f);;
	boundBox.minPoint = center - scale / 2.0f;
	boundBox.maxPoint = center + scale / 2.0f;

	if (Intersection::Inside == boundBox.IsInside(worldRay))
	{
		isCovered = true;
		isClicked = lockClick == false ? mouseManager->IsClicked() : false;
	}
	else
	{
		isCovered = false;
		isClicked = false;
	}
	if (useDefaultCovered)
	{
		auto data = uiBuffer->Map<UIData>();
		{
			data->isCovered = this->isCovered;
			data->isClicked = this->isClicked;
			data->isInstanced = this->isInstanced;
		}
		uiBuffer->Unmap();
	}
}

void UIWidgetFrame::SetIsInstanced(const bool& var)
{
	this->isInstanced = var;
	auto data = uiBuffer->Map<UIData>();
	{
		data->isCovered = this->isCovered;
		data->isClicked = this->isClicked;
		data->isInstanced = this->isInstanced;
	}
	uiBuffer->Unmap();
}

void UIWidgetFrame::SetText(const std::wstring& var)
{
	if (this->text == var)
		return;
	this->text = var;
	resourceManager->GetFontImporter()->SetText(FONT_NANUM, var, renderable, transform);
	renderable->SetTexture(TextureType::Albedo, resourceManager->Load<Texture>(NULL_STRING, FONT_NANUM));
}

void UIWidgetFrame::SetTextFromMultibyte(const std::string& var)
{
	SetText(FileSystem::ToWstring(var));
}
