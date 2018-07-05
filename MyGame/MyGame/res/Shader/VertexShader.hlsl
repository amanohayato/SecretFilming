#include"DxLibVertexShader.hlsli"

//Tan, Bino���g���ꍇ�A�f�t�H���g��VS_INPUT�̃f�[�^�̊ԕ�����S�Ė��߂Ă����K�v������(�f�[�^�̃Y�����N�����Ȃ�����)
struct VS_INPUT {
	float4 Position:POSITION;//���[�J�����W
	float3 Normal:NORMAL0;//�@��
	float4 Diffuse : COLOR0;//�f�B�t���[�Y
	float4 Specular:COLOR1;//�X�y�L����
	float4 TexCoords0:TEXCOORD0;//�e�N�X�`�����W0
	float4 TexCoords1:TEXCOORD1;//�e�N�X�`�����W1
	float3 Tangent:TANGENT0;//�ڐ�
	float3 Binormal:BINORMAL0;//�]�@��
	int4 BlendIndices0:BLENDINDICES0;//�{�[�������pFloat�^�萔�z��C���f�b�N�X0
	float4 BlendWeight0:BLENDWEIGHT0;//�{�[�������p�E�F�C�g�l0
};

struct VS_OUTPUT {
	float2 TexCoord:TEXCOORD0;//�e�N�X�`�����W
	float3 WTangent:TEXCOORD1;//�ڐ�
	float3 WBinormal : TEXCOORD2;//�]�@��
	float3 WNormal:TEXCOORD3;//���[���h�@��
	float4 WPosition:TEXCOORD4;//���[���h���W
	float4 Position:SV_POSITION;//���K���f�o�C�X���_���W

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

	//g_LocalWorldMatrix�̓��[�g�̃��[���h�ϊ��s��
	VSOutput.WPosition.x = dot(VSInput.Position, lLocalWorldMatrix[0]);
	VSOutput.WPosition.y = dot(VSInput.Position, lLocalWorldMatrix[1]);
	VSOutput.WPosition.z = dot(VSInput.Position, lLocalWorldMatrix[2]);
	VSOutput.WPosition.w = 1.0;

	//���_���W�n�ɕϊ�
	float4 lViewPosition;
	lViewPosition.x = dot(VSOutput.WPosition, g_Base.ViewMatrix[0]);
	lViewPosition.y = dot(VSOutput.WPosition, g_Base.ViewMatrix[1]);
	lViewPosition.z = dot(VSOutput.WPosition, g_Base.ViewMatrix[2]);
	lViewPosition.w = 1.0;

	//���K���f�o�C�X���W�n�ɕϊ�
	VSOutput.Position.x = dot(lViewPosition, g_Base.ProjectionMatrix[0]);
	VSOutput.Position.y = dot(lViewPosition, g_Base.ProjectionMatrix[1]);
	VSOutput.Position.z = dot(lViewPosition, g_Base.ProjectionMatrix[2]);
	VSOutput.Position.w = dot(lViewPosition, g_Base.ProjectionMatrix[3]);

	//�@���x�N�g���̍��W�ϊ�(���[���h���W�n�ɕϊ�)
	VSOutput.WNormal.x = dot(VSInput.Normal, lLocalWorldMatrix[0].xyz);
	VSOutput.WNormal.y = dot(VSInput.Normal, lLocalWorldMatrix[1].xyz);
	VSOutput.WNormal.z = dot(VSInput.Normal, lLocalWorldMatrix[2].xyz);

	//�ڃx�N�g���̍��W�ϊ�(���[���h���W�n�ɕϊ�)
	VSOutput.WTangent.x = dot(VSInput.Tangent, lLocalWorldMatrix[0].xyz);
	VSOutput.WTangent.y = dot(VSInput.Tangent, lLocalWorldMatrix[1].xyz);
	VSOutput.WTangent.z = dot(VSInput.Tangent, lLocalWorldMatrix[2].xyz);

	//�]�@���x�N�g���̍��W�ϊ�(���[���h���W�n�ɕϊ�)
	VSOutput.WBinormal.x = dot(VSInput.Binormal, lLocalWorldMatrix[0].xyz);
	VSOutput.WBinormal.y = dot(VSInput.Binormal, lLocalWorldMatrix[1].xyz);
	VSOutput.WBinormal.z = dot(VSInput.Binormal, lLocalWorldMatrix[2].xyz);

	VSOutput.TexCoord.xy = VSInput.TexCoords0.xy;//�e�N�X�`�����W�̃Z�b�g

	return VSOutput;
}