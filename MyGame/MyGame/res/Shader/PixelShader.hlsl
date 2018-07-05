#include"DxLibPixelShader.hlsli"

struct PS_INPUT {
	float2 TexCoord:TEXCOORD0;//テクスチャ座標
	float3 WTangent:TEXCOORD1;//接線
	float3 WBinormal:TEXCOORD2;//従法線
	float3 WNormal:TEXCOORD3;//法線
	float4 WPosition:TEXCOORD4;//ライト方向ベクトル
	float4 Position:SV_POSITION;//プロジェクション座標

};

struct PS_OUTPUT {
	float4 Color0:SV_TARGET0;//色
};

//ディフューズは簡易版のまま
//スペキュラを物理ベースでの計算
//ラフネス(表面をつるつる0.0f～ザラザラ1.0fに、質感を決める)

//ディフューズマップ
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);

//法線マップ
SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);

//スペキュラマップ
SamplerState g_SpecularMapSampler:register(s2);
Texture2D g_SpecularMapTexture:register(t2);

//アンビエントオクルージョンマップ
SamplerState g_AoMapSampler:register(s3);
Texture2D g_AoMapTexture:register(t3);

//IBLスペキュラ環境マップ(環境マップを光源にする,キューブマップ)
SamplerState g_IBLSpecularMapSampler:register(s11);
TextureCube g_IBLSpecularMapTexture:register(t11);

//IBLディフューズ環境マップ(環境マップを光源にする,キューブマップ)
SamplerState g_IBLDiffuseMapSampler:register(s12);
TextureCube g_IBLDiffuseMapTexture:register(t12);

//IBLBRDFマップ(通常の2Dテクスチャ)
SamplerState g_IBLBRDFMapSampler:register(s13);
Texture2D g_IBLBRDFMapTexture:register(t13);

cbuffer PixrrlShaderCB:register(b4) {
	float4 g_WorldViewPosition;//視点位置
	float4 g_WorldLightPosition;//ライト位置
	float4 g_LightColor;//ライトカラー
}

static const float PI = 3.1415926;
static const float u_mipmap_scale = 9;
static const float u_rim_scale = 1.0;

//拡散反射光の正規化
float phong_diffuse() {
	return (1.0 / PI);
}

//フレネル反射光の計算
float3 fresnel_factor(float3 f0, float product) {
	return f0 + (1.0 - f0)*pow(1.01 - product, 5.0);
}

//マイクロファセット分布の計算 Trowbridge-Reitz(GGX) 表面上にある傷(ザラザラ=傷が多い、ツルツル=傷が少ない)の表現(マイクロファセット=微小面)(表面の粗さの表現)
float D_GGX(float roughness, float NdH) {
	float m = roughness*roughness;
	float m2 = m*m;
	float d = (NdH* m2 - NdH)*NdH + 1.0;
	return m2 / (PI*d*d);
}

//幾何減衰率の計算(表面の粗さを表現する、旧計算だとShininessで行う必要があった)
float G_schlick(float roughness, float NdV, float NdL) {
	float k = roughness*roughness*0.5;
	float V = NdV*(1.0 - k) + k;
	float L = NdL*(1.0 - k) + k;
	return min(2.0, 0.36 / (V*L));
}

//クックトランスの鏡面反射モデルの計算(フォンモデルとは違った計算、金属のツヤ部分の計算式、此方の方がツヤ感がリアル)
float3 cooktorrance_specular(float NdL, float NdV, float NdH, float3 F, float roughness) {
	float D = D_GGX(roughness, NdH);
	float G = G_schlick(roughness, NdV, NdL);
	float rim = lerp(1.0 - roughness*u_rim_scale*0.9, 1.0, NdV);
	return min((F*G*D) / rim, 1.0);
}

//ノンリニア空間からリニア空間に変換(テクスチャRGB値の調整)
float3 convert_to_linear(float3 color) {
	return pow(color, 2.2);
}

//リニア空間からノンリニア空間に変換
float3 convert_to_none_linear(float3 color) {
	return pow(color, 1 / 2.2);
}


PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;

	float3x3 matTBN = float3x3(normalize(PSInput.WTangent), normalize(PSInput.WBinormal), normalize(PSInput.WNormal));
	float3 N = mul(normalize(g_NormalMapTexture.Sample(g_NormalMapSampler, PSInput.TexCoord).xyz*2.0 - 1.0), matTBN);
	float3 V = normalize(g_WorldViewPosition.xyz - PSInput.WPosition.xyz);
	float3 L = normalize(g_WorldLightPosition.xyz - PSInput.WPosition.xyz);
	float3 H = normalize(L + V);
	float3 R = reflect(-V, N);//環境マップ用

	float NdL = max(0.0001, dot(N, L));//0.0001は0除算回避のため、dotはベクトルの向きの差を調べている
	float NdV = max(0.0001, dot(N, V));//0.0001は0除算回避のため、dotはベクトルの向きの差を調べている
	float NdH = max(0.0001, dot(N, H));//0.0001は0除算回避のため、dotはベクトルの向きの差を調べている
	float HdV = max(0.0001, dot(H, V));//0.0001は0除算回避のため、dotはベクトルの向きの差を調べている
	float LdV = max(0.0001, dot(L, V));//0.0001は0除算回避のため、dotはベクトルの向きの差を調べている

	//アルベドカラー(非金属部分)
	float4 albedo_color = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoord.xy);
	albedo_color.rgb = convert_to_linear(albedo_color.rgb);
	//スペキュラカラー(金属部分)
	float4 specular_color = g_SpecularMapTexture.Sample(g_SpecularMapSampler, PSInput.TexCoord.xy);
	specular_color.rgb = convert_to_linear(albedo_color.rgb);
	//ラフネス(0:ツルツル～1:ザラザラ)　UnityのSmoothness(ラフネスの逆版) こっちをラフネスに変える、SpecularMapのアルファ部分にスムースネスデータを入れとく
	float roughness = 1.0 - specular_color.a;
	//アンビエントオクルージョン(トゥーンレンダリング用の枠に無理やりテクスチャを入れとく)
	float ao = g_AoMapTexture.Sample(g_AoMapSampler, PSInput.TexCoord.xy).r;

	//物理ベースシェーダー用のライトカラーを計算(ディフューズのπの計算とのつじつま合わせのため=PIを外すと1/3の明るさになってしまうため,↓の方でディフューズ、スペキュラにπの計算をして正規化してるから)
	float3 light_color = g_LightColor.rgb*PI;

	//鏡面反射光を求める
	float3 specular_fresnel = fresnel_factor(specular_color.rgb, HdV);
	float3 specular_reflectance = cooktorrance_specular(NdL, NdV, NdH, specular_fresnel, roughness)*NdL;

	//環境BRDFの計算(キューブマップからとってきたリフレクションの情報)
	float2 brdf = g_IBLBRDFMapTexture.Sample(g_IBLBRDFMapSampler, float2(NdV, 1.0 - roughness)).xy;
	float3 ibl_specular = min(0.99, specular_color.rgb*brdf.x + brdf.y);
	//環境鏡面反射の計算
	float3 env_specular = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, R, roughness*u_mipmap_scale).xyz;
	//最終的な鏡面反射光の計算(ラフネスを考慮して、ザラザラ感を)
	float3 specular_light = (specular_reflectance*light_color) + (env_specular*ibl_specular);
	//拡散反射光を求める(おうめんれいやーもでる)
	float3 diffuse_color = albedo_color.xyz;
	float3 diffuse_reflectance = diffuse_color*NdL*phong_diffuse();
	//環境拡散反射の計算
	float3 env_diffuse = g_IBLDiffuseMapTexture.Sample(g_IBLDiffuseMapSampler, N).xyz*phong_diffuse();
	//最終的な拡散反射光の計算
	float3 diffuse_light = (diffuse_reflectance*light_color) + (env_diffuse*diffuse_color);

	//最終的な光の計算
	float3 final_light = (diffuse_light + specular_light)*ao;
	PSOutput.Color0.rgb = convert_to_none_linear(final_light);
	PSOutput.Color0.a = albedo_color.a;

	return PSOutput;
}