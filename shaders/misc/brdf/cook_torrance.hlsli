
float	distribution_ggx(float3 normal, float3 halfway_dir, float roughness)
{
	float r2 = roughness * roughness;
	float n_dot_h = max(0.0f, dot(normal, halfway_dir));
	float n_dot_h2 = n_dot_h * n_dot_h;

	float denom = (n_dot_h2 * (r2 - 1.0f) + 1.0f);
	denom = 3.14159265f * denom * denom;

	return (r2 / denom);
}

float	geometry_schlick_ggx(float n_dot_v, float roughness)
{
	float r = (roughness + 1.0f);
	float k = (r * r) / 8.0f;
	float denom = n_dot_v * (1.0 - k) + k;

	return (n_dot_v / denom);
}

float	geometry_smith(float3 normal, float3 view_dir, float3 light_dir, float roughness)
{
	float n_dot_v = max(0.0f, dot(normal, view_dir));
	float n_dot_l = max(0.0f, dot(normal, light_dir));
	float ggx1 = geometry_schlick_ggx(n_dot_v, roughness);
	float ggx2 = geometry_schlick_ggx(n_dot_l, roughness);

	return (ggx1 * ggx2);
}

float3	fresnel_schlick(float cost, float3 f0, float roughness)
{
	return (f0 + (max(float3(1.0f - roughness, 1.0f - roughness, 1.0f - roughness), f0) - f0) * pow(1.0f - cost, 5.0f));
}

float3	cook_torrance(float3 view_dir, float3 light_dir, float3 halfway_dir, float3 normal, float3 F, float roughness)
{
	float NDF = distribution_ggx(normal, halfway_dir, roughness);
	float G = geometry_smith(normal, view_dir, light_dir, roughness);

	float3 num = NDF * G * F;
	float denom = 4.0f * max(0.0f, dot(normal, view_dir)) * max(0.0f, dot(normal, light_dir));
	denom = max(0.001f, denom);
	float3 brdf = num / denom;
	
	return (brdf);
}
