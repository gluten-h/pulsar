
float4	point_sample_texture_atlas(Texture2D texture_atlas, SamplerState smplr, float4 uv_rect, float2 rel_uv)
{
	float2 abs_uv = float2(lerp(uv_rect.x, uv_rect.z, rel_uv.x), lerp(uv_rect.y, uv_rect.w, rel_uv.y));
	return (texture_atlas.Sample(smplr, abs_uv));
}

float4	linear_sample_texture_atlas(Texture2D texture_atlas, SamplerState smplr, float4 uv_rect, float2 rel_uv)
{
	uint width, height;
	texture_atlas.GetDimensions(width, height);

	float2 abs_uv = float2(lerp(uv_rect.x, uv_rect.z, rel_uv.x), lerp(uv_rect.y, uv_rect.w, rel_uv.y));
	float2 pixel = abs_uv * float(width) + 0.5f;
	float2 fract = frac(pixel);

	float4 red_all = texture_atlas.GatherRed(smplr, abs_uv);
	float top_red = lerp(red_all.w, red_all.z, fract.x);
	float bottom_red = lerp(red_all.x, red_all.y, fract.x);
	float red = lerp(top_red, bottom_red, fract.y);

	float4 green_all = texture_atlas.GatherGreen(smplr, abs_uv);
	float top_green = lerp(green_all.w, green_all.z, fract.x);
	float bottom_green = lerp(green_all.x, green_all.y, fract.x);
	float green = lerp(top_green, bottom_green, fract.y);

	float4 blue_all = texture_atlas.GatherBlue(smplr, abs_uv);
	float top_blue = lerp(blue_all.w, blue_all.z, fract.x);
	float bottom_blue = lerp(blue_all.x, blue_all.y, fract.x);
	float blue = lerp(top_blue, bottom_blue, fract.y);

	float4 alpha_all = texture_atlas.GatherAlpha(smplr, abs_uv);
	float top_alpha = lerp(alpha_all.w, alpha_all.z, fract.x);
	float bottom_alpha = lerp(alpha_all.x, alpha_all.y, fract.x);
	float alpha = lerp(top_alpha, bottom_alpha, fract.y);

	return (float4(red, green, blue, alpha));
}
