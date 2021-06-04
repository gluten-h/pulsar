
Texture2D   mat_albedo : register(t0);

cbuffer material_cb : register(b0)
{
	float3      mat_albedo_color;
};

SamplerState    smpl : register(s0);


struct f_out
{
	float4 position : SV_Target0;
	float4 albedo : SV_Target1;
	float4 normal : SV_Target2;
};


f_out       frag(float4 pos : SV_POSITION, float4 world_pos : POSITION, float3 normal : NORMAL, float2 uv : UV)
{
	f_out output;

	output.position = world_pos;
	output.albedo = mat_albedo.Sample(smpl, uv) * float4(mat_albedo_color, 1.0f);
	output.normal = float4(normalize(normal), 1.0f);

	return (output);
}
