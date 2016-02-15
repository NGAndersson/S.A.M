cbuffer instancePartBuffer : register(b1)
{
	float4 instancePos[20];
};

struct VS_IN
{
	float4 Pos : POSITION;
};

struct VS_OUT
{
	float4 Pos : POS;
	float4 CenterPos : CenterPos;
};

VS_OUT VS_main(VS_IN input, uint instanceID : SV_InstanceID)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = float4((input.Pos + instancePos[instanceID]).xyz, 1);
	output.CenterPos = float4(instancePos[instanceID].xyz, 1);

	return output;
}