#include "FieldBase.h"
#include<DxLib.h>
#include"../Math/Vector3.h"
#include"../Define.h"
#include"../Graphic/Shader/ShaderManager.h"

// コンストラクタ
FieldBase::FieldBase(int field, int skybox) :
	field_(field), skyBox_(skybox), mesh_(field_), out_(skybox){
	//モデルが設定されていなかったら返す
	if (field_ < 0 || skyBox_<0)return;

	// フィールドの座標指定
	MV1SetPosition(field_,Vector3::Zero);
	// フィールドの拡大率指定
	MV1SetScale(field_, Vector3::Vector3ToVECTOR(Vector3::One * FIELD_SCALE));

	// スカイボックスの座標指定
	MV1SetPosition(skyBox_, Vector3::Zero);
	// スカイボックスの拡大率指定
	MV1SetScale(skyBox_, Vector3::One*2.f*FIELD_SCALE);
}

// 更新
void FieldBase::update(float deltaTime) {
	if (field_ < 0 || skyBox_<0)return;
}

// 描画
void FieldBase::draw() const {
	if (field_ < 0 || skyBox_<0)return;

	// スカイボックスの描画
	MV1DrawModel(skyBox_);
	// フィールドの描画
	MV1DrawModel(field_);
}

// フィールドのハンドル取得
int FieldBase::modelHandle() {
	return field_;
}

CollisionMesh& FieldBase::getMesh()
{
	return mesh_;
}

CollisionMesh & FieldBase::getOutMesh()
{
	return out_.mesh_;
}
