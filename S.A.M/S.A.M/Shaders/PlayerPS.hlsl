Texture2D ObjTex : register(t0);

SamplerState sampAni : register(s0);

cbuffer OBJColourType : register(b0)
{
	float3 Diffuse;
	float3 Albi;
	float3 Tf;
	float3 Ni;
};

struct PS_IN
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

float4 PS_main(PS_IN input) : SV_TARGET
{
	float3 pixelOut = ObjTex.Sample(sampAni, input.Tex).xyz;
	return float4(pixelOut + Diffuse, 1.0);
}