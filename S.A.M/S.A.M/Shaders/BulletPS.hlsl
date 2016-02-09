Texture2D ObjTex : register(t0);

SamplerState sampAni : register(s0);

cbuffer OBJColourType : register(b0)
{
	float3 Diffuse;
	float3 Albi;
	float3 Tf;
	float3 Ni;
};

cbuffer LightData : register(b1)
{
	float4 LightPos[6];
	float4 LightColor[6];
	float4 LightRange[6];
};

cbuffer CameraType : register(b2)
{
	float4 CameraPos;
	float4x4 ViewProjection;
};

struct PS_IN
{
	float4 Pos : SV_POSITION;
	float4 NormalInW : NORMALINW;
	float2 Tex : TEXCOORD;
};

float4 PS_main(PS_IN input) : SV_TARGET
{
	//float3 SpecularAlbedo = float3(0.5f, 0.5f, 0.5f);
	//float SpecularPower = 1.0f;

	//float3 TotLight = float3(0, 0, 0);
	//float3 Light = float3(0, 0, 0);
	//float Distance;
	//float Attenuation = 1.0f;
	//
	//for (int i = 0; i < LightRange[0].y; i++)
	//{
	//	if (LightRange[i].z == 0)	//pointLight
	//	{
	//		Light = input.Pos - LightPos[i].xyz;
	//		Distance = length(Light);
	//		Attenuation = max(0, 1.0f - (Distance / LightRange[i].x));	//Dämpning


	//		Light /= Distance;
	//	}
	//	else if (LightRange[i].z == 1)	//directional light
	//	{
	//		Light = -LightPos[i].xyz;
	//	}

	//	float NormalDotLight = saturate(dot(input.NormalInW, Light));
	//	float3 Diffuselight = NormalDotLight * LightColor[i].xyz * Diffuse;

	//	float3 V = CameraPos.xyz - input.Pos;
	//	float3 H = normalize(Light + V);
	//	float3 SpecularL = pow(saturate(dot(input.NormalInW, H)), SpecularPower) * LightColor[i].xyz * SpecularAlbedo.xyz * NormalDotLight;

	//	TotLight = ((Diffuse + SpecularL) * Attenuation) + TotLight;
	//}
	//if (TotLight.x == 0 && TotLight.y == 0 && TotLight.z == 0)
	//{
	//	return float4(0.2f, 0.2f, 0.5f, 1.0f);
	//}


	float3 pixelOut = ObjTex.Sample(sampAni, input.Tex).xyz;
	return float4(pixelOut + Diffuse, 1.0);
}