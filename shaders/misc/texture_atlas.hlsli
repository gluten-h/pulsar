
#define SUBTEXEL_PRECISION_OFFSET 1.0f / 512.0f


float4	point_sample_texture_atlas(Texture2D texture_atlas, SamplerState point_sampler, float4 uv_rect, float2 rel_uv)
{
	float2 abs_uv = float2(lerp(uv_rect.x, uv_rect.z, rel_uv.x), lerp(uv_rect.y, uv_rect.w, rel_uv.y));
	return (texture_atlas.Sample(point_sampler, abs_uv));
}

float4	linear_sample_texture_atlas(Texture2D texture_atlas, SamplerState point_sampler, float4 uv_rect, float2 rel_uv)
{
	uint width, height;
	texture_atlas.GetDimensions(width, height);
	float2 texel_size = float2(1.0f / float(width), 1.0f / float(height));

	float2 abs_uv = float2(lerp(uv_rect.x, uv_rect.z, rel_uv.x), lerp(uv_rect.y, uv_rect.w, rel_uv.y));

	//don't know why but without this clamp stuff borders won't work properly
	abs_uv.x = clamp(abs_uv.x, uv_rect.x + texel_size.x * 0.5f + SUBTEXEL_PRECISION_OFFSET * texel_size.x, uv_rect.z - texel_size.x * 0.5f - SUBTEXEL_PRECISION_OFFSET * texel_size.x);
	abs_uv.y = clamp(abs_uv.y, uv_rect.y + texel_size.y * 0.5f + SUBTEXEL_PRECISION_OFFSET * texel_size.y, uv_rect.w - texel_size.y * 0.5f - SUBTEXEL_PRECISION_OFFSET * texel_size.y);

	float2 fract = frac(float2(abs_uv.x * float(width) - 0.5f + SUBTEXEL_PRECISION_OFFSET,
								abs_uv.y * float(height) - 0.5f + SUBTEXEL_PRECISION_OFFSET));

	// 0.0, 0.0 - top left
	// 1.0, 1.0 - bottom right
	float2 pix_pos = float2(fract.x > 0.5f, fract.y > 0.5f);

	float is_left_in_rect = abs_uv.x - texel_size.x * pix_pos.x >= uv_rect.x;
	float is_right_in_rect = abs_uv.x + texel_size.x * !pix_pos.x < uv_rect.z;
	float is_top_in_rect = abs_uv.y - texel_size.y * pix_pos.y >= uv_rect.y;
	float is_bottom_in_rect = abs_uv.y + texel_size.y * !pix_pos.y < uv_rect.w;

	float is_top_left_in_rect = is_left_in_rect && is_top_in_rect;
	float is_top_right_in_rect = is_right_in_rect && is_top_in_rect;
	float is_bottom_left_in_rect = is_left_in_rect && is_bottom_in_rect;
	float is_bottom_right_in_rect = is_right_in_rect && is_bottom_in_rect;

	float top_line_lerp = fract.x;
	float bottom_line_lerp = fract.x;
	float vert_line_lerp = fract.y;

	if (!is_top_left_in_rect)
		top_line_lerp = 1.0f;
	if (!is_top_right_in_rect)
		top_line_lerp = 0.0f;
	if (!is_bottom_left_in_rect)
		bottom_line_lerp = 1.0f;
	if (!is_bottom_right_in_rect)
		bottom_line_lerp = 0.0f;

	if (!is_top_left_in_rect && !is_top_right_in_rect)
		vert_line_lerp = 1.0f;
	else if (!is_bottom_left_in_rect && !is_bottom_right_in_rect)
		vert_line_lerp = 0.0f;

	float4 red_all = texture_atlas.GatherRed(point_sampler, abs_uv);
	float top_red = lerp(red_all.w, red_all.z, top_line_lerp);
	float bottom_red = lerp(red_all.x, red_all.y, bottom_line_lerp);
	float red = lerp(top_red, bottom_red, vert_line_lerp);

	float4 green_all = texture_atlas.GatherGreen(point_sampler, abs_uv);
	float top_green = lerp(green_all.w, green_all.z, top_line_lerp);
	float bottom_green = lerp(green_all.x, green_all.y, bottom_line_lerp);
	float green = lerp(top_green, bottom_green, vert_line_lerp);

	float4 blue_all = texture_atlas.GatherBlue(point_sampler, abs_uv);
	float top_blue = lerp(blue_all.w, blue_all.z, top_line_lerp);
	float bottom_blue = lerp(blue_all.x, blue_all.y, bottom_line_lerp);
	float blue = lerp(top_blue, bottom_blue, vert_line_lerp);

	float4 alpha_all = texture_atlas.GatherAlpha(point_sampler, abs_uv);
	float top_alpha = lerp(alpha_all.w, alpha_all.z, top_line_lerp);
	float bottom_alpha = lerp(alpha_all.x, alpha_all.y, bottom_line_lerp);
	float alpha = lerp(top_alpha, bottom_alpha, vert_line_lerp);

	return (float4(red, green, blue, alpha));
}
