
float3		get_point_light_dir(float3 l_pos, float3 pos)
{
	return (normalize(l_pos - pos));
}
