/* http://developer.download.nvidia.com/CgTutorial/cg_tutorial_chapter05.html*/
Texture2D txDiffuse : register(t0);
SamplerState samLinear : register(s0);

cbuffer cbNeverChanges : register(b0)
{
	matrix View;
};

cbuffer cbChangeOnResize : register(b1)
{
	matrix Projection;
};

cbuffer cbChangesEveryFrame : register(b2)
{
	matrix World;
	float4 vMeshColor;
};

cbuffer cbLightingBuffer : register(b3)
{
	matrix Ignore;
	float3 globalAmbient;
	float3 lightColor;
	float3 lightPosition;
	float3 eyePosition;
	float3 Ke;
	float3 Ka;
	float3 Kd;
	float3 Ks;
	float shininess;
};

//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 Tex : TEXCOORD0;
	float3 Norm : NORMAL;
	float4 color : COLOR;
};
struct LIGHT_INPUT
{
	VS_INPUT Input;
	float3 globalAmbient;
	float3 lightColor;
	float3 lightPosition;
	float3 eyePosition;
	float3 Ke;
	float3 Ka;
	float3 Kd;
	float3 Ks;
	float shininess;
};
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Norm : NORMAL;
	float4 color : COLOR;
};
float4 C5E1v_basicLight(LIGHT_INPUT input)
{

	float4 ret;
	return ret;


	//float3 P = input.Input.Pos.xyz;

	//float3 N = input.Input.Norm;



	//// Compute the emissive term

	//float3 emissive = input.Ke;



	////// Compute the ambient term

	////float3 ambient = Ka * globalAmbient;



	////// Compute the diffuse term

	////float3 L = normalize(lightPosition - P);

	////float diffuseLight = max(dot(N, L), 0);

	////float3 diffuse = Kd * lightColor * diffuseLight;



	////// Compute the specular term

	////float3 V = normalize(eyePosition - P);

	////float3 H = normalize(L + V);

	////float specularLight = pow(max(dot(N, H), 0),

	////	shininess);

	////if (diffuseLight <= 0) specularLight = 0;

	////float3 specular = Ks * lightColor * specularLight;



	////input.color.xyz = emissive;//+ ambient + diffuse + specular;

	//input.color.w = 1;
	//return input.color;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;
	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Tex = input.Tex;
	output.Norm = mul(float4(input.Norm, 1), World).xyz;
	output.color.xyz = Ke.xyz;
	return output;
};




//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------


float4 PS(PS_INPUT input) : SV_Target
{
	float4  finalColor;
finalColor.xyz = input.color;
finalColor.a = 1;
return finalColor;
};

