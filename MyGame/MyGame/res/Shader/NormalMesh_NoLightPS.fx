// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 Diffuse         : COLOR0 ;		// �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1 ;		// �X�y�L�����J���[
	float2 TexCoords0      : TEXCOORD0;	// �e�N�X�`�����W
	float4 WPos      : TEXCOORD1 ;
	float4 Position        : SV_POSITION;	// ���W( �v���W�F�N�V������� )
} ;

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 Color0           : SV_TARGET0 ;	// �F
} ;


// �萔�o�b�t�@�s�N�Z���V�F�[�_�[��{�p�����[�^
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	float4		FactorColor ;			// �A���t�@�l��

	float		MulAlphaColor ;			// �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0f:��Z���Ȃ�  1.0f:��Z���� )
	float		AlphaTestRef ;			// �A���t�@�e�X�g�Ŏg�p�����r�l
	float2		Padding1 ;

	int			AlphaTestCmpMode ;		// �A���t�@�e�X�g��r���[�h( DX_CMP_NEVER �Ȃ� )
	int3		Padding2 ;

	float4		IgnoreTextureColor ;	// �e�N�X�`���J���[���������p�J���[
} ;

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_BASE				: register( b1 )
{
	DX_D3D11_PS_CONST_BUFFER_BASE		g_Base ;
} ;

cbuffer Floor_CB : register(b3)
{
	int4 celltype[64];//�Z�����̃e�N�X�`���^�C�v(�z��T�C�Y�͏��T�C�Y�ɂ���ĕύX���鎖)

	int gridSize;//1�}�X���Ƃ̃T�C�Y
	int maxSize;//�����f���̍ő�T�C�Y
	int columnSize;//�O���b�h�̗񕪊���
	float padding;
}

SamplerState g_DiffuseMapSampler            : register( s0 ) ;		// �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D    g_DiffuseMapTexture            : register( t0 ) ;		// �f�B�t���[�Y�}�b�v�e�N�X�`��


// main�֐�
PS_OUTPUT main( PS_INPUT PSInput )
{
	PS_OUTPUT PSOutput ;
	float4 TextureDiffuseColor ;

	// �e�N�X�`���J���[�̓ǂݍ���
	float2 position;
	position = (PSInput.TexCoords0* maxSize);

	int indexNum = (int)(position.x / gridSize)+ ((int)(position.y / gridSize)*8);
	indexNum = clamp(indexNum, 0, 63);//�z��T�C�Y-1��ݒ肷��
	int cell = celltype[indexNum].x;

	position.x = (fmod(position.x , gridSize)+(gridSize*cell))*0.006;
	position.y = fmod(position.y , gridSize)*0.006;
	position *= (165.0 / 1024.0);//�e�N�X�`���̃u���b�N���̃T�C�Y/�e�N�X�`���̑S�̃T�C�Y

	TextureDiffuseColor =  g_DiffuseMapTexture.Sample( g_DiffuseMapSampler, position) ;

	PSOutput.Color0.rgb = TextureDiffuseColor.rgb;
	PSOutput.Color0.a = 1.0;
	
	// �o�̓A���t�@ = �e�N�X�`���A���t�@ * �s�����x
	//PSOutput.Color0.a = TextureDiffuseColor.a * g_Base.FactorColor.a ;

	// �o�̓p�����[�^��Ԃ�
	return PSOutput;
}

