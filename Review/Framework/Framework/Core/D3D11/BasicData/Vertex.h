#pragma once

struct VertexPosition
{
	Vector3 position;
	
	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 1;

	VertexPosition()
		: position(0, 0, 0)
	{}

	VertexPosition(const Vector3& position)
		: position(position)
	{}
};

struct VertexPositionScaleSprite
{
	Vector3 position;
	Vector3 scale;
	Vector2 spriteOffset;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 3;

	VertexPositionScaleSprite()
		: position(0, 0, 0), scale(0, 0, 0), spriteOffset(0, 0)
	{}

	VertexPositionScaleSprite(const Vector3& position, const Vector3& scale, const Vector2& spriteOffset)
		: position(position), scale(scale), spriteOffset(spriteOffset)
	{}
};

struct VertexColor
{
	Vector3 position;
	Color4 color;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;

	VertexColor()
		: position(0, 0, 0)
		, color(0, 0, 0, 1)
	{}

	VertexColor(const Vector3& position, const Color4& color)
		: position(position)
		, color(color)
	{}
};

struct VertexTexture
{
	Vector3 position;
	Vector2 uv;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 2;

	VertexTexture()
		: position(0, 0, 0)
		, uv(0, 0)
	{}

	VertexTexture(const Vector3& position, const Vector2& uv)
		: position(position)
		, uv(uv)
	{}
};

struct VertexTextureNormal
{
	Vector3 position;
	Vector2 uv;
	Vector3 normal;

	static D3D11_INPUT_ELEMENT_DESC descs[];
	static const uint count = 3;

	VertexTextureNormal()
		: position(0, 0, 0)
		, uv(0, 0)
		, normal(0, 0, 0)
	{}
	
	VertexTextureNormal(const Vector3& position, const Vector2& uv, const Vector3& normal)
		: position(position)
		, uv(uv)
		, normal(0, 0, 0)
	{}
};