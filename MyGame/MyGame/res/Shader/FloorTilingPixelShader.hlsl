// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
	float4 Diffuse         : COLOR0;		// �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1;		// �X�y�L�����J���[
	float2 TexCoords0      : TEXCOORD0;	// �e�N�X�`�����W
	float4 WPos      : TEXCOORD1;
	float4 Position        : SV_POSITION;	// ���W( �v���W�F�N�V������� )
};

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
	float4 Color0           : SV_TARGET0;	// �F
};


// �萔�o�b�t�@�s�N�Z���V�F�[�_�[��{�p�����[�^
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	float4		FactorColor;			// �A���t�@�l��

	float		MulAlphaColor;			// �J���[�ɃA���t�@�l����Z���邩�ǂ���( 0.0f:��Z���Ȃ�  1.0f:��Z���� )
	float		AlphaTestRef;			// �A���t�@�e�X�g�Ŏg�p�����r�l
	float2		Padding1;

	int			AlphaTestCmpMode;		// �A���t�@�e�X�g��r���[�h( DX_CMP_NEVER �Ȃ� )
	int3		Padding2;

	float4		IgnoreTextureColor;	// �e�N�X�`���J���[���������p�J���[
};

// ��{�p�����[�^
cbuffer cbD3D11_CONST_BUFFER_PS_BASE				: register(b1)
{
	DX_D3D11_PS_CONST_BUFFER_BASE		g_Base;
};

cbuffer Floor_CB : register(b3)
{
	float gridSize;//1�}�X���Ƃ̃T�C�Y
	float maxXSize;//�����f���̍ő�T�C�Y
	float maxYSize;//�����f���̍ő�T�C�Y
	int columnSize;//�O���b�h�̗񕪊���
	int4 celltype[1672];//�Z�����̃e�N�X�`���^�C�v(�z��T�C�Y�͏��T�C�Y�ɂ���ĕύX���鎖)
}

SamplerState g_DiffuseMapSampler            : register(s0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��
Texture2D    g_DiffuseMapTexture            : register(t0);		// �f�B�t���[�Y�}�b�v�e�N�X�`��


																// main�֐�
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float4 TextureDiffuseColor;

	// �e�N�X�`���J���[�̓ǂݍ���
	float2 position;
	position.x = (PSInput.TexCoords0.x* maxXSize);
	position.y = (PSInput.TexCoords0.y* maxYSize);

	int indexNum = (int)(position.x / (gridSize)) + ((int)(position.y / (gridSize)) * columnSize);
	//int indexNum = (int)((position.x / (gridSize)) + ((position.y / (gridSize)) * 88.0));
	indexNum = clamp(indexNum, 0, 6687);//�z��T�C�Y-1��ݒ肷��
	float cellsplit[4];
	int cellpos = (indexNum / 4);
	cellsplit[0] = celltype[cellpos].x;
	cellsplit[1] = celltype[cellpos].y;
	cellsplit[2] = celltype[cellpos].z;
	cellsplit[3] = celltype[cellpos].w;
	int cellslide = indexNum % 4;
	float cell = cellsplit[cellslide];

	position.x = fmod(position.x, gridSize)/gridSize;//0�`1
	position.y = fmod(position.y, gridSize)/gridSize;//0�`1

	position *= (1024.0 / 4096.0);//�e�N�X�`���̃u���b�N���̃T�C�Y/�e�N�X�`���̑S�̃T�C�Y


	int xslide = cell % 2;
	int yslide = ceil(cell / 2) - 1;
	position.x += xslide * (1024.0 / 4096.0);
	position.y += yslide * (1024.0 / 4096.0);
	TextureDiffuseColor = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, position);


	PSOutput.Color0.rgb = TextureDiffuseColor.rgb;
	//PSOutput.Color0.rgb = float3(1.0,1.0,1.0);

	//PSOutput.Color0.a = 1.0;

	// �o�̓A���t�@ = �e�N�X�`���A���t�@ * �s�����x
	PSOutput.Color0.a = TextureDiffuseColor.a * g_Base.FactorColor.a ;

	// �o�̓p�����[�^��Ԃ�
	return PSOutput;
}

