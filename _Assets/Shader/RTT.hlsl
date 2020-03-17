#include "Common.hlsl"

PixelTexture VS(VertexTexture input)
{
	PixelTexture output;
	output.position	  = input.position;
	output.uv = input.uv;

	return output;
}

Texture2D basic_texture    : register(t0);
SamplerState samp			: register(s0);

float4 PS(PixelTexture input) : SV_Target
{    
    return basic_texture.Sample(samp, input.uv);
}