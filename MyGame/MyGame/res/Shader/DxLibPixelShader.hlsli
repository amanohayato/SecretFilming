#ifndef DX_LIB_PIXEL_SHADER_H_
#define DX_LIB_PIXEL_SHADER_H_

#include "DxLibShaderCommon.hlsli"

#define DX_PIXELLIGHTING_LIGHT_NUM          (6)     // �s�N�Z���P�ʃ��C�e�B���O�œ����Ɏg�p�ł��郉�C�g�̍ő吔
#define DX_D3D11_PS_CONST_FILTER_SIZE       (256)   // �t�B���^�[�p�萔�o�b�t�@�̃T�C�Y

// �f�[�^�^��` ---------------------------------

// �V���h�E�}�b�v�p�����[�^
struct DX_D3D11_PS_CONST_SHADOWMAP
{
    float       AdjustDepth;            // 臒l�[�x�␳�l
    float       GradationParam;         // �O���f�[�V�����͈�
    float       Enable_Light0;          // ���C�g�O�ւ̓K�p���
    float       Enable_Light1;          // ���C�g�P�ւ̓K�p���

    float       Enable_Light2;          // ���C�g�Q�ւ̓K�p���
    float3      Padding;                // �p�f�B���O
};

// �萔�o�b�t�@�s�N�Z���V�F�[�_�[��{�p�����[�^
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
    float4      FactorColor;            // �A���t�@�l��

    float       MulAlphaColor;          // �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0f:��Z���Ȃ�  1.0f:��Z���� )
    float       AlphaTestRef;           // �A���t�@�e�X�g�Ŏg�p�����r�l
    float2      Padding1;

    int         AlphaTestCmpMode;       // �A���t�@�e�X�g��r���[�h( DX_CMP_NEVER �Ȃ� )
    int3        Padding2;
};

// �萔�o�b�t�@�V���h�E�}�b�v�p�����[�^
struct DX_D3D11_PS_CONST_BUFFER_SHADOWMAP
{
    DX_D3D11_PS_CONST_SHADOWMAP Data[3];
};

// �萔��` ----------------------------------------------------------------------

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_BASE : register(b1)
{
    DX_D3D11_PS_CONST_BUFFER_BASE       g_Base;
};

// �V���h�E�}�b�v�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_SHADOWMAP : register(b2)
{
    DX_D3D11_PS_CONST_BUFFER_SHADOWMAP  g_ShadowMap;
};

#endif
