struct PS_INPUT
{
	float4 Diffuse         : COLOR0;
	float4 Specular        : COLOR1;
	float2 TexCoords0      : TEXCOORD0;
	float2 TexCoords1      : TEXCOORD1;
};

struct PS_OUTPUT
{
	float4 Output          : SV_TARGET0;
};
// ï`âÊÉJÉâÅ[Ç…èÊéZÇ∑ÇÈíl
cbuffer PERCENT_CBUFFER : register(b4)
{
	float4	percent;
}
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);

PS_OUTPUT main(PS_INPUT psin)
{
	PS_OUTPUT psout;
	float4 texc;
	float maxPercent = 100.0;
	texc = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, psin.TexCoords0.xy);
	float isDraw = clamp(sign(((1.0-psin.TexCoords0.y)*maxPercent) - percent.x), 0.0, 1.0);
	isDraw = 1.0 - isDraw;
	psout.Output.r = texc.r*isDraw;
	psout.Output.g = texc.g*isDraw;
	psout.Output.b = texc.b*isDraw;
	psout.Output.a = texc.a*isDraw;

	return psout;
}