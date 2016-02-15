cbuffer CameraViewProject : register(b0)
{
	float4 CameraPos;
	float4x4 ViewProjection;
};

struct GS_IN
{
	float4 Pos : POS;
	float4 CenterPos : CENTERPOS;
};

struct GS_OUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL;
	float3 Position : POS;
	float2 Tex : TEXCOORD;
	float4 CenterPos : CENTERPOS;
};

[maxvertexcount(6)]
void GS_main(point GS_IN input[1], inout TriangleStream< GS_OUT > streamOutput)
{
	GS_OUT output = (GS_OUT)0;

	float3 _Normal = normalize(float3(CameraPos.x - input[0].Pos.x, CameraPos.y - input[0].Pos.y, CameraPos.z - input[0].Pos.z));
	float3 _VekRi = normalize(cross(float3(0, 1, 0), _Normal));
	float3 _VekUp = normalize(cross(_Normal, _VekRi));
	_VekUp = _VekUp / 10;
	_VekRi = _VekRi / 10;

	output.Pos = mul(float4(input[0].Pos.xyz + _VekRi - _VekUp, 1), ViewProjection);
	output.Normal = _Normal;
	output.Position = float3(input[0].Pos.xyz + _VekRi - _VekUp);
	output.Tex = float2(0, 0);
	output.CenterPos = input[0].CenterPos;
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz + _VekRi + _VekUp, 1), ViewProjection);
	output.Normal = _Normal;
	output.Position = float3(input[0].Pos.xyz + _VekRi + _VekUp);
	output.Tex = float2(0, 1);
	output.CenterPos = input[0].CenterPos;
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz - _VekRi + _VekUp , 1), ViewProjection);
	output.Normal = _Normal;
	output.Position = float3(input[0].Pos.xyz - _VekRi + _VekUp );
	output.Tex = float2(1, 1);
	output.CenterPos = input[0].CenterPos;
	streamOutput.Append(output);

	streamOutput.RestartStrip();

	output.Pos = mul(float4(input[0].Pos.xyz + _VekRi - _VekUp, 1), ViewProjection);
	output.Normal = _Normal;
	output.Position = float3(input[0].Pos.xyz + _VekRi - _VekUp );
	output.Tex = float2(0, 0);
	output.CenterPos = input[0].CenterPos;
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz - _VekRi + _VekUp, 1), ViewProjection);
	output.Normal = _Normal;
	output.Position = float3(input[0].Pos.xyz - _VekRi + _VekUp);
	output.Tex = float2(1, 1);
	output.CenterPos = input[0].CenterPos;
	streamOutput.Append(output);

	output.Pos = mul(float4(input[0].Pos.xyz - _VekRi - _VekUp, 1), ViewProjection);
	output.Normal = _Normal;
	output.Position = float3(input[0].Pos.xyz - _VekRi - _VekUp);
	output.Tex = float2(1, 0);
	output.CenterPos = input[0].CenterPos;
	streamOutput.Append(output);

	streamOutput.RestartStrip();
}