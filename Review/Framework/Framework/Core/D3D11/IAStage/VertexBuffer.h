#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class VertexBuffer final : public IPipeline
{
public:
	VertexBuffer(class Context* context);
	~VertexBuffer();

	ID3D11Buffer* GetBuffer() const { return buffer; }
	const uint& GetVertexCount() const { return vertexCount; }
	void SetVertexCount(const uint& var) { vertexCount = var; }
	const uint& GetVertexOffset() const { return offset; }
	void SetVertexOffset(const uint& offset) { this->offset = offset; }
	const uint& GetVertexStride() const { return stride; }

	template <typename T>
	void Create
	(
		const std::vector<T>& vertices,
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT
	);
	void Clear();
	void BindPipeline();

	template <typename T>
	T* Map();
	void Unmap();

private:
	class Graphics* graphics;

	ID3D11Buffer* buffer;
	uint stride;
	uint offset;
	uint vertexCount;
};

template<typename T>
inline void VertexBuffer::Create(const std::vector<T>& vertices, const D3D11_USAGE & usage)
{
	if(vertices.empty())
		return;

	Clear();

	stride = sizeof(T);
	vertexCount = vertices.size();

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
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.ByteWidth = sizeof(T) * vertices.size();

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertices.data();

	auto hr = graphics->GetDevice()->CreateBuffer
	(
		&desc,
		&subData,
		&buffer
	);
	assert(SUCCEEDED(hr));
}

template<typename T>
inline T* VertexBuffer::Map()
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
