struct VS_IN
{
	float4 Pos : POSITION;
};

struct VS_OUT
{
	float4 Pos : POS;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = input.Pos;

	return output;
}