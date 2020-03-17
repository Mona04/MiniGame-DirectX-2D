#include "Framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(Context * context)
	: buffer(nullptr)
	, indexCount(0)
	, offset(0)
{
	graphics = context->GetSubsystem<Graphics>();
}

IndexBuffer::~IndexBuffer()
{
	Clear();
}

void IndexBuffer::Create(const std::vector<uint>& indices, const D3D11_USAGE & usage)
{
	assert(!indices.empty());

	Clear();

	indexCount = indices.size();

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
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.ByteWidth = sizeof(uint) * indices.size();

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = indices.data();

	auto hr = graphics->GetDevice()->CreateBuffer
	(
		&desc,
		&subData,
		&buffer
	);
	assert(SUCCEEDED(hr));
}

void IndexBuffer::Clear()
{
	indexCount = 0;
	SAFE_RELEASE(buffer);
}

void IndexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetIndexBuffer
	(
		buffer,
		DXGI_FORMAT_R32_UINT,
		offset
	);
}

uint* IndexBuffer::Map()
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

	return reinterpret_cast<uint*>(mappedResource.pData);
}

void IndexBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(buffer, 0);
}
