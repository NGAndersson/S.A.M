cbuffer worldPosition : register(b0)
{
	float4x4 World[];
};

struct BulletVS_IN
{
	float3 Pos : POSITION;
	float2 Tex : TEXCOORD;
	float3 Normal : NORMAL;
};

struct BulletVS_OUT
{
	float4 PosInW : WORLDPOS;
	float2 Tex : TEXCOORD;
};

BulletVS_OUT VS_main(VS_IN input, uint instanceID : SV_InstanceID)
{
	BulletVS_OUT output = (BulletVS_OUT)0;

	output.PosInW = mul(float4(input.Pos, 1), World[instanceID]);
	output.Tex = input.Tex;

	return output;
}