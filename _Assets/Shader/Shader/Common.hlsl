//-----------------------------------------------------------
//Global Constant Buffer
//-----------------------------------------------------------
cbuffer CameraBuffer : register(b0)
{
    matrix WVP;
    matrix View;
    matrix Proj;
    matrix Proj_Ortho;
    matrix VP;
    matrix VP_Ortho;
    float Camera_Near;
    float Camera_Far;
    float2 Resolution;
    float3 Camera_Position;
};

//-----------------------------------------------------------
//VS Constant Buffer
//-----------------------------------------------------------
cbuffer TransformBuffer : register(b1)
{
    matrix World;
    matrix WVP_Current;
    matrix WVP_Previous;
};

//-----------------------------------------------------------
//PS Constant Buffer
//-----------------------------------------------------------
cbuffer MaterialBuffer : register(b1)
{
    float4 Material_albedo;
    float2 Material_tiling;
    float2 Material_offset;
    float Material_normal_strength;
}