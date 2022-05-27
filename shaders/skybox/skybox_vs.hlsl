
cbuffer camera_cb : register(b0)
{
	matrix view;
	matrix proj;
}

struct vs_out
{
	float4 pos : SV_POSITION;
	float3 world_pos : POSITION;
};


vs_out	vert(float3 pos : POSITION)
{
	vs_out output;
	
	output.pos = mul(float4(pos.xyz, 0.0f), mul(view, proj)).xyww;
	output.world_pos = pos;

	return (output);
}
