#include "Common.hlsl"

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv       : TEXCOORD0;
    float3 Normal   : NORMAL0;
};

struct PixelInput
{
    float4 PositionCS           : SV_POSITION0;
    float2 Uv                   : TEXCOORD0;
    float3 Normal               : NORMAL0;
    float4 PositionVS           : POSITION0;
    float4 PositionWS           : POSITION1;
    float4 PositionCS_Current   : SCREEN_POSITION0;
    float4 PositionCS_Previous  : SCREEN_POSITION_PREV0;
};

struct PixelOutput
{
    float4 Albedo   : SV_Target0;
    float4 Normal   : SV_Target1;
    float2 Velocity : SV_Target2;
    float2 Depth    : SV_Target3;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.PositionWS           = mul(input.Position, World);
    output.PositionVS           = mul(output.PositionWS, View);
    output.PositionCS           = mul(output.PositionVS, Proj);
    output.PositionCS_Current   = mul(input.Position, WVP_Current);
    output.PositionCS_Previous  = mul(input.Position, WVP_Previous);
    output.Normal               = normalize(mul(input.Normal, (float3x3) World));
    output.Uv                   = input.Uv;

    return output;
}

Texture2D AlbedoTexture : register(t0);
Texture2D NormalTexture : register(t1);
Texture2D EmissiveTexture : register(t2);
SamplerState Samp : register(s0);

PixelOutput PS(PixelInput input)
{
    PixelOutput gbuffer;

    float4 albedo = Material_albedo;
    float3 normal = input.Normal;
    
    float2 position_current = input.PositionCS_Current.xy / input.PositionCS_Current.w;
    float2 position_previous = input.PositionCS_Previous.xy / input.PositionCS_Previous.w;
    float2 position_delta = position_current - position_previous;
    float2 velocity = position_delta * float2(0.5f, -0.5f);

    float depth_linear = 1.0f;
    float depth_cs = 1.0f;

#if ALBEDO_TEXTURE
    albedo *= AlbedoTexture.Sample(Samp, input.Uv);
#endif

#if NORMAL_TEXTURE

#endif

#if EMISSIVE_TEXTURE

#endif

    gbuffer.Albedo = albedo;
    gbuffer.Normal = float4(normalize(normal), 1.0f);
    gbuffer.Velocity = velocity;
    gbuffer.Depth = float2(depth_linear, depth_cs);

    return gbuffer;
}