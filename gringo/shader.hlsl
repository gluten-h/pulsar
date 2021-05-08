
cbuffer cv_buffer
{
    matrix cv_world;
    matrix cv_view;
    matrix cv_proj;
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

    //output.pos = mul(mul(mul(float4(pos, 1.0f), cv_world), cv_view), cv_proj);
    output.pos = mul(cv_proj, mul(cv_view, mul(cv_world, float4(pos, 1.0f))));
    output.normal = normal;
    output.uv = uv;

    return (output);
}


float4  frag(float4 pos : SV_POSITION, float3 normal : NORMAL, float2 uv : UV) : SV_TARGET
{
    return (float4(abs(normal), 1.0f));
}