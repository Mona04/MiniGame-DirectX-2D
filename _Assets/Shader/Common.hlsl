#include "CommonVertex.hlsl"

//===========================================================
//Global Constant
//===========================================================
#define GLOBAL_SCALE 100

#define PI 3.1415926535897932384626433832795
#define INV_PI 1.0 / PI
#define EPSILON 0.00000001

//===========================================================
//Packing
//===========================================================
float3 Pack(float3 value)//-->[-1, 1] -> [0, 1]
{
    return value * 0.5f + 0.5f;
}

float3 UnPack(float3 value)//-->[0, 1] -> [-1, 1]
{
    return value * 2.0f - 1.0f;
}

//===========================================================
//Luminance
//===========================================================
float Luminance(float3 color)
{
    return max(dot(color, float3(0.299f, 0.587f, 0.114f)), 0.0001f);
}

float Luminance(float4 color)
{
    return max(dot(color.rgb, float3(0.299f, 0.587f, 0.114f)), 0.0001f);
}