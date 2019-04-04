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
	float E = 0;
	float3 lightColor;
	float E1 = 1;
	float3 lightPosition;
	float E2 = 1;
	float3 eyePosition;
	float E3 = 1;
	float3 Ke;
	float E4 = 1;
	float3 Ka;
	float E5 = 1;
	float3 Kd;
	float E6 = 1;
	float3 Ks;
	float E7 = 1;
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
struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 Tex : TEXCOORD0;
	float3 Norm : NORMAL;
	float4 color : COLOR;
};
float4 C5E1v_basicLight(VS_INPUT input)
{

	float3 P = input.Pos.xyz;

	float3 N = input.Norm;



	 //Compute the emissive term

	float3 emissive = Ke.xyz;



	// Compute the ambient term

	float3 ambient = Ka * globalAmbient;



	// Compute the diffuse term

	float3 L = normalize(lightPosition - P);

	float diffuseLight = max(dot(N, L), 0);

	float3 diffuse = Kd * lightColor * diffuseLight;



	// Compute the specular term

	float3 V = normalize(eyePosition - P);

	float3 H = normalize(L + V);

	float specularLight = pow(max(dot(N, H), 0),

		shininess);

	if (diffuseLight <= 0) specularLight = 0;

	float3 specular = Ks * lightColor * specularLight;


	float4 color;
	color.xyz = emissive + ambient + diffuse + specular;

	color.w = 1;
	return color;
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
	output.color = C5E1v_basicLight(input);
	return output;
};




//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------


float4 PS(PS_INPUT input) : SV_Target
{
	float4  finalColor;
finalColor.xyz = input.color.xyz;
finalColor.a = 1;
//return finalColor;
return txDiffuse.Sample(samLinear, input.Tex) * finalColor;
};

