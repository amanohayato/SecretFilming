#ifndef DX_LIB_SHADER_COMMON_HLSLI_
#define DX_LIB_SHADER_COMMON_HLSLI_

#define DX_D3D11_COMMON_CONST_LIGHT_NUM         (6)     // ���ʃp�����[�^�̃��C�g�̍ő吔

// �\���̒�` --------------------------------------------------------------------

// �}�e���A���p�����[�^
struct DX_D3D11_CONST_MATERIAL
{
    float4      Diffuse;                // �f�B�t���[�Y�J���[
    float4      Specular;               // �X�y�L�����J���[
    float4      Ambient_Emissive;       // �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
    float       Power;                  // �X�y�L�����̋���
    float3      Padding;                // �p�f�B���O
};

// �t�H�O�p�����[�^
struct DX_D3D11_VS_CONST_FOG
{
    float       LinearAdd;              // �t�H�O�p�p�����[�^ end / ( end - start )
    float       LinearDiv;              // �t�H�O�p�p�����[�^ -1  / ( end - start )
    float       Density;                // �t�H�O�p�p�����[�^ density
    float       E;                      // �t�H�O�p�p�����[�^ ���R�ΐ��̒�
    float4      Color;                  // �J���[
};

// ���C�g�p�����[�^
struct DX_D3D11_CONST_LIGHT
{
    int         Type;                   // ���C�g�^�C�v( DX_LIGHTTYPE_POINT �Ȃ� )
    int3        Padding1;               // �p�f�B���O�P

    float3      Position;               // ���W( �r���[��� )
    float       RangePow2;              // �L�������̂Q��

    float3      Direction;              // ����( �r���[��� )
    float       FallOff;                // �X�|�b�g���C�g�pFallOff

    float3      Diffuse;                // �f�B�t���[�Y�J���[
    float       SpotParam0;             // �X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )

    float3      Specular;               // �X�y�L�����J���[
    float       SpotParam1;             // �X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )

    float4      Ambient;                // �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������

    float       Attenuation0;           // �����ɂ�錸�������p�p�����[�^�O
    float       Attenuation1;           // �����ɂ�錸�������p�p�����[�^�P
    float       Attenuation2;           // �����ɂ�錸�������p�p�����[�^�Q
    float       Padding2;               // �p�f�B���O�Q
};

// �s�N�Z���V�F�[�_�[�E���_�V�F�[�_�[���ʃp�����[�^
struct DX_D3D11_CONST_BUFFER_COMMON
{
    DX_D3D11_CONST_LIGHT        Light[DX_D3D11_COMMON_CONST_LIGHT_NUM];         // ���C�g�p�����[�^
    DX_D3D11_CONST_MATERIAL     Material;                                       // �}�e���A���p�����[�^
    DX_D3D11_VS_CONST_FOG       Fog;                                            // �t�H�O�p�����[�^
};

// ���_�V�F�[�_�[�E�s�N�Z���V�F�[�_�[���ʃp�����[�^
cbuffer cbD3D11_CONST_BUFFER_COMMON : register(b0)
{
    DX_D3D11_CONST_BUFFER_COMMON    g_Common;
};

#endif
