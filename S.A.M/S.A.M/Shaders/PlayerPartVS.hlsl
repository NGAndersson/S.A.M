struct VS_IN
{
	float4 Pos : POSITION;
	float4 SourcePos : SOURCEPOS;
};

struct VS_OUT
{
	float4 Pos : POS;
	float4 SourcePos : SOURCEPOS;
};

VS_OUT VS_main(VS_IN input)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = input.Pos;
	output.SourcePos = input.SourcePos;

	return output;
}