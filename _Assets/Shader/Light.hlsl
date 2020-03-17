#include "Common.hlsl"

Texture2D albedo_texture : register(t0);
Texture2D normal_texture : register(t1);
Texture2D depth_texture : register(t2);

SamplerState linear_samp : register(s0);
SamplerState point_samp : register(s1);

#define Max_Lights 64

cbuffer LightBuffer : register(b1)
{
    matrix wvp;

    float4 directional_color;
    float4 directional_intensity;
    float4 directional_direction;

    float4 point_light_position[Max_Lights];
    float4 point_light_color[Max_Lights];
    float4 point_light_intensity_range[Max_Lights];

    float4 spot_light_position[Max_Lights];
    float4 spot_light_direction[Max_Lights];
    float4 spot_light_intensity_range_angle[Max_Lights];
    float4 spot_light_color[Max_Lights];

    float point_light_count;
    float spot_light_count;
}

PixelTexture VS(VertexTexture input)
{
    PixelTexture output;

    output.position = input.position;
    output.uv = input.uv;

    return output;
}

float4 PS(PixelTexture input) : SV_Target
{
    float2 texcoord         = input.uv;
	float3 color = albedo_texture.Sample(linear_samp, texcoord);
	/*
	float3 color            = 0.0f;
	
    float depth             = depth_texture.Sample(linear_samp, texcoord).r;
    float3 world_pos        = GetWorldPositionFromDepth(depth, global_view_proj_inverse, texcoord);
    float3 camera_to_pixel  = normalize(world_pos.xyz - global_camera_position.xyz);

    float4 albedo           = albedo_texture.Sample(linear_samp, texcoord);
    float4 normal_sample    = normal_texture.Sample(linear_samp, texcoord);
    float3 normal           = normalize(normal_sample);

    //Test
    color += albedo.rgb;

    //Directional
    Light directional_light;
    directional_light.color     = directional_color.rgb;
    directional_light.direction = normalize(-directional_direction).xyz;
       
    directional_light.intensity = saturate(dot(normal, directional_light.direction));
    directional_light.intensity *= directional_intensity;

    if (directional_light.intensity > 0.0f)
        color += directional_light.color * directional_light.intensity;

    //Point Light
    Light point_light;
    for (int i = 0; i < point_light_count; i++)
    {
        float3 position         = point_light_position[i].xyz;
        float range             = point_light_intensity_range[i].y;
        point_light.intensity   = point_light_intensity_range[i].x;
        point_light.color       = point_light_color[i].rgb;
        
        point_light.direction   = normalize(position - world_pos);
        float dist              = length(world_pos - position);
        float attenuation       = saturate(1.0f - dist / range);
        //attenuation *= attenuation;
        //point_light.intensity *= attenuation;

        if (dist < range)
        {
            //TODO : 
            color += point_light.color * point_light.intensity;
        }
    }

    //Spot Light
    Light spot_light;
    for (int j = 0; j < spot_light_count; j++)
    {
        float3 position         = spot_light_position[j].xyz;
        float range             = spot_light_intensity_range_angle[j].y;
        float cut_off_angle     = 1.0f - spot_light_intensity_range_angle[j].z;

        spot_light.direction    = normalize(-spot_light_direction[j].xyz);
        spot_light.intensity    = spot_light_intensity_range_angle[j].x;
        spot_light.color        = spot_light_color[j].rgb;

        float3 direction        = normalize(position - world_pos);
        float dist              = length(world_pos - position);
        float theta             = dot(direction, spot_light.direction);
        float epsilon           = cut_off_angle - cut_off_angle * 0.9f;
        float attenuation       = saturate(1.0f - dist / range);
        attenuation             *= attenuation;
        spot_light.intensity    *= attenuation;

        if(theta > cut_off_angle)
            color += spot_light.color * spot_light.intensity;
    }
	*/

   return float4(color, 1.0f);
}