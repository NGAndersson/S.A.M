cbuffer CameraViewProject : register(b0)
{
	float4 CameraPos;
	float4x4 ViewProjection;
};

struct GS_IN
{
	float4 PosInW : WORLDPOS;
	float2 Tex : TEXCOORD;
};

struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD;
};


[maxvertexcount(3)]
void GS_main(triangle GS_IN input[3], inout TriangleStream< GS_OUT > streamOutput)
{
	GS_OUT output = (GS_OUT)0;

	float3 Vec1 = normalize(input[1].PosInW - input[0].PosInW);
	float3 Vec2 = normalize(input[2].PosInW - input[0].PosInW);
	float3 Norm = cross(Vec1, Vec2);
	float3 VnPosCam = float3(input[0].PosInW.x - CameraPos.x, input[0].PosInW.y - CameraPos.y, input[0].PosInW.z - CameraPos.z);
	float dotNP = dot(VnPosCam, Norm);

	if (dotNP <= 0)
	{
		for (int i = 0; i < 3; i++)
		{
			output.Pos = mul(input[i].PosInW, ViewProjection);
			output.Tex = input[i].Tex;
			streamOutput.Append(output);
		}
		streamOutput.RestartStrip();
	}
}