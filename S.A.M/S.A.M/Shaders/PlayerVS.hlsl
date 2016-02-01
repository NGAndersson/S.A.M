cbuffer worldPosition : register(b0)
{
	float4x4 World;
	float3 Position;
};

cbuffer CameraViewProject : register(b1)
{
	float4 CameraPos;
	float4x4 ViewProjection;
};

struct PlayerVS_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
};

struct PlayerVS_OUT
{
	float4 PosInW : WORLDPOS;
	float2 Tex : TEXCOORD;
	float4 Pos : SV_POSITION;
};

PlayerVS_OUT VS_main(PlayerVS_IN input)
{
	PlayerVS_OUT output = (PlayerVS_OUT)0;

	output.PosInW = mul(float4(input.Pos, 1), World);// +float4(Position, 0.0f);
	output.Pos = mul(output.PosInW, ViewProjection);

	//output.PosInW = float4(input.Pos, 1.0f);
	//output.Pos = float4(input.Pos.x, input.Pos.y, input.Pos.z+0.51f, 1.0f);
	output.Tex = input.Tex;

	return output;
}