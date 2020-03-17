cbuffer CameraBuffer : register(b0)
{
    matrix View;
    matrix Proj;
};

cbuffer TransformBuffer : register(b1)
{
    matrix World;
};

cbuffer AnimationBuffer : register(b2)
{
    float2 TextureSize;
    float2 SpriteOffset;
    float2 SpriteSize;
};

cbuffer ColorBuffer : register(b0)
{
    float4 Color;
};

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : UV0;
};

struct PixelInput
{
    float4 Position : SV_POSITION0;
    float2 Uv : UV0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;

    output.Position = float4(input.Position.xy * SpriteSize, 0.0f, 1.0f);
	output.Position = mul(output.Position, World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Proj);

    output.Uv = input.Uv;
	output.Uv *= SpriteSize / TextureSize;
	output.Uv += SpriteOffset / TextureSize;

    return output;
}

Texture2D SourceTexture : register(t0);
SamplerState Samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
	return SourceTexture.Sample(Samp, input.Uv) + Color;
}