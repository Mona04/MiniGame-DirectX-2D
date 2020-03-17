#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class ConstantBuffer final : public IPipeline
{
public:
	ConstantBuffer(class Context* context);
	~ConstantBuffer();

	ID3D11Buffer* GetBuffer() const { return buffer; }

	template <typename T>
	void Create(const D3D11_USAGE& usage = D3D11_USAGE_DYNAMIC);
	void Clear();
	void BindPipeline(const ShaderStage& stage, const uint& slot);

	template <typename T>
	T* Map();
	void Unmap();

private:
	class Graphics* graphics;
	ID3D11Buffer* buffer;
};

template<typename T>
inline void ConstantBuffer::Create(const D3D11_USAGE & usage)
{
	Clear();

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
	case D3D11_USAGE_IMMUTABLE:
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}

	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(T);

	auto hr = graphics->GetDevice()->CreateBuffer
	(
		&desc,
		nullptr,
		&buffer
	);

	assert(SUCCEEDED(hr));
}

template<typename T>
inline T * ConstantBuffer::Map()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	auto hr = graphics->GetDeviceContext()->Map
	(
		buffer,
		0,
		D3D11_MAP_WRITE_DISCARD,
		0,
		&mappedResource
	);
	assert(SUCCEEDED(hr));

	return reinterpret_cast<T*>(mappedResource.pData);
}