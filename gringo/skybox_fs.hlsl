
TextureCube cubemap : register(t0);
SamplerState smpl : register(s0);


float4		frag(float4 pos : SV_POSITION, float3 world_pos : POSITION) : SV_TARGET
{
	float4 color = float4(cubemap.Sample(smpl, world_pos).xyz, 1.0f);
	
	return (color);
}