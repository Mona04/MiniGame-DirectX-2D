#include "Common.hlsl"

Texture2D albedo_texture    : register(t0);
Texture2D normal_texture    : register(t1);
Texture2D depth_texture     : register(t2);

SamplerState linear_clamp_sampler   : register(s0);
SamplerState point_clamp_sampler    : register(s1);

PixelTexture VS(VertexTexture input)
{
    PixelTexture output;

    output.position = mul(input.position, global_vp_ortho);
    output.uv       = input.uv;

    return output;
}

float4 PS(PixelTexture input) : SV_Target
{
    float2 texcoord = input.uv;
    
    return albedo_texture.Sample(linear_clamp_sampler, texcoord);
}