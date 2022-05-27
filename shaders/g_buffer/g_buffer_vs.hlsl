
cbuffer transform_cb : register(b0)
{
    matrix model;
    matrix norm;
};

cbuffer camera_cb : register(b1)
{
	matrix view;
	matrix proj;
}

struct vs_out
{
    float4 pos : SV_POSITION;
    float4 world_pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
};

vs_out  vert(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV)
{
    vs_out output;

	output.pos = mul(float4(pos.xyz, 1.0f), mul(mul(model, view), proj));
	output.world_pos = mul(float4(pos.xyz, 1.0f), model);
	output.normal = mul(normal, (float3x3) norm);
    output.uv = uv;

    return (output);
}
