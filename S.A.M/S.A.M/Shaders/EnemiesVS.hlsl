cbuffer worldPosition : register(b0)
{
	float4x4 World[100];
	float4x4 Rotation[100];
};

cbuffer healthColour : register(b2)
{
	float4	Colour[100];
}

struct VS_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
};

struct VS_OUT
{
	float4 PosInW : WORLDPOS;
	float4 NormalInW : NORMALINW;
	float4 Colour : COLOUR;
	float2 Tex : TEXCOORD;
};

VS_OUT VS_main(VS_IN input, uint instanceID : SV_InstanceID)
{
	VS_OUT output = (VS_OUT)0;

	output.PosInW = mul(float4(input.Pos, 1), World[instanceID]);
	output.NormalInW = normalize(mul(float4(input.Normal, 1), Rotation[instanceID]));
	output.Colour = Colour[instanceID];
	output.Tex = input.Tex;

	return output;
}