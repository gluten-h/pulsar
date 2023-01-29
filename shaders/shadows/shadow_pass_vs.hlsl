
cbuffer transform_cb : register(b0)
{
	matrix model;
	matrix norm;
};

cbuffer view_cb : register(b1)
{
	matrix view;
}

cbuffer proj_cb : register(b2)
{
	matrix proj;
}

struct vs_out
{
	float4 pos : SV_POSITION;
	float4 world_view_pos : POSITION0;
};

vs_out	vert(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV)
{
	vs_out output;

	output.pos = mul(float4(pos.xyz, 1.0f), mul(mul(model, view), proj));
	output.world_view_pos = mul(float4(pos.xyz, 1.0f), mul(model, view));

	return (output);
}
