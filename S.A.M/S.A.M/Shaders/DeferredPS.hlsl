// Textures
Texture2D NormalTex : register(t0);
Texture2D DiffuseAlbedoTex : register(t1);
Texture2D SpecularAlbedoTex : register(t2);
Texture2D PositionTex : register(t3);

//Constants
cbuffer LightData : register(b1)
{
	float4 LightPos[200];
	float4 LightColor[200];
	float4 LightRange[200];
};

cbuffer CameraType : register(b2)
{
	float4 CameraPos;
	float4x4 ViewProjection;
};



struct PS_IN
{
	float4 Pos : SV_POSITION;
};

float4 PS_main(PS_IN input) : SV_TARGET
{
	int3 ScreenPos = int3(input.Pos.xy, 0);
	float3 Normal = NormalTex.Load(ScreenPos).xyz;
	float3 DiffuseLight = DiffuseAlbedoTex.Load(ScreenPos).xyz;
	float4 Specular = SpecularAlbedoTex.Load(ScreenPos);
	float3 Pos = PositionTex.Load(ScreenPos).xyz;


	float3 SpecularAlbedo = Specular.xyz;
	float SpecularPower = Specular.w;
	Normal = normalize(Normal);

	float Attenuation = 1.0f;
	float3 TotLight = float3(0, 0, 0);
	float3 Light = float3(0, 0, 0);
	float Distance;


	for (int i = 0; i < LightRange[0].y; i++)
	{
		if (LightRange[i].z == 0)	//pointLight
		{
			Light = Pos - LightPos[i].xyz;
			Distance = length(Light);
			Attenuation = max(0, 1.0f - (Distance / LightRange[i].x));	//D�mpning


			Light /= Distance;
		}
		else if (LightRange[i].z == 1)	//directional light
		{
			Light = -LightPos[i].xyz;
		}

		float NormalDotLight = saturate(dot(Normal, Light));
		float3 Diffuse = NormalDotLight * LightColor[i].xyz * DiffuseLight;
		float3 V = CameraPos.xyz - Pos;
		float3 H = normalize(Light + V);
		float3 SpecularL = pow(saturate(dot(Normal, H)), SpecularPower) * LightColor[i].xyz * SpecularAlbedo.xyz * NormalDotLight;

		TotLight = ((Diffuse + SpecularL) * Attenuation) + TotLight;
	}
	TotLight = TotLight + (float3(0.3, 0.3, 0.3) * DiffuseLight);

	return float4(TotLight, 1.0f);
}