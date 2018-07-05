#ifndef DX_LIB_VERTEX_SHADER_HLSLI_
#define DX_LIB_VERTEX_SHADER_HLSLI_

#include "DxLibShaderCommon.hlsli"

// �}�N����` -----------------------------------

#define DX_VERTEXLIGHTING_LIGHT_NUM                     3           // ���_�P�ʃ��C�e�B���O�œ����Ɏg�p�ł��郉�C�g�̍ő吔
#define DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM            3           // �e�N�X�`�����W�ϊ��s��̓]�u�s��̐�
#define DX_D3D11_VS_CONST_WORLD_MAT_NUM                 54          // �g���C�A���O�����X�g��œ����Ɏg�p���郍�[�J�������[���h�s��̍ő吔

// �f�[�^�^��` ---------------------------------

// ��{�p�����[�^
struct DX_D3D11_VS_CONST_BUFFER_BASE
{
    float4      AntiViewportMatrix[4];              // �A���`�r���[�|�[�g�s��
    float4      ProjectionMatrix[4];                // �r���[�@���@�v���W�F�N�V�����s��
    float4      ViewMatrix[3];                      // ���[���h�@���@�r���[�s��
    float4      LocalWorldMatrix[3];                // ���[�J���@���@���[���h�s��

    float4      ToonOutLineSize;                    // �g�D�[���̗֊s���̑傫��
    float       DiffuseSource;                      // �f�B�t���[�Y�J���[( 0.0f:�}�e���A��  1.0f:���_ )
    float       SpecularSource;                     // �X�y�L�����J���[(   0.0f:�}�e���A��  1.0f:���_ )
    float       MulSpecularColor;                   // �X�y�L�����J���[�l�ɏ�Z����l( �X�y�L�������������Ŏg�p )
    float       Padding;
};

// ���̑��̍s��
struct DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX
{
    float4      ShadowMapLightViewProjectionMatrix[3][4];                   // �V���h�E�}�b�v�p�̃��C�g�r���[�s��ƃ��C�g�ˉe�s�����Z��������
    float4      TextureMatrix[DX_D3D11_VS_CONST_TEXTURE_MATRIX_NUM][2]; // �e�N�X�`�����W����p�s��
};

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
struct DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX
{
    float4      Matrix[DX_D3D11_VS_CONST_WORLD_MAT_NUM * 3];                    // ���[�J���@���@���[���h�s��
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_VS_BASE : register(b1)
{
    DX_D3D11_VS_CONST_BUFFER_BASE               g_Base;
};

// ���̑��̍s��
cbuffer cbD3D11_CONST_BUFFER_VS_OTHERMATRIX : register(b2)
{
    DX_D3D11_VS_CONST_BUFFER_OTHERMATRIX        g_OtherMatrix;
};

// �X�L�j���O���b�V���p�́@���[�J���@���@���[���h�s��
cbuffer cbD3D11_CONST_BUFFER_VS_LOCALWORLDMATRIX : register(b3)
{
    DX_D3D11_VS_CONST_BUFFER_LOCALWORLDMATRIX   g_LocalWorldMatrix;
};

#endif

