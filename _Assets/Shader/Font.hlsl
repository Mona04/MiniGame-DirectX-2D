#include "Common.hlsl"

cbuffer FontBuffer : register(b0)
{
	matrix transform;
	float4 color;
}

PixelTexture VS(VertexTexture input)
{
	PixelTexture output;

	output.position = mul(input.position, transform);
	output.uv = input.uv;

	return output;
}

Texture2D font_texture : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelTexture input) : SV_Target
{
	float4 final_color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	final_color.r = font_texture.Sample(samp, input.uv).r;  // ª©≥æ∂ß r8 ∏∏ ª©≥¡¿Ω
	final_color.g = final_color.r;
	final_color.b = final_color.r;
	final_color.a = final_color.r;

	final_color *= color;

	return final_color;
}