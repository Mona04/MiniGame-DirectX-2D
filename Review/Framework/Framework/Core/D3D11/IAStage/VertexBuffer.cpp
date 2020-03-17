#include "Framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Context * context)
	: buffer(nullptr)
	, stride(0)
	, vertexCount(0)
	, offset(0)
{
	graphics = context->GetSubsystem<Graphics>();
}

VertexBuffer::~VertexBuffer()
{
	Clear();
}

void VertexBuffer::Clear()
{
	stride = 0;
	vertexCount = 0;

	SAFE_RELEASE(buffer);
}

void VertexBuffer::BindPipeline()
{
	graphics->GetDeviceContext()->IASetVertexBuffers
	(
		0,
		1,
		&buffer,
		&stride,
		&offset
	);
}

void VertexBuffer::Unmap()
{
	graphics->GetDeviceContext()->Unmap(buffer, 0);
}
