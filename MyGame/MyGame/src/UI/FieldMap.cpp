#include "FieldMap.h"
#include"../World/IWorld.h"
#include"../Actor/Actor.h"
#include"../ID/EnumIDs.h"
#include"../Graphic/Sprite.h"
#include"../Field/Building/BuildingBase.h"
#include"../Scene/Manager/GameDataManager.h"
#include"../Actor/Enemy/EnemyBase.h"
#include"../Field/WalkGraph.h"
#include"../Define.h"


#include<DxLib.h>

static const Vector2 defaultPinPos{ 100.0f,-100.0f };
static constexpr float delayRate = 0.3f;
static constexpr float speedRate = 15.0f;
static constexpr float defaultCount = 0.2f*speedRate;//赤ピンとのディレイ
static const Vector2 ICON_POS = Vector2{ 200.0f,300.0f };

static const std::array<int,6> leftUpNumber_{
	4,2,
	0,1,
	3,5
};

inline float MathAngle(const Vector2& targetVect, const Vector2& baseVect = Vector2::Up, int rollVect = 1) {
	//Vector2 nTVect = Vector2::Normalize(targetVect);
	//Vector2 nBVect = Vector2::Normalize(baseVect);
	Vector2 nTVect = targetVect;
	Vector2 nBVect = baseVect;

	float angle = Vector2::Dot(nTVect, nBVect) / (nTVect.Length()*nBVect.Length());
	angle = MathHelper::ToDegrees(acos(angle));
	if (MathHelper::Sign(nTVect.x) > 0) {
		angle = 360 - angle;

	}
	return angle;
}
FieldMap::FieldMap(IWorld* world):
world_(world)
{
}

void FieldMap::initialize()
{
	for (auto& b : world_->getBuildings()) {
		buildings_.push_back(b);

	}

	colorSin_ = 0;
	evpCount_ = 0;
	drawIconList_.clear();
	drawIconList_.push_back(std::make_tuple(SPRITE_ID::SPRITE_DESC_PLAYER, SPRITE_ID::SPRITE_TEXT_PLAYER, Vector3{255,255,255}));
	drawIconList_.push_back(std::make_tuple(SPRITE_ID::SPRITE_DESC_ENEMY, SPRITE_ID::SPRITE_TEXT_ENEMY, Vector3{ 255,255,255 }));
	drawIconList_.push_back(std::make_tuple(SPRITE_ID::SPRITE_PIN, SPRITE_ID::SPRITE_TEXT_BLACKPIN, Vector3{ 0,0,0 }));
	drawIconList_.push_back(std::make_tuple(SPRITE_ID::SPRITE_PIN, SPRITE_ID::SPRITE_TEXT_REDPIN, Vector3{ 255,0,0 }));
	drawIconList_.push_back(std::make_tuple(SPRITE_ID::SPRITE_DESC_GOAL, SPRITE_ID::SPRITE_TEXT_GOAL, Vector3{ 255,255,255 }));
}

void FieldMap::update(float deltaTime)
{
	constexpr int speed = 3;
	constexpr int SIN_MAX = 360;
	colorSin_ = (colorSin_ + speed) % SIN_MAX;

	pin_add(deltaTime);

	auto enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	if (evpCount_ > enemy->GetEventPoints().size())targetpin_reset();
	evpCount_ = (int)enemy->GetEventPoints().size();
}

void FieldMap::draw(const Vector2 & position) const
{
	Vector2 origin;

	float size = 0.8f;//表示サイズ

	//足場を塗る
	for (int y = 0; y < world_->getFieldOnly()->getHeight(); y++) {
		for (int x = 0; x < world_->getFieldOnly()->getWidth(); x++) {
			int tileType = world_->getFieldOnly()->getFloorTile(x, y);

			Vector2 tilePos;
			tilePos.x = (float)x * SQUARES_WIDTH;
			tilePos.y = (float)y * SQUARES_HEIGHT;
			tilePos *= size; 
			tilePos += position;
			auto tcolor = (tileType==3)?GetColor(255, 245, 245) : GetColor(255, 255, 255);
			DrawBox((int)tilePos.x, (int)tilePos.y, (int)(tilePos.x + SQUARES_WIDTH * size), (int)(tilePos.y + SQUARES_HEIGHT * size), tcolor, TRUE);
		}
	}

	//ビルを建てる
	auto fieldsize = GameDataManager::getInstance().getMapSize();
	for (auto& b : buildings_) {
		if(!b.lock()->getActive())continue;
		auto bpos=b.lock()->getPosition();
		bpos.z = fieldsize.y - bpos.z;
		bpos *= size;
		bpos.x += position.x;
		bpos.z += position.y;
		Vector2 bsize;
		bsize.x=b.lock()->getHorizonal();
		bsize.y=b.lock()->getVertical();
		bsize *= 16.5f*size;
		int col = 220;
		int linecol = 180;
		DrawBox((int)(bpos.x - bsize.x * 0.5f), (int)(bpos.z - bsize.y * 0.5f),(int)( bpos.x + bsize.x * 0.5f),(int)( bpos.z + bsize.y * 0.5f), GetColor(col, col, col), TRUE);
		DrawBox((int)(bpos.x - bsize.x * 0.5f), (int)(bpos.z - bsize.y * 0.5f), (int)(bpos.x + bsize.x * 0.5f), (int)(bpos.z + bsize.y * 0.5f), GetColor(linecol, linecol, linecol), FALSE);

	}

	auto goalpos=world_->getWalkMap().getNode(0, goalNodeIndex).position;
	Vector2 gpos2D = Vector2{ goalpos.x,fieldsize.y - goalpos.z };
	gpos2D *= size;
	gpos2D += position;
	Vector2 or = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_MAP_GOAL);
	or *= 0.5f;
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MAP_GOAL, gpos2D, or , Vector2::One, FALSE);

	auto enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	
	int max = 64;
	int currentColor = MathHelper::Clamp((int)(abs(MathHelper::Sin((float)colorSin_)) * (float)max), 0, max);
	auto evpCol = GetColor(255, 165+ currentColor, currentColor);
	std::tuple<float,float,float> evpinCol = std::make_tuple(229.f, 0.f, 11.f);
	 	 	
	float currentRate = MathHelper::Clamp(targetPinRate_- defaultCount, 0.0f, 1.0f);
	
	float delay = 0.0f;
	//イベントポイントを作る
	std::function<void()> delaychange=[&]{
		delay = 0.0f; 
		currentRate = MathHelper::Clamp(targetPinRate_ - defaultCount, 0.0f, 1.0f);
	};
	for (auto& ep : enemy->GetEventPoints()) {
		Vector2 pos = Vector2{ ep.position_.x,fieldsize.y - ep.position_.z };
		pos *= size;
		pos += position;
		Vector2 bsize;
		bsize.x = ep.building_.lock()->getHorizonal();
		bsize.y = ep.building_.lock()->getVertical();
		bsize *= 17.0f*size;
		 	 	
		DrawBox((int)(pos.x - bsize.x * 0.5f), (int)(pos.y - bsize.y * 0.5f), (int)(pos.x + bsize.x * 0.5f), (int)(pos.y + bsize.y * 0.5f), evpCol, TRUE);
		DrawBox((int)(pos.x - bsize.x * 0.5f),(int)( pos.y - bsize.y * 0.5f), (int)(pos.x + bsize.x * 0.5f), (int)(pos.y + bsize.y * 0.5f), GetColor(0, 0, 0), FALSE);
		
		SetDrawBright((int)std::get<0>(evpinCol),(int) std::get<1>(evpinCol),(int) std::get<2>(evpinCol));

		//ピンを刺す
		Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_PIN);
		origin.x = 0.0f;

		delay = delayRate * (leftUpNumber_[ep.block_]);
		currentRate = MathHelper::Clamp(pinPosRate_ - defaultCount - delay, 0.0f, 1.0f);
		delaychange();
		delaychange = [] {};
		Vector2 drawPos = Vector2::Lerp(pos + defaultPinPos, pos, currentRate);
		constexpr int firstSize = 6;

		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_PIN, drawPos, origin,Vector2::One);
		SetDrawBright(255, 255, 255);

		evpCol = GetColor(67, 135, 233);
		evpinCol= std::make_tuple(0.f, 0.f, 0.f);
	}

	Vector2 pos = Vector2{ enemy->getPosition().x,fieldsize.y - enemy->getPosition().z }*size;
	pos += position;

#ifdef _DEBUG
	auto allPath = world_->getWalkMap().getNode(0);
	int cou = 0;
	for (auto& i : allPath) {
		Vector2 pos{ i.position.x,fieldsize.y-i.position.z };
		pos *= size;
		pos += position;
		DrawCircle(pos.x, pos.y, 5.0f, GetColor(0, 255, 0));
		DrawFormatString(pos.x, pos.y, GetColor(0, 0, 0), "%d", cou);

		for (auto& e : i.edges) {
			Vector2 ePos = { allPath[e.node].position.x,fieldsize.y - allPath[e.node].position.z };
			ePos *= size;
			ePos += position;
			DrawLine(pos.x, pos.y, ePos.x, ePos.y, GetColor(255, 0, 0));
		}

		cou++;
	}
#endif

	auto path = enemy->getPath();
	for (auto ep = path.rbegin(); ep != path.rend();++ep) {
		Vector2 epoint{ (*ep).x,fieldsize.y - (*ep).z };
		epoint *= size;
		epoint += position;
		DrawLineAA(pos.x, pos.y, epoint.x, epoint.y, GetColor(192, 0, 0), 4.0f);
		pos.x = epoint.x;
		pos.y = epoint.y;
	}


	//キャラ描画
	pos = Vector2{ enemy->getPosition().x,fieldsize.y - enemy->getPosition().z }*size;
	pos += position;
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_MAP_ENEMY);
	origin= origin *0.5f;
	
	Vector2 forward{ enemy->getRotation().Forward().x,enemy->getRotation().Forward().z };
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MAP_ENEMY, pos, origin, Vector2::One, MathAngle(forward,Vector2::Down) + 180.0f);

	//std::list<std::weak_ptr<Actor>> actors;
	//world_->findActors(ActorGroup::ENEMY_ACTOR, "Enemy", actors);
	//for (auto a : actors) {
	//	Vector2 pos = Vector2{ a.lock()->getPosition().x,fieldsize.y -a.lock()->getPosition().z }*size;
	//	pos += position;
	//	DrawCircle(pos.x, pos.y, 5, GetColor(255, 0, 0));
	//}

	Vector2 posit = Vector2{ world_->findActor("Player")->getPosition().x, fieldsize.y -world_->findActor("Player")->getPosition().z }*size;
	posit += position;
	origin = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_MAP_PLAYER);
	origin = origin * 0.5f;

	forward=Vector2{ world_->findActor("Player")->getRotation().Forward().x,world_->findActor("Player")->getRotation().Forward().z };
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MAP_PLAYER, posit, origin, Vector2::One, MathAngle(forward,Vector2::Down)+180.0f);
	//DrawCircle(posit.x, posit.y, 5, GetColor(0, 0, 255));


	//アイコン描画
	float xSlide = (float)world_->getFieldOnly()->getWidth() * SQUARES_WIDTH * size;

	pos = ICON_POS + position;
	pos.x += xSlide;
	for (auto& dil : drawIconList_) {
		SetDrawBright((int)std::get<2>(dil).x, (int)std::get<2>(dil).y, (int)std::get<2>(dil).z);
		Sprite::GetInstance().Draw(std::get<0>(dil), pos);
		pos.y += Sprite::GetInstance().GetSize(std::get<0>(dil)).y;

		SetDrawBright(255, 255, 255);
		Sprite::GetInstance().Draw(std::get<1>(dil), pos);
		pos.y += Sprite::GetInstance().GetSize(std::get<1>(dil)).y;

	}
}

void FieldMap::pin_reset()
{
	pinPosRate_ = defaultCount;
	targetPinRate_ = 0.0f;
}

void FieldMap::targetpin_reset()
{
	targetPinRate_ = defaultCount;

}

void FieldMap::pin_add(float deltaTime)
{
	pinPosRate_ += deltaTime* speedRate;
	targetPinRate_ += deltaTime* speedRate;
}
