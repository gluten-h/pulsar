
cbuffer cv_buffer
{
    matrix cv_world;
    matrix cv_view;
    matrix cv_proj;
};


struct v_out
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

v_out   vert(float3 pos : POSITION, float2 uv : UV)
{
    v_out output;

    //output.pos = mul(mul(mul(float4(pos, 1.0f), cv_world), cv_view), cv_proj);
    output.pos = mul(cv_proj, mul(cv_view, mul(cv_world, float4(pos, 1.0f))));
    output.uv = uv;

    return (output);
}


Texture2D tex;
SamplerState smpl;


float4  frag(float4 pos : SV_POSITION, float2 uv : UV) : SV_TARGET
{
    return (tex.Sample(smpl, uv));
}