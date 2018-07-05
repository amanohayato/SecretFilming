// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 Diffuse         : COLOR0;		// ディフューズカラー
	float4 Specular        : COLOR1;		// スペキュラカラー
	float2 TexCoords0      : TEXCOORD0;	// テクスチャ座標
	float4 WPos      : TEXCOORD1;
	float4 Position        : SV_POSITION;	// 座標( プロジェクション空間 )
};

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 Color0           : SV_TARGET0;	// 色
};


// 定数バッファピクセルシェーダー基本パラメータ
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	float4		FactorColor;			// アルファ値等

	float		MulAlphaColor;			// カラーにアルファ値を乗算するかどうか( 0.0f:乗算しない  1.0f:乗算する )
	float		AlphaTestRef;			// アルファテストで使用する比較値
	float2		Padding1;

	int			AlphaTestCmpMode;		// アルファテスト比較モード( DX_CMP_NEVER など )
	int3		Padding2;

	float4		IgnoreTextureColor;	// テクスチャカラー無視処理用カラー
};

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_PS_BASE				: register(b1)
{
	DX_D3D11_PS_CONST_BUFFER_BASE		g_Base;
};

cbuffer Floor_CB : register(b3)
{
	float gridSize;//1マスごとのサイズ
	float maxXSize;//床モデルの最大サイズ
	float maxYSize;//床モデルの最大サイズ
	int columnSize;//グリッドの列分割数
	int4 celltype[1672];//セル毎のテクスチャタイプ(配列サイズは床サイズによって変更する事)
}

SamplerState g_DiffuseMapSampler            : register(s0);		// ディフューズマップテクスチャ
Texture2D    g_DiffuseMapTexture            : register(t0);		// ディフューズマップテクスチャ


																// main関数
PS_OUTPUT main(PS_INPUT PSInput)
{
	PS_OUTPUT PSOutput;
	float4 TextureDiffuseColor;

	// テクスチャカラーの読み込み
	float2 position;
	position.x = (PSInput.TexCoords0.x* maxXSize);
	position.y = (PSInput.TexCoords0.y* maxYSize);

	int indexNum = (int)(position.x / (gridSize)) + ((int)(position.y / (gridSize)) * columnSize);
	//int indexNum = (int)((position.x / (gridSize)) + ((position.y / (gridSize)) * 88.0));
	indexNum = clamp(indexNum, 0, 6687);//配列サイズ-1を設定する
	float cellsplit[4];
	int cellpos = (indexNum / 4);
	cellsplit[0] = celltype[cellpos].x;
	cellsplit[1] = celltype[cellpos].y;
	cellsplit[2] = celltype[cellpos].z;
	cellsplit[3] = celltype[cellpos].w;
	int cellslide = indexNum % 4;
	float cell = cellsplit[cellslide];

	position.x = fmod(position.x, gridSize)/gridSize;//0～1
	position.y = fmod(position.y, gridSize)/gridSize;//0～1

	position *= (1024.0 / 4096.0);//テクスチャのブロック毎のサイズ/テクスチャの全体サイズ


	int xslide = cell % 2;
	int yslide = ceil(cell / 2) - 1;
	position.x += xslide * (1024.0 / 4096.0);
	position.y += yslide * (1024.0 / 4096.0);
	TextureDiffuseColor = g_DiffuseMapTexture.Sample(g_DiffuseMapSampler, position);


	PSOutput.Color0.rgb = TextureDiffuseColor.rgb;
	//PSOutput.Color0.rgb = float3(1.0,1.0,1.0);

	//PSOutput.Color0.a = 1.0;

	// 出力アルファ = テクスチャアルファ * 不透明度
	PSOutput.Color0.a = TextureDiffuseColor.a * g_Base.FactorColor.a ;

	// 出力パラメータを返す
	return PSOutput;
}

