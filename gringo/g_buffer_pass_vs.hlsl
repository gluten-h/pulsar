
cbuffer transform_cb : register (b0)
{
    matrix model;
    matrix view;
    matrix proj;
    matrix norm;
};


struct v_out
{
    float4 pos : SV_POSITION;
    float4 world_pos : POSITION;
    float3 normal : NORMAL;
    float2 uv : UV;
};

v_out       vert(float3 pos : POSITION, float3 normal : NORMAL, float2 uv : UV)
{
    v_out output;

    output.pos = mul(proj, mul(view, mul(model, float4(pos, 1.0f))));
    output.world_pos = mul(model, float4(pos, 1.0f));
    output.normal = mul((float3x3)norm, normal);
    output.uv = uv;

    return (output);
}
