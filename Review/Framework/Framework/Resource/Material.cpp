#include "Framework.h"
#include "Material.h"
#include "Framework/Shader/Shader.h"

Material::Material(Context * context)
	: IResource(context)
	, albedoColor(1.0f, 1.0f, 1.0f, 1.0f)
	, uvTiling(1.0f, 1.0f)
	, uvOffset(0.0f, 0.0f)
	, normalStrength(0.0f)
	, samplerType(SamplerType::wrap_anisotropic)
{
}

void Material::LoadFromFile(const std::string& path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Read);
	{
		stream.Read(albedoColor);
		stream.Read(uvTiling);
		stream.Read(uvOffset);
		stream.Read(normalStrength);
		samplerType = static_cast<SamplerType>(stream.ReadUInt());
	}
	stream.Close();
}

void Material::SaveToFile(const std::string & path)
{
	FileStream stream;
	stream.Open(path, StreamMode::Write);
	{
		stream.Write(albedoColor);
		stream.Write(uvTiling);
		stream.Write(uvOffset);
		stream.Write(normalStrength);
		stream.Write(static_cast<uint>(samplerType));
	}
	stream.Close();
}


