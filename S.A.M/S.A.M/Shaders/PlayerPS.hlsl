Texture2D ObjTex : register(t6);

SamplerState sampAni : register(s0);

cbuffer OBJColourType : register(b0)
{
	float3 Deffuse;
	float3 Albi;
	float3 Tf;
	float3 Ni;
};

struct PlayerPS_IN
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};

float4 PS_main(PlayerPS_IN input) : SV_TARGET
{
	float3 pixelOut = ObjTex.Sample(sampAni, input.Tex).xyz;
	return float4(1.0f, 0.0f, 0.0f, 0.0f);
	return float4(pixelOut + Deffuse, 1.0);
}