

cbuffer transform_cb : register(b0)
{
	matrix view;
	matrix proj;
}


float4 main( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}