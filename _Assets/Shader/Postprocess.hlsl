#include "Common.hlsl"
#include "Blur.hlsl"
#include "Scaling.hlsl"

cbuffer PostprocessBuffer : register(b0)
{
	float2 global_resolution;
	float2 blur_direction;
	float blur_sigma;
	float  bloom_intensity;
};
#define global_texel_size float2(1.0f / global_resolution.x, 1.0f / global_resolution.y)

PixelTexture VS(VertexTexture input)
{
    PixelTexture output;

	output.position = input.position;
	output.uv       = input.uv;

    return output;
}

Texture2D source_texture1    : register(t0);
Texture2D source_texture2    : register(t1);
Texture2D source_texture3    : register(t2);
SamplerState samp            : register(s0);

float4 PS(PixelTexture input) : SV_Target
{
    float4 color = float4(1, 0, 0, 1);

#if PASS_TEXTURE
    color = source_texture1.Sample(samp, input.Uv);
#endif

#if PASS_DOWNSAMPLE_BOX
    color = DownsampleBox_AntiFlicker
    (
        input.uv,
        global_texel_size,
        source_texture1,
        samp
    );
#endif

#if PASS_BRIGHT
	color = source_texture1.Sample(samp, input.uv);
	color = Luminance(color) * color;   // green 이 없으면 어두워짐
#endif

#if PASS_UPSAMPLE_BOX
    color = UpsampleBox
    (
        input.uv,
        global_texel_size,
        source_texture1,
        samp,
        4.0f
    );
#endif

#if PASS_BOX_BLUR

#endif

#if PASS_GAUSSIAN_BLUR
    color = GaussianBlur
    (
        input.uv,
        source_texture1,
        samp,
        global_texel_size,
        blur_direction,
        blur_sigma
    );
#endif

#if PASS_BILATERAL_GAUSSIAN_BLUR

#endif

#if PASS_BLEND
    float4 source_color1 = source_texture1.Sample(samp, input.uv);
    float4 source_color2 = source_texture2.Sample(samp, input.uv);
    color = source_color1 + (source_color2 * bloom_intensity);
#endif

    return color;
}