#include "Common.hlsl"

cbuffer WorldBuffer : register(b0)
{
	matrix ui_world;
}

cbuffer UIBuffer : register(b1)
{
	float isCovered;
	float isClicked;
	float isInstanced;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 material_albedo;
	float2 material_tiling;
	float2 material_offset;
	float material_normal_strength;
}

cbuffer AnimationBuffer : register(b3)
{
	float2 TextureSize;
	float2 SpriteOffset;
	float2 SpriteSize;
	float isReversed;
	float weight;
}

PixelTexture VS(VertexTextureInstanced input)
{
	PixelTexture output;
	matrix world = ui_world;

	if (isInstanced == 1)
	{
		world._11 = input.scale_Instanced.x;
		world._22 = input.scale_Instanced.y;
		world._41 += input.position_Instanced.x;
		world._42 += input.position_Instanced.y;
		
		output.uv = (input.uv * SpriteSize + input.sprite_Offset_Instanced) / TextureSize;
	}
	else
	{
		output.uv = (input.uv * SpriteSize + SpriteOffset) / TextureSize;
	}

	output.position = mul(input.position, world);
	
	return output;
}

Texture2D basic_texture    : register(t0);
SamplerState samp			: register(s0);

float4 PS(PixelTexture input) : SV_Target
{
	float4 result = float4(1.0f, 1.0f, 1.0f, 1.0f);

#if PASS_TEXTURE
	float2 texcoord = input.uv;

	if (isReversed)
		texcoord.x = 1.0f - texcoord.x;
	texcoord = float2(texcoord.x * material_tiling.x + material_offset.x, texcoord.y * material_tiling.y + material_offset.y);
	result *= basic_texture.SampleLevel(samp, texcoord, 0);
	result *= material_albedo;
#endif

#if PASS_COLOR
	result = material_albedo;
#endif

	if (isCovered)
		result += float4(0.15f, 0.15f, 0.15f, 0.15f);

	return result;
}