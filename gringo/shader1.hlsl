
cbuffer cv_buffer
{
    matrix transform;
};


struct v_out
{
    float4 pos : SV_POSITION;
};

v_out   vert(float3 pos : POSITION)
{
    v_out output;

    output.pos = mul(float4(pos, 1.0f), transform);

    return (output);
}


float4  frag(float4 pos : SV_POSITION) : SV_TARGET
{
    return (float4(1.0f, 1.0f, 1.0f, 1.0f));
}