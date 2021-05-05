
cbuffer cv_buffer
{
    matrix transform;
};


struct v_out
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
};

v_out   vert(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV)
{
    v_out output;

    output.pos = mul(float4(pos, 1.0f), transform);
    output.normal = normal;
    output.uv = uv;

    return (output);
}


float4  frag(float4 pos : SV_POSITION, float3 normal : NORMAL, float2 uv : UV) : SV_TARGET
{
    return (float4(abs(normal), 1.0f));
}