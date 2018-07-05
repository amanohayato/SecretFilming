#include"DxLibVertexShader.hlsli"

//Tan, Binoを使う場合、デフォルトのVS_INPUTのデータの間部分を全て埋めておく必要がある(データのズレを起こさないため)
struct VS_INPUT {
	float4 Position:POSITION;//ローカル座標
	float3 Normal:NORMAL0;//法線
	float4 Diffuse : COLOR0;//ディフューズ
	float4 Specular:COLOR1;//スペキュラ
	float4 TexCoords0:TEXCOORD0;//テクスチャ座標0
	float4 TexCoords1:TEXCOORD1;//テクスチャ座標1
	float3 Tangent:TANGENT0;//接線
	float3 Binormal:BINORMAL0;//従法線
	int4 BlendIndices0:BLENDINDICES0;//ボーン処理用Float型定数配列インデックス0
	float4 BlendWeight0:BLENDWEIGHT0;//ボーン処理用ウェイト値0
};

struct VS_OUTPUT {
	float2 TexCoord:TEXCOORD0;//テクスチャ座標
	float3 WTangent:TEXCOORD1;//接線
	float3 WBinormal : TEXCOORD2;//従法線
	float3 WNormal:TEXCOORD3;//ワールド法線
	float4 WPosition:TEXCOORD4;//ワールド座標
	float4 Position:SV_POSITION;//正規化デバイス頂点座標

};

VS_OUTPUT main(VS_INPUT VSInput)
{
	VS_OUTPUT VSOutput;

	int4 lBoneFloatIndex;
	lBoneFloatIndex = VSInput.BlendIndices0;
	float4 lLocalWorldMatrix[3];
	lLocalWorldMatrix[0] = g_LocalWorldMatrix.Matrix[lBoneFloatIndex.x + 0] * VSInput.BlendWeight0.x;
	lLocalWorldMatrix[1] = g_LocalWorldMatrix.Matrix[lBoneFloatIndex.x + 1] * VSInput.BlendWeight0.x;
	lLocalWorldMatrix[2] = g_LocalWorldMatrix.Matrix[lBoneFloatIndex.x + 2] * VSInput.BlendWeight0.x;
	lLocalWorldMatrix[0] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.y + 0] * VSInput.BlendWeight0.y;
	lLocalWorldMatrix[1] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.y + 1] * VSInput.BlendWeight0.y;
	lLocalWorldMatrix[2] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.y + 2] * VSInput.BlendWeight0.y;
	lLocalWorldMatrix[0] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.z + 0] * VSInput.BlendWeight0.z;
	lLocalWorldMatrix[1] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.z + 1] * VSInput.BlendWeight0.z;
	lLocalWorldMatrix[2] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.z + 2] * VSInput.BlendWeight0.z;
	lLocalWorldMatrix[0] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.w + 0] * VSInput.BlendWeight0.w;
	lLocalWorldMatrix[1] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.w + 1] * VSInput.BlendWeight0.w;
	lLocalWorldMatrix[2] += g_LocalWorldMatrix.Matrix[lBoneFloatIndex.w + 2] * VSInput.BlendWeight0.w;

	//g_LocalWorldMatrixはルートのワールド変換行列
	VSOutput.WPosition.x = dot(VSInput.Position, lLocalWorldMatrix[0]);
	VSOutput.WPosition.y = dot(VSInput.Position, lLocalWorldMatrix[1]);
	VSOutput.WPosition.z = dot(VSInput.Position, lLocalWorldMatrix[2]);
	VSOutput.WPosition.w = 1.0;

	//視点座標系に変換
	float4 lViewPosition;
	lViewPosition.x = dot(VSOutput.WPosition, g_Base.ViewMatrix[0]);
	lViewPosition.y = dot(VSOutput.WPosition, g_Base.ViewMatrix[1]);
	lViewPosition.z = dot(VSOutput.WPosition, g_Base.ViewMatrix[2]);
	lViewPosition.w = 1.0;

	//正規化デバイス座標系に変換
	VSOutput.Position.x = dot(lViewPosition, g_Base.ProjectionMatrix[0]);
	VSOutput.Position.y = dot(lViewPosition, g_Base.ProjectionMatrix[1]);
	VSOutput.Position.z = dot(lViewPosition, g_Base.ProjectionMatrix[2]);
	VSOutput.Position.w = dot(lViewPosition, g_Base.ProjectionMatrix[3]);

	//法線ベクトルの座標変換(ワールド座標系に変換)
	VSOutput.WNormal.x = dot(VSInput.Normal, lLocalWorldMatrix[0].xyz);
	VSOutput.WNormal.y = dot(VSInput.Normal, lLocalWorldMatrix[1].xyz);
	VSOutput.WNormal.z = dot(VSInput.Normal, lLocalWorldMatrix[2].xyz);

	//接ベクトルの座標変換(ワールド座標系に変換)
	VSOutput.WTangent.x = dot(VSInput.Tangent, lLocalWorldMatrix[0].xyz);
	VSOutput.WTangent.y = dot(VSInput.Tangent, lLocalWorldMatrix[1].xyz);
	VSOutput.WTangent.z = dot(VSInput.Tangent, lLocalWorldMatrix[2].xyz);

	//従法線ベクトルの座標変換(ワールド座標系に変換)
	VSOutput.WBinormal.x = dot(VSInput.Binormal, lLocalWorldMatrix[0].xyz);
	VSOutput.WBinormal.y = dot(VSInput.Binormal, lLocalWorldMatrix[1].xyz);
	VSOutput.WBinormal.z = dot(VSInput.Binormal, lLocalWorldMatrix[2].xyz);

	VSOutput.TexCoord.xy = VSInput.TexCoords0.xy;//テクスチャ座標のセット

	return VSOutput;
}