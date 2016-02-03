cbuffer CameraViewProject : register(b0)
{
	float4 CameraPos;
	float4x4 ViewProjection;
};

struct GS_IN
{
	float4 Pos : POS;
};

struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Position : POS;
	float2 Tex : TEXCOORD;
};

[maxvertexcount(6)]
void GS_main(point GS_IN input[1], inout TriangleStream< GS_OUT > streamOutput)
{
	GS_OUT output = (GS_OUT)0;

	float3 Normal = normalize(float3(CameraPos.x - input[0].Pos.x, CameraPos.y - input[0].Pos.y, CameraPos.z - input[0].Pos.z));
	float3 VekRi = normalize(cross(float3(0, 1, 0), Normal));
	float3 VekUp = normalize(cross(Normal, VekRi));

	output.Pos = mul(float4(input[0].Pos.xyz + VekRi - VekUp, 1), ViewProjection);
	output.Normal = Normal;
	output.Position = float3(input[0].Pos.xyz + VekRi - VekUp);
	output.Tex = float2(0, 0);
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz + VekRi + VekUp, 1), ViewProjection);
	output.Normal = Normal;
	output.Position = float3(input[0].Pos.xyz + VekRi + VekUp);
	output.Tex = float2(0, 1);
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz - VekRi + VekUp, 1), ViewProjection);
	output.Normal = Normal;
	output.Position = float3(input[0].Pos.xyz - VekRi + VekUp);
	output.Tex = float2(1, 1);
	streamOutput.Append(output);

	streamOutput.RestartStrip();

	output.Pos = mul(float4(input[0].Pos.xyz + VekRi - VekUp, 1), ViewProjection);
	output.Normal = Normal;
	output.Position = float3(input[0].Pos.xyz + VekRi - VekUp);
	output.Tex = float2(0, 0);
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz - VekRi + VekUp, 1), ViewProjection);
	output.Normal = Normal;
	output.Position = float3(input[0].Pos.xyz - VekRi + VekUp);
	output.Tex = float2(1, 1);
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz - VekRi - VekUp, 1), ViewProjection);
	output.Normal = Normal;
	output.Position = float3(input[0].Pos.xyz - VekRi - VekUp);
	output.Tex = float2(1, 0);
	streamOutput.Append(output);

	streamOutput.RestartStrip();
}