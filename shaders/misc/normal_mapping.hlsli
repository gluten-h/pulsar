
float3		normal_mapping(float3 t, float3 b, float3 n, float3 normal_map_value, float normal_factor)
{
	float3 map_n = normal_map_value * 2.0f - 1.0f;
	map_n.x *= normal_factor;
	map_n.y *= normal_factor;
	float3x3 tbn = float3x3(t, b, n);
	float3 normal_out = normalize(mul(transpose(tbn), map_n));

	return (normal_out);
}
