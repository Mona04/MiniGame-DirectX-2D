
struct VertexInput
{
	folat4 position : POSITION0;
	float2 uv  : TEXCOORD;
	float4 color: COLOR0;
};

PixelInput VS(VertexInput input)
{
	PixelInput output;

	output.position = mul(input.position, global_view);
	output.position = mul(output.position, global_proj);
	output.uv = input.uv;
	output.uv = input.uv;

	return output;
}

float4 PS(PixelInput input) : SV_Target
{
	float4 color = source_texture.Sample(samp, input.uv);
	return color * input.color;
}