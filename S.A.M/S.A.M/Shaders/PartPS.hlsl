Texture2D PartTex : register(t0);

SamplerState sampAni : register(s0);

struct PS_IN
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Position : POS;
	float2 Tex : TEXCOORD;
};

float4 PS_main(PS_IN input) : SV_TARGET
{
	//return float4(1, 0, 0, 1.0);

	float3 pixelOut = PartTex.Sample(sampAni, input.Tex).xyz;
	return float4(pixelOut, 1.0);
}