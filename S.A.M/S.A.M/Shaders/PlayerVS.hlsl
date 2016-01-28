cbuffer worldPosition : register(b0)
{
	float4x4 World;
	float4 Position;
};

struct PlayerVS_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
};

struct PlayerVS_OUT
{
	float4 PosInW : POSINW;
	float2 Tex : TEXCOORD;
};

PlayerVS_OUT VS_main(PlayerVS_IN input)
{
	PlayerVS_OUT output = (PlayerVS_OUT)0;

	output.PosInW = mul(float4(input.Pos, 1), World) + Position;

	output.Tex = input.Tex;

	return output;
}