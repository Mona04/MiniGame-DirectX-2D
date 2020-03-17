#include "Common.hlsl"

struct VertexInput
{
	float4 Position : POSITION0;
	float2 Uv       : TEXCOORD0;
};

struct PixelInput
{
	float4 Position : SV_POSITION0;
	float2 Uv       : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, global_wvp);
    output.Position = mul(output.Position, global_view);
    output.Position = mul(output.Position, global_proj);

    output.Uv = input.Uv;

    return output;
}

Texture2D AlbedoTexture : register(t0);
Texture2D NormalTexture : register(t1);
Texture2D EmissiveTexture : register(t2);
SamplerState Samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = float4(1, 0, 0, 1);

#if ALBEDO_TEXTURE
    color = AlbedoTexture.Sample(Samp, input.Uv);
#endif

#if NORMAL_TEXTURE

#endif

#if EMISSIVE_TEXTURE

#endif
    return color;
}