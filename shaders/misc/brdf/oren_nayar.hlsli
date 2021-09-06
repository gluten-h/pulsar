
float3		oren_nayar(float3 view_dir, float3 light_dir, float3 normal, float3 albedo, float roughness)
{
	float n_dot_l = dot(normal, light_dir);
	float n_dot_v = dot(normal, view_dir);
	float l_dot_v = dot(light_dir, view_dir);
	
	float s = l_dot_v - n_dot_l * n_dot_v;
	float t = lerp(1.0f, max(n_dot_l, n_dot_v), step(0.0f, s));
	
	float r2 = roughness * roughness;
	float3 A = 1.0f + r2 * (albedo / (r2 + 0.13f) + 0.5f / (r2 + 0.33f));
	float B = 0.45f * r2 / (r2 + 0.09f);
	
	return (albedo * max(0.0f, n_dot_l) * (A + B * s / t) / 3.14159265f);
}
