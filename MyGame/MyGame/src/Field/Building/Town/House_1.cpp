#include "House_1.h"
#include "../../../Graphic/Model.h"
#include "../../../Graphic/Sprite.h"

House_1::House_1(IWorld* world, const Vector3& position, int rotationNum) :
	BuildingBase(world, "House_1", position, 5, 5, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_HOUSE_1));
}

House_1::House_1(IWorld* world, const Vector2& position, int rotationNum) :
	BuildingBase(world, "House_1", position, 5, 5, rotationNum) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_HOUSE_1));
}

House_1::House_1(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) :
	BuildingBase(world, "House_1", width, height, 5, 5, rotationNum, offset) {
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_HOUSE_1));
}

void House_1::update(float deltaTime) {

}

void House_1::draw() const {
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	animation_.Draw(pose);
}

void House_1::end() {
}

void House_1::setTexture(int type)
{
	auto i = MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0);
	switch (type)
	{
	case 1: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_HOUSE1_BLACK), FALSE);
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialNormalMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_NORMAL_HOUSE1_BLACK), FALSE);
		break; 
	}
	case 2: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_HOUSE1_WHITE), FALSE);
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialNormalMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_NORMAL_HOUSE1_WHITE), FALSE);
		break;
	}
	case 3: {
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialDifMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_HOUSE1_BROWN), FALSE);
		MV1SetTextureGraphHandle(animation_.getModelHandle(), MV1GetMaterialNormalMapTexture(animation_.getModelHandle(), 0), Sprite::GetInstance().GetHandle(SPRITE_ID::TEXTURE_NORMAL_HOUSE1_BROWN), FALSE);
		break;
	}
	default:
		break;
	}
}

std::shared_ptr<BuildingBase> House_1::clone() {
	return std::make_shared<House_1>(world_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> House_1::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<House_1>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> House_1::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<House_1>(world, position, rotationNum);
}

std::shared_ptr<BuildingBase> House_1::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<House_1>(world, width, height, rotationNum, offset);
}
