
float2	sample_cubemap(float3 d, out uint face_id)
{
	float3 d_abs = abs(d);
	float ma;
	float2 uv;

	if (d_abs.z >= d_abs.x && d_abs.z >= d_abs.y)
	{
		face_id = d.z < 0.0f ? 5 : 4;
		ma = 0.5f / d_abs.z;
		uv = float2(d.z < 0.0f ? -d.x : d.x, -d.y);
	}
	else if (d_abs.y >= d_abs.x)
	{
		face_id = d.y < 0.0f ? 3 : 2;
		ma = 0.5f / d_abs.y;
		uv = float2(d.x, d.y < 0.0f ? -d.z : d.z);
	}
	else
	{
		face_id = d.x < 0.0f ? 1 : 0;
		ma = 0.5f / d_abs.x;
		uv = float2(d.x < 0.0f ? d.z : -d.z, -d.y);
	}

	return (uv * ma + 0.5f);
}
