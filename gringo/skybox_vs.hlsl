

cbuffer transform_cb : register(b0)
{
	matrix model;
	matrix view;
	matrix proj;
	matrix norm;
};


struct vs_out
{
	float4 pos : SV_POSITION;
	float3 world_pos : POSITION;
};


vs_out		vert(float3 pos : POSITION)
{
	vs_out output;
	
	output.pos = mul(proj, mul(view, float4(pos, 0.0f))).xyww;
	output.world_pos = pos;

	return (output);
}
