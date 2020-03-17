cbuffer TransformBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;
};

struct VertexInput
{
    float4 Position : POSITION0;
    float2 Uv : TEXCOORD0;
};

struct PixelInput
{
    float4 Position : SV_POSITION0;
    float2 Uv : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);

    output.Uv = input.Uv;

    return output;
}

Texture2D SourceTexture : register(t0);
SamplerState Samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = SourceTexture.Sample(Samp, input.Uv);

    //clip(color.a - 0.9f);

    return color;
}