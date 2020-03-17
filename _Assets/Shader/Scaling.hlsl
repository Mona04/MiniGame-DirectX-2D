//=============================================================
//Downsampling
//=============================================================
float4 DownsampleBox
(
    float2 uv, 
    float2 texel_size, 
    Texture2D source_texture, 
    SamplerState bilinear_sampler
)
{
    float4 d = texel_size.xyxy * float4(-1.0f, -1.0f, 1.0f, 1.0f);
	// 원본에서 사본의 위치로 이동하려면 output 기준의 텍셀 사이즈가 필요함 

    float4 s;
    s =  source_texture.Sample(bilinear_sampler, uv + d.xy);
    s += source_texture.Sample(bilinear_sampler, uv + d.zy);
    s += source_texture.Sample(bilinear_sampler, uv + d.xw);
    s += source_texture.Sample(bilinear_sampler, uv + d.zw);

    return s * (1.0f / 4.0f);
}

float4 DownsampleBox_AntiFlicker
(
    float2 uv,
    float2 texel_size,
    Texture2D source_texture,
    SamplerState bilinear_sampler
)
{
    float4 d = texel_size.xyxy * float4(-1.0f, -1.0f, 1.0f, 1.0f);

    float4 s1 = source_texture.Sample(bilinear_sampler, uv + d.xy);
    float4 s2 = source_texture.Sample(bilinear_sampler, uv + d.zy);
    float4 s3 = source_texture.Sample(bilinear_sampler, uv + d.xw);
    float4 s4 = source_texture.Sample(bilinear_sampler, uv + d.zw);

    //Karis's Luma weight average
    float s1w = 1.0f / Luminance(s1) + 1.0f;
    float s2w = 1.0f / Luminance(s2) + 1.0f;
    float s3w = 1.0f / Luminance(s3) + 1.0f;
    float s4w = 1.0f / Luminance(s4) + 1.0f;
    float sum = 1.0f / (s1w + s2w + s3w + s4w);

    return (s1 * s1w + s2 * s2w + s3 * s3w + s4 * s4w) * sum;
}

//=============================================================
//Upsampling
//=============================================================
float4 UpsampleBox
(
    float2 uv, 
    float2 texel_size, 
    Texture2D source_texture, 
    SamplerState bilinear_sampler, 
    float4 sample_scale
)
{
	float4 d = texel_size.xyxy * float4(-1.0f, -1.0f, 1.0f, 1.0f) * (sample_scale * 0.5f);
	// sample_scale 을 넣는 이유는 올리면서 한번더 블러 먹임

    float4 s;
    s =  source_texture.Sample(bilinear_sampler, uv + d.xy);
    s += source_texture.Sample(bilinear_sampler, uv + d.zy);
    s += source_texture.Sample(bilinear_sampler, uv + d.xw);
    s += source_texture.Sample(bilinear_sampler, uv + d.zw);

    return s * (1.0f / 4.0f);
}