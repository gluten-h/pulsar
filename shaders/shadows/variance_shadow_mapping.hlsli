
#define MIN_VARIANCE 0.00002f


float	linstep(float min, float max, float v)
{
	return (clamp((v - min) / (max - min), 0.0f, 1.0f));
}

float	variance_shadow_mapping(float2 moments, float light_dist)
{
	float p = step(light_dist, moments.x);
	float variance = max(MIN_VARIANCE, moments.y - moments.x * moments.x);
	float d = light_dist - moments.x;
	float p_max = linstep(0.3f, 1.0f, variance / (variance + d * d)); // 0.3 isn't supposed to be hardcoded, it should be loaded to the shader

	return (max(p, p_max));
}
