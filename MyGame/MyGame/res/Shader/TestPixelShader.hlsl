#include"DxLibPixelShader.hlsli"

// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float2 TexCoord:TEXCOORD0;//�e�N�X�`�����W
	float3 WTangent:TEXCOORD1;//�ڐ�
	float3 WBinormal : TEXCOORD2;//�]�@��
	float3 WNormal:TEXCOORD3;//���[���h�@��
	float4 WPosition:TEXCOORD4;//���[���h���W
	float4 Position:SV_POSITION;//���K���f�o�C�X���_���W
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 Color0          : SV_TARGET0;
};


//�f�B�t���[�Y�}�b�v
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);

															// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float4 albedo_color = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoord.xy);

	// �o�̓J���[ = �e�N�X�`���J���[
	PSOutput.Color0 = float4(albedo_color);

	// �o�̓p�����[�^��Ԃ�
	return PSOutput;
}