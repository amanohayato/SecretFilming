#include "Field.h"
#include <DxLib.h>
#include "../../Math/Vector3.h"
#include "../../Define.h"
#include "../../Graphic/Shader/ShaderManager.h"
#include "../../Graphic/Model.h"
#include "../../Graphic/Shader/CBuff/Floor_CB.h"
#include"../../Graphic/Sprite.h"


Field::Field(int field):
	field_(field), mesh_(field_)
{
	//モデルが設定されていなかったら返す
	if (field_ < 0) return;
	
	// フィールドの座標指定
	MV1SetPosition(field_, Vector3::Zero);
	// フィールドの拡大率指定
	MV1SetScale(field_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));
	ftm_.initialize();

	
}

void Field::update(float deltaTime)
{
	if (field_ < 0) return;

}

void Field::draw() const
{
	if (field_ < 0) return;
	// フィールドの描画
	auto cbuffid = ShaderManager::getInstance().getCBuff(ShaderID::TILING_SHADER);
	Floor_CB* fcb = (Floor_CB*)GetBufferShaderConstantBuffer(cbuffid);


	fcb->gridSize = 16.5f;
	fcb->maxXSize = 1452.0f;
	fcb->maxYSize = 1254.0f;
	fcb->columnSize = 88;

	for (int i = 0; i < CELLTYPE_SIZE; i++) {
		fcb->celltype[i].x = ftm_.get(i * 4);
		fcb->celltype[i].y = ftm_.get(i * 4 + 1);
		fcb->celltype[i].z = ftm_.get(i * 4 + 2);
		fcb->celltype[i].w = ftm_.get(i * 4 + 3);
	}

	//ShaderManager::getInstance().UpdateCBuff<Floor_CB>(ShaderID::TILING_SHADER, cb, 3);

	UpdateShaderConstantBuffer(cbuffid);
	SetShaderConstantBuffer(cbuffid, DX_SHADERTYPE_PIXEL, 3);

	ShaderManager::getInstance().begin(ShaderID::TILING_SHADER);
	SetUseTextureToShader(0,Sprite::GetInstance().GetHandle(SPRITE_ID::SPRITE_TEXTURE));
	MV1DrawModel(field_);
	ShaderManager::getInstance().end();

}

void Field::shadowDraw() const
{
	Model::GetInstance().Draw(MODEL_ID::MODEL_SHADOW_TILE, Matrix::CreateTranslation(Vector3::Up*0.01f));
}

int Field::modelHandle()
{
	return field_;
}

CollisionMesh& Field::getMesh()
{
	return mesh_;
}

int Field::getFloorTile(int x, int y) const
{
	return ftm_.get(x, y);
}

int Field::getWidth() const
{
	return ftm_.getWidth();
}

int Field::getHeight() const
{
	return ftm_.getHeight();
}
