struct VSout
{
	float3 color : COLOR;
	float4 pos : SV_POSITION;
};

cbuffer CBuf
{
	matrix transform;
};

VSout main( float3 pos : POSITION, float3 color : COLOR)
{
	VSout vsout;
	vsout.color = color;
	vsout.pos = mul(float4(pos, 1.0f), transform);
	return vsout;
}