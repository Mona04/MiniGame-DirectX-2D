#pragma once
#include "IComponent.h"

enum class MeshType : uint;
enum class TextureType : uint;

class Renderable : public IComponent
{
public:
	Renderable(class Context* context);
	~Renderable();

	void Update() override;
	void Render() override;	

	class Texture* GetTexture(const TextureType& type);
	std::map<TextureType, Texture*> GetTextures() { return textures; }
	void SetTexture(const TextureType& type, class Texture* texture);
	void SetTexture(const TextureType& type, const std::string& path, const std::string& name);
	void RemoveTexture(const TextureType& type);
	
	const bool HasTexture(const TextureType& type) { return textures.find(type) != textures.end(); }

	class Mesh* GetMesh() { return mesh; }
	void SetMesh(const std::string& path, const std::string& name = NULL_STRING);

	class Material* GetMaterial() { return material; }
	void SetMaterial(const std::string& path = NULL_STRING, const std::string& name = NULL_STRING);

	class ConstantBuffer* GetMaterialBuffer() { return materialBuffer; }

private:
	class ResourceManager* resourceManager;
	class Material* material;
	class Mesh* mesh;
	std::map<TextureType, Texture*> textures;
	class ConstantBuffer* materialBuffer;
};