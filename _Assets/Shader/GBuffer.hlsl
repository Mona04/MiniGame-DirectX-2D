#include "Common.hlsl"

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

cbuffer RenderOptionBuffer : register(b0)
{
	int isInstanced;
	int isAnimated;
	int hasAlbedoTexture;
	int hasNormalTexture;
	int hasEmissiveTexture;
}

//Local ConstantBuffer
cbuffer CameraBuffer : register(b1)
{
	matrix camera_view;
	matrix camera_proj;
	float3 camera_Pos;
	float camera_near;
	float camera_far;
};

cbuffer WorldBuffer : register(b2)
{
	matrix model_world;
	matrix wvp_current;
	matrix wvp_previous;
}

cbuffer MaterialBuffer : register(b2)
{
	float4 material_albedo;
	float2 material_tiling;
	float2 material_offset;
	float material_normal_strength;
};

cbuffer AnimationBuffer : register(b3)
{
	float2 TextureSize;
	float2 SpriteOffset;
	float2 SpriteSize;
	float isReversed;
	float weight;
}

PixelInput VS(VertexTextureNormalInstanced input)
{
	matrix world = model_world;
	PixelInput output;

	if (isInstanced == 1)
	{
		world._11 = input.scale_Instanced.x;
		world._22 = input.scale_Instanced.y;
		world._33 = input.scale_Instanced.z;
		world._41 += input.position_Instanced.x;
		world._42 += input.position_Instanced.y;
		world._43 += input.position_Instanced.z;		
	}

	if (isAnimated == 1)
	{
		if(isInstanced == 1)
			output.uv = (input.uv * SpriteSize + input.sprite_Offset_Instanced) / TextureSize;
		else
			output.uv = (input.uv * SpriteSize + SpriteOffset) / TextureSize;

		int sign = isReversed == 1 ? -1 : 1;
		world._11 = world._11 * SpriteSize.x / weight ;
		world._22 = world._22 * SpriteSize.y / weight ;
		world._41 -= (world._11 - model_world._11) / 2.0f * sign;
		world._42 += (world._22 - model_world._22) / 2.0f;
	}
	else
	{
		output.uv = input.uv;
	}

    output.positionWS           = mul(input.position, world);
    output.positionVS           = mul(output.positionWS, camera_view);
    output.positionCS           = mul(output.positionVS, camera_proj);
    output.positionCS_current   = mul(input.position, wvp_current);
    output.positionCS_previous  = mul(input.position, wvp_previous);
    output.normal               = normalize(mul(input.normal, (float3x3) model_world));

	return output;
}

Texture2D albedoTexture    : register(t0);
Texture2D normalTexture    : register(t1);
Texture2D emissiveTexture  : register(t2);
SamplerState samp           : register(s0);

PixelOutput PS(PixelInput input)
{
    PixelOutput gbuffer;

	float4 albedo = material_albedo;
    float3 normal = input.normal;
    
    float2 position_current     = input.positionCS_current.xy / input.positionCS_current.w;
    float2 position_previous    = input.positionCS_previous.xy / input.positionCS_previous.w;
    float2 position_delta       = position_current - position_previous;
    float2 velocity             = position_delta * float2(0.5f, -0.5f);

    float depth_linear          = 1.0f;
    float depth_cs              = 1.0f;

	float2 texcoord = input.uv;
	if (isReversed)
		texcoord.x = 1.0f - texcoord.x;
    texcoord = float2(texcoord.x * material_tiling.x + material_offset.x, texcoord.y * material_tiling.y + material_offset.y);

	if(hasAlbedoTexture)
		albedo *= albedoTexture.Sample(samp, texcoord);

	gbuffer.albedo = albedo;
    gbuffer.normal = float4(normalize(normal), 1.0f);
    gbuffer.velocity = velocity;
    gbuffer.depth = float2(depth_linear, depth_cs);

    return gbuffer;
}