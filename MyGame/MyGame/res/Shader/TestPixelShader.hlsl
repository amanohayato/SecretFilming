#include"DxLibPixelShader.hlsli"

// ピクセルシェーダーの入力
struct PS_INPUT
{
	float2 TexCoord:TEXCOORD0;//テクスチャ座標
	float3 WTangent:TEXCOORD1;//接線
	float3 WBinormal : TEXCOORD2;//従法線
	float3 WNormal:TEXCOORD3;//ワールド法線
	float4 WPosition:TEXCOORD4;//ワールド座標
	float4 Position:SV_POSITION;//正規化デバイス頂点座標
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 Color0          : SV_TARGET0;
};


//ディフューズマップ
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);

															// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float4 albedo_color = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoord.xy);

	// 出力カラー = テクスチャカラー
	PSOutput.Color0 = float4(albedo_color);

	// 出力パラメータを返す
	return PSOutput;
}