
float	frag(float4 pos : SV_POSITION, float4 world_view_pos : POSITION0) : SV_TARGET
{
	float depth = length(world_view_pos.xyz);
	return (depth);
}
