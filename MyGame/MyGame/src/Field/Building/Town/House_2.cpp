#include "House_2.h"
#include "../../../Graphic/Model.h"
#include "../../../Graphic/Sprite.h"

House_2::House_2(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "House_2", position, 6, 4, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_HOUSE_2));
}

House_2::House_2(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "House_2", position, 6, 4, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_HOUSE_2));
}

House_2::House_2(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "House_2", width, height, 6, 4, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_HOUSE_2));
}

void House_2::update(float deltaTime) {

}

void House_2::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void House_2::end() {
}

void House_2::setTexture(int type)
{
	auto i = MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0);
	switch (type)
	{
	case 1: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_HOUSE2_WHITE), FALSE);
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialNormalMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_NORMAL_HOUSE2_WHITE), FALSE);
		break;
	}
	case 2: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_HOUSE2_BLACK), FALSE);
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialNormalMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_NORMAL_HOUSE2_BLACK), FALSE);
		break;
	}
	case 3: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_HOUSE2_RED), FALSE);
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialNormalMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_NORMAL_HOUSE2_RED), FALSE);
		break;
	}
	default:
		break;
	}
}

std::shared_ptr<BuildingBase> House_2::clone() {
	return std::make_shared<House_2>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> House_2::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<House_2>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> House_2::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<House_2>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> House_2::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<House_2>(world, width, height, rotationNum, offset);
}
