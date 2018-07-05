#include"DxLibPixelShader.hlsli"

struct PS_INPUT {
	float2 TexCoord:TEXCOORD0;//�e�N�X�`�����W
	float3 WTangent:TEXCOORD1;//�ڐ�
	float3 WBinormal:TEXCOORD2;//�]�@��
	float3 WNormal:TEXCOORD3;//�@��
	float4 WPosition:TEXCOORD4;//���C�g�����x�N�g��
	float4 Position:SV_POSITION;//�v���W�F�N�V�������W

};

struct PS_OUTPUT {
	float4 Color0:SV_TARGET0;//�F
};

//�f�B�t���[�Y�͊ȈՔł̂܂�
//�X�y�L�����𕨗��x�[�X�ł̌v�Z
//���t�l�X(�\�ʂ����0.0f�`�U���U��1.0f�ɁA���������߂�)

//�f�B�t���[�Y�}�b�v
SamplerState g_DiffuseMapSampler:register(s0);
Texture2D g_DiffuseMapTexture:register(t0);

//�@���}�b�v
SamplerState g_NormalMapSampler:register(s1);
Texture2D g_NormalMapTexture:register(t1);

//�X�y�L�����}�b�v
SamplerState g_SpecularMapSampler:register(s2);
Texture2D g_SpecularMapTexture:register(t2);

//�A���r�G���g�I�N���[�W�����}�b�v
SamplerState g_AoMapSampler:register(s3);
Texture2D g_AoMapTexture:register(t3);

//IBL�X�y�L�������}�b�v(���}�b�v�������ɂ���,�L���[�u�}�b�v)
SamplerState g_IBLSpecularMapSampler:register(s11);
TextureCube g_IBLSpecularMapTexture:register(t11);

//IBL�f�B�t���[�Y���}�b�v(���}�b�v�������ɂ���,�L���[�u�}�b�v)
SamplerState g_IBLDiffuseMapSampler:register(s12);
TextureCube g_IBLDiffuseMapTexture:register(t12);

//IBLBRDF�}�b�v(�ʏ��2D�e�N�X�`��)
SamplerState g_IBLBRDFMapSampler:register(s13);
Texture2D g_IBLBRDFMapTexture:register(t13);

cbuffer PixrrlShaderCB:register(b4) {
	float4 g_WorldViewPosition;//���_�ʒu
	float4 g_WorldLightPosition;//���C�g�ʒu
	float4 g_LightColor;//���C�g�J���[
}

static const float PI = 3.1415926;
static const float u_mipmap_scale = 9;
static const float u_rim_scale = 1.0;

//�g�U���ˌ��̐��K��
float phong_diffuse() {
	return (1.0 / PI);
}

//�t���l�����ˌ��̌v�Z
float3 fresnel_factor(float3 f0, float product) {
	return f0 + (1.0 - f0)*pow(1.01 - product, 5.0);
}

//�}�C�N���t�@�Z�b�g���z�̌v�Z Trowbridge-Reitz(GGX) �\�ʏ�ɂ��鏝(�U���U��=���������A�c���c��=�������Ȃ�)�̕\��(�}�C�N���t�@�Z�b�g=������)(�\�ʂ̑e���̕\��)
float D_GGX(float roughness, float NdH) {
	float m = roughness*roughness;
	float m2 = m*m;
	float d = (NdH* m2 - NdH)*NdH + 1.0;
	return m2 / (PI*d*d);
}

//�􉽌������̌v�Z(�\�ʂ̑e����\������A���v�Z����Shininess�ōs���K�v��������)
float G_schlick(float roughness, float NdV, float NdL) {
	float k = roughness*roughness*0.5;
	float V = NdV*(1.0 - k) + k;
	float L = NdL*(1.0 - k) + k;
	return min(2.0, 0.36 / (V*L));
}

//�N�b�N�g�����X�̋��ʔ��˃��f���̌v�Z(�t�H�����f���Ƃ͈�����v�Z�A�����̃c�������̌v�Z���A�����̕����c���������A��)
float3 cooktorrance_specular(float NdL, float NdV, float NdH, float3 F, float roughness) {
	float D = D_GGX(roughness, NdH);
	float G = G_schlick(roughness, NdV, NdL);
	float rim = lerp(1.0 - roughness*u_rim_scale*0.9, 1.0, NdV);
	return min((F*G*D) / rim, 1.0);
}

//�m�����j�A��Ԃ��烊�j�A��Ԃɕϊ�(�e�N�X�`��RGB�l�̒���)
float3 convert_to_linear(float3 color) {
	return pow(color, 2.2);
}

//���j�A��Ԃ���m�����j�A��Ԃɕϊ�
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
	float3 R = reflect(-V, N);//���}�b�v�p

	float NdL = max(0.0001, dot(N, L));//0.0001��0���Z����̂��߁Adot�̓x�N�g���̌����̍��𒲂ׂĂ���
	float NdV = max(0.0001, dot(N, V));//0.0001��0���Z����̂��߁Adot�̓x�N�g���̌����̍��𒲂ׂĂ���
	float NdH = max(0.0001, dot(N, H));//0.0001��0���Z����̂��߁Adot�̓x�N�g���̌����̍��𒲂ׂĂ���
	float HdV = max(0.0001, dot(H, V));//0.0001��0���Z����̂��߁Adot�̓x�N�g���̌����̍��𒲂ׂĂ���
	float LdV = max(0.0001, dot(L, V));//0.0001��0���Z����̂��߁Adot�̓x�N�g���̌����̍��𒲂ׂĂ���

	//�A���x�h�J���[(���������)
	float4 albedo_color = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, PSInput.TexCoord.xy);
	albedo_color.rgb = convert_to_linear(albedo_color.rgb);
	//�X�y�L�����J���[(��������)
	float4 specular_color = g_SpecularMapTexture.Sample(g_SpecularMapSampler, PSInput.TexCoord.xy);
	specular_color.rgb = convert_to_linear(albedo_color.rgb);
	//���t�l�X(0:�c���c���`1:�U���U��)�@Unity��Smoothness(���t�l�X�̋t��) �����������t�l�X�ɕς���ASpecularMap�̃A���t�@�����ɃX���[�X�l�X�f�[�^�����Ƃ�
	float roughness = 1.0 - specular_color.a;
	//�A���r�G���g�I�N���[�W����(�g�D�[�������_�����O�p�̘g�ɖ������e�N�X�`�������Ƃ�)
	float ao = g_AoMapTexture.Sample(g_AoMapSampler, PSInput.TexCoord.xy).r;

	//�����x�[�X�V�F�[�_�[�p�̃��C�g�J���[���v�Z(�f�B�t���[�Y�̃΂̌v�Z�Ƃ̂��܍��킹�̂���=PI���O����1/3�̖��邳�ɂȂ��Ă��܂�����,���̕��Ńf�B�t���[�Y�A�X�y�L�����Ƀ΂̌v�Z�����Đ��K�����Ă邩��)
	float3 light_color = g_LightColor.rgb*PI;

	//���ʔ��ˌ������߂�
	float3 specular_fresnel = fresnel_factor(specular_color.rgb, HdV);
	float3 specular_reflectance = cooktorrance_specular(NdL, NdV, NdH, specular_fresnel, roughness)*NdL;

	//��BRDF�̌v�Z(�L���[�u�}�b�v����Ƃ��Ă������t���N�V�����̏��)
	float2 brdf = g_IBLBRDFMapTexture.Sample(g_IBLBRDFMapSampler, float2(NdV, 1.0 - roughness)).xy;
	float3 ibl_specular = min(0.99, specular_color.rgb*brdf.x + brdf.y);
	//�����ʔ��˂̌v�Z
	float3 env_specular = g_IBLSpecularMapTexture.SampleLevel(g_IBLSpecularMapSampler, R, roughness*u_mipmap_scale).xyz;
	//�ŏI�I�ȋ��ʔ��ˌ��̌v�Z(���t�l�X���l�����āA�U���U������)
	float3 specular_light = (specular_reflectance*light_color) + (env_specular*ibl_specular);
	//�g�U���ˌ������߂�(�����߂�ꂢ��[���ł�)
	float3 diffuse_color = albedo_color.xyz;
	float3 diffuse_reflectance = diffuse_color*NdL*phong_diffuse();
	//���g�U���˂̌v�Z
	float3 env_diffuse = g_IBLDiffuseMapTexture.Sample(g_IBLDiffuseMapSampler, N).xyz*phong_diffuse();
	//�ŏI�I�Ȋg�U���ˌ��̌v�Z
	float3 diffuse_light = (diffuse_reflectance*light_color) + (env_diffuse*diffuse_color);

	//�ŏI�I�Ȍ��̌v�Z
	float3 final_light = (diffuse_light + specular_light)*ao;
	PSOutput.Color0.rgb = convert_to_none_linear(final_light);
	PSOutput.Color0.a = albedo_color.a;

	return PSOutput;
}