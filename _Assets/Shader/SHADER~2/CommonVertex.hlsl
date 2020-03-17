//========================================================================
//VS input
//========================================================================
struct Vertex
{
    float4 position : POSITION0;
};

struct VertexColor
{
    float4 position : POSITION0;
    float4 color    : COLOR0;
};

struct VertexTexture
{
    float4 position : POSITION0;
    float2 uv       : TEXCOORD0;
};

struct VertexTextureNormal
{
    float4 position : POSITION0;
    float2 uv       : TEXCOORD0;
    float3 normal   : NORMAL0;
};

//========================================================================
//PS input
//========================================================================
struct Pixel
{
    float4 position : SV_POSITION0;
};

struct PixelColor
{
    float4 position : SV_POSITION0;
    float4 color    : COLOR0;
};

struct PixelTexture
{
    float4 position : SV_POSITION0;
    float2 uv       : TEXCOORD0;
};

struct PixelTextureNormal
{
    float4 position : SV_POSITION0;
    float2 uv       : TEXCOORD0;
    float3 normal   : NORMAL0;
};
