
float3		tone_mapping(float3 hdr_color, float exposure)
{
	float3 mapped = float3(1.0f, 1.0f, 1.0f) - exp(-hdr_color * exposure);

	return (mapped);
}
