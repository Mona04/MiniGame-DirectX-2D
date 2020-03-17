//==================================================
//Gaussian Blur
//==================================================
float CalcGaussianWeight(int sample_dist, float sigma)
{
    float g = 1.0f / sqrt(2.0f * 3.141592f * pow(sigma, 2));
    return (g * exp(-(pow(sample_dist, 2) / (2.0f * pow(sigma, 2)))));
}

float4 GaussianBlur
(
    float2 uv, 
    Texture2D src_texture, 
    SamplerState samp, 
    float2 texel_size, 
    float2 direction, 
    float sigma
)
{
    float total_weight  = 0.0f;
    float color         = 0.0f;

    for (int i = -5; i < 5; i++)
    {
        float2 texcoord = uv + (i * texel_size * direction);
        float weight    = CalcGaussianWeight(i, sigma);

        color           += src_texture.SampleLevel(samp, texcoord, 0) * weight;
        total_weight    += weight;
    }

    color /= total_weight;

    return color;
}