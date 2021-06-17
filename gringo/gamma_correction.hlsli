
float3		srgb_to_linear(float3 color, float gamma)
{
	return (pow(color, float3(gamma, gamma, gamma)));
}

float3		gamma_correction(float3 color, float gamma)
{
	float c_gamma = 1.0f / gamma;
	float3 c_color = color / (color + float3(1.0f, 1.0f, 1.0f));
	
	return (pow(c_color, float3(c_gamma, c_gamma, c_gamma)));
}
