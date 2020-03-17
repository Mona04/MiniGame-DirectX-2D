#pragma once
#include "Framework/Core/Subsystem/Render/IPipeline.h"

class IndexBuffer final : public IPipeline
{
public:
	IndexBuffer(class Context* context);
	~IndexBuffer();

	ID3D11Buffer* GetBuffer() const { return buffer; }
	const uint& GetIndexCount() const { return indexCount; }
	void SetIndexCount(const uint& var) { this->indexCount = var; }
	const uint& GetIndexOffset() const { return offset; }
	void SetIndexOffset(const uint& offset) { this->offset = offset; }

	void Create
	(
		const std::vector<uint>& indices,
		const D3D11_USAGE& usage = D3D11_USAGE_DEFAULT
	);
	void Clear();
	void BindPipeline();

	uint* Map();
	void Unmap();

private:
	class Graphics* graphics;
	ID3D11Buffer* buffer;
	uint indexCount;
	uint offset;
};
