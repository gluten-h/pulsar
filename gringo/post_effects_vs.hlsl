
struct vs_out
{
	float4 pos : SV_Position;
	float2 uv : UV;
};


vs_out vert(uint vI : SV_VERTEXID)
{
	vs_out output;

	output.uv = float2(vI & 1, vI >> 1);
	output.pos = float4((output.uv.x - 0.5f) * 2, -(output.uv.y - 0.5f) * 2, 0, 1);

	return (output);
}