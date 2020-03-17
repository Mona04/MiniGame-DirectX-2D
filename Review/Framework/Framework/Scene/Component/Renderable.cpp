#include "Framework.h"
#include "Renderable.h"
#include "Framework/Resource/Texture.h"

Renderable::Renderable(Context * context)
	: IComponent(context)
	, mesh(nullptr)
	, material(nullptr)
	, materialBuffer(nullptr)
{
	IComponent::type = ComponentType::Renderable;

	resourceManager = context->GetSubsystem<ResourceManager>();

	materialBuffer = new ConstantBuffer(context);
	materialBuffer->Create<MaterialData>();
}

Renderable::~Renderable()
{
	SAFE_DELETE(materialBuffer);
}

void Renderable::Update()
{
	if (material)
	{
		auto data = materialBuffer->Map<MaterialData>();
		{
			data->Material_albedo = material->GetAlbedoColor();

			data->Material_normal_strength = material->GetNormalStrength();
			data->Material_offset = material->GetUvOffset();
			data->Material_tiling = material->GetUvTiling();
		}
		materialBuffer->Unmap();
	}
}

void Renderable::Render()
{
	mesh->GetVertexBuffer()->BindPipeline();
	mesh->GetIndexBuffer()->BindPipeline();

	if (HasTexture(TextureType::Albedo))
		GetTexture(TextureType::Albedo)->BindPipeline(ShaderStage::PS, 0);
	if (HasTexture(TextureType::Emissive))
		GetTexture(TextureType::Emissive)->BindPipeline(ShaderStage::PS, 1);
	if (HasTexture(TextureType::Normal))
		GetTexture(TextureType::Normal)->BindPipeline(ShaderStage::PS, 2);
}

Texture* Renderable::GetTexture(const TextureType& type)
{
	if (textures.find(type) == textures.end())
		return nullptr;
	return textures[type];
}

void Renderable::SetTexture(const TextureType& type, Texture* texture)
{
	if (textures.find(type) != textures.end())
	{
		if (texture->GetResourceName() == this->textures.find(type)->second->GetResourceName())
			return;
		textures.erase(textures.find(type));
	}

	if (texture)
		textures.insert(std::make_pair(type, texture));
}

void Renderable::SetTexture(const TextureType& type, const std::string& path, const std::string& name)
{
	Texture* texture = resourceManager->Load<Texture>(path, name);
	SetTexture(type, texture);
}

void Renderable::RemoveTexture(const TextureType& type)
{
	if (textures.find(type) != textures.end())
		textures.erase(textures.find(type));
}

void Renderable::SetMesh(const std::string& path, const std::string& name)
{
	std::string _name = name == NULL_STRING ? FileSystem::GetIntactFileNameFromPath(path) : name;
	
	if (Mesh* tmp = resourceManager->GetResourceFromName<Mesh>(_name))
	{
		mesh = tmp;
		return;
	}

	mesh = resourceManager->Load<Mesh>(path, _name);
}

void Renderable::SetMaterial(const std::string& path, const std::string & name)
{
	std::string _name = name == NULL_STRING ? FileSystem::GetIntactFileNameFromPath(path) : name;

	if (Material* tmp = resourceManager->GetResourceFromName<Material>(_name))
	{
		material = tmp;
		return;
	}

	material = resourceManager->Load<Material>(path, _name);
}
