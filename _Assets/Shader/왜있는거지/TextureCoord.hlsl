cbuffer TransformBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Proj;
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
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Proj);

    output.Uv = input.Uv;

    return output;
}

Texture2D SourceTexture : register(t0);
Texture2D SourceTexture2 : register(t1);
SamplerState Samp : register(s0);

float4 PS(PixelInput input) : SV_Target
{
    float4 color = 0;

    [flatten]
    if(input.Uv.x < 1.0f)
        color = SourceTexture.Sample(Samp, input.Uv) + float4(1, 1, 0, 0);
    else
        color = SourceTexture2.Sample(Samp, float2(input.Uv.x - 1.0f, input.Uv.y));

    return color;
}