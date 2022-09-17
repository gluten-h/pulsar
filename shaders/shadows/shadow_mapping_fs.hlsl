
float2	frag(float4 pos : SV_POSITION, float4 world_view_pos : POSITION0) : SV_TARGET
{
	float2 moments;
	float depth = length(world_view_pos.xyz);

	float dx = ddx(depth);
	float dy = ddy(depth);

	moments.x = depth;
	moments.y = depth * depth + 0.25f * (dx * dx + dy * dy);

	return (moments);
}
