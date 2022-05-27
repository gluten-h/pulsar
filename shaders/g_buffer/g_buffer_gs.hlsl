
struct gs_in
{
	float4	pos : SV_POSITION;
	float4	world_pos : POSITION;
	float3	normal : NORMAL;
	float2	uv : UV;
};

struct gs_out
{
	float4	pos : SV_POSITION;
	float4	world_pos : POSITION;
	float3	normal : NORMAL;
	float2	uv : UV;

	nointerpolation float3	t : TANGENT0;
	nointerpolation float3	b : TANGENT1;
};


[maxvertexcount(3)]
void	geom(triangle gs_in input[3], inout TriangleStream<gs_out> output)
{
	gs_out tri[3];

	float3 edge1 = input[1].world_pos - input[0].world_pos;
	float3 edge2 = input[2].world_pos - input[0].world_pos;
	float2 delta_uv1 = input[1].uv - input[0].uv;
	float2 delta_uv2 = input[2].uv - input[0].uv;
	float f = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv2.x * delta_uv1.y);

	float3 t;
	t.x = f * (delta_uv2.y * edge1.x - delta_uv1.y * edge2.x);
	t.y = f * (delta_uv2.y * edge1.y - delta_uv1.y * edge2.y);
	t.z = f * (delta_uv2.y * edge1.z - delta_uv1.y * edge2.z);
	t = normalize(t);

	float3 b;
	b.x = f * (-delta_uv2.x * edge1.x + delta_uv1.x * edge2.x);
	b.y = f * (-delta_uv2.x * edge1.y + delta_uv1.x * edge2.y);
	b.z = f * (-delta_uv2.x * edge1.z + delta_uv1.x * edge2.z);
	b = normalize(b);

	for (uint i = 0; i < 3; i++)
	{
		tri[i].pos = input[i].pos;
		tri[i].world_pos = input[i].world_pos;
		tri[i].normal = input[i].normal;
		tri[i].uv = input[i].uv;

		tri[i].t = t;
		tri[i].b = b;

		output.Append(tri[i]);
	}
}