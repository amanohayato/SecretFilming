// ピクセルシェーダーの入力
struct PS_INPUT
{
	float4 Diffuse         : COLOR0 ;		// ディフューズカラー
	float4 Specular        : COLOR1 ;		// スペキュラカラー
	float2 TexCoords0      : TEXCOORD0;	// テクスチャ座標
	float4 WPos      : TEXCOORD1 ;
	float4 Position        : SV_POSITION;	// 座標( プロジェクション空間 )
} ;

// ピクセルシェーダーの出力
struct PS_OUTPUT
{
	float4 Color0           : SV_TARGET0 ;	// 色
} ;


// 定数バッファピクセルシェーダー基本パラメータ
struct DX_D3D11_PS_CONST_BUFFER_BASE
{
	float4		FactorColor ;			// アルファ値等

	float		MulAlphaColor ;			// カラーにアルファ値を乗算するかどうか( 0.0f:乗算しない  1.0f:乗算する )
	float		AlphaTestRef ;			// アルファテストで使用する比較値
	float2		Padding1 ;

	int			AlphaTestCmpMode ;		// アルファテスト比較モード( DX_CMP_NEVER など )
	int3		Padding2 ;

	float4		IgnoreTextureColor ;	// テクスチャカラー無視処理用カラー
} ;

// 基本パラメータ
cbuffer cbD3D11_CONST_BUFFER_PS_BASE				: register( b1 )
{
	DX_D3D11_PS_CONST_BUFFER_BASE		g_Base ;
} ;

cbuffer Floor_CB : register(b3)
{
	int4 celltype[64];//セル毎のテクスチャタイプ(配列サイズは床サイズによって変更する事)

	int gridSize;//1マスごとのサイズ
	int maxSize;//床モデルの最大サイズ
	int columnSize;//グリッドの列分割数
	float padding;
}

SamplerState g_DiffuseMapSampler            : register( s0 ) ;		// ディフューズマップテクスチャ
Texture2D    g_DiffuseMapTexture            : register( t0 ) ;		// ディフューズマップテクスチャ


// main関数
PS_OUTPUT main( PS_INPUT PSInput )
{
	PS_OUTPUT PSOutput ;
	float4 TextureDiffuseColor ;

	// テクスチャカラーの読み込み
	float2 position;
	position = (PSInput.TexCoords0* maxSize);

	int indexNum = (int)(position.x / gridSize)+ ((int)(position.y / gridSize)*8);
	indexNum = clamp(indexNum, 0, 63);//配列サイズ-1を設定する
	int cell = celltype[indexNum].x;

	position.x = (fmod(position.x , gridSize)+(gridSize*cell))*0.006;
	position.y = fmod(position.y , gridSize)*0.006;
	position *= (165.0 / 1024.0);//テクスチャのブロック毎のサイズ/テクスチャの全体サイズ

	TextureDiffuseColor =  g_DiffuseMapTexture.Sample( g_DiffuseMapSampler, position) ;

	PSOutput.Color0.rgb = TextureDiffuseColor.rgb;
	PSOutput.Color0.a = 1.0;
	
	// 出力アルファ = テクスチャアルファ * 不透明度
	//PSOutput.Color0.a = TextureDiffuseColor.a * g_Base.FactorColor.a ;

	// 出力パラメータを返す
	return PSOutput;
}

