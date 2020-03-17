#include "Common.hlsl"

cbuffer MaterialBuffer : register(b1)
{
    float4 material_albedo;
    float2 material_tiling;
    float2 material_offset;
    float material_normal_strength;
};

cbuffer ActorBuffer : register(b2)
{
    matrix model_world;
    matrix wvp_current;
    matrix wvp_previous;
};

struct PixelInput
{
    float4 positionCS           : SV_POSITION0;
    float2 uv                   : TEXCOORD0;
    float3 normal               : NORMAL0;
    float4 positionVS           : POSITION0;
    float4 positionWS           : POSITION1;
    float4 positionCS_current   : SCREEN_POSITION0;
    float4 positionCS_previous  : SCREEN_POSITION_PREV0;
};

struct PixelOutput
{
    float4 albedo   : SV_Target0;
    float4 normal   : SV_Target1;
    float2 velocity : SV_Target2;
    float2 depth    : SV_Target3;
};

PixelInput VS(VertexTextureNormal input)
{
    PixelInput output;
    output.positionWS           = mul(input.position, model_world);
    output.positionVS           = mul(output.positionWS, global_view);
    output.positionCS           = mul(output.positionVS, global_proj);
    output.positionCS_current   = mul(input.position, wvp_current);
    output.positionCS_previous  = mul(input.position, wvp_previous);
    output.normal               = normalize(mul(input.normal, (float3x3) model_world));
    output.uv                   = input.uv;

    return output;
}

Texture2D albedo_texture    : register(t0);
Texture2D normal_texture    : register(t1);
Texture2D emissive_texture  : register(t2);
SamplerState samp           : register(s0);

PixelOutput PS(PixelInput input)
{
    PixelOutput gbuffer;

    float4 albedo               = material_albedo;
    float3 normal               = input.normal;
    
    float2 position_current     = input.positionCS_current.xy / input.positionCS_current.w;
    float2 position_previous    = input.positionCS_previous.xy / input.positionCS_previous.w;
    float2 position_delta       = position_current - position_previous;
    float2 velocity             = position_delta * float2(0.5f, -0.5f);

    float depth_linear          = 1.0f;
    float depth_cs              = 1.0f;

    float2 texcoord             = float2(input.uv.x * material_tiling.x + material_offset.x, input.uv.y * material_tiling.y + material_offset.y);

#if ALBEDO_TEXTURE
    albedo *= albedo_texture.Sample(samp, texcoord);
#endif

#if NORMAL_TEXTURE

#endif

#if EMISSIVE_TEXTURE

#endif

    gbuffer.albedo = albedo;
    gbuffer.normal = float4(normalize(normal), 1.0f);
    gbuffer.velocity = velocity;
    gbuffer.depth = float2(depth_linear, depth_cs);

    return gbuffer;
}