#include "Confirm.h"
#include"../../Graphic/Sprite.h"
#include"../../Scene/Manager/GameDataManager.h"
#include"../../Define.h"
#include"../Player/Player.h"

Confirm::Confirm()
{

}

Confirm::Confirm(IWorld * world):
	Actor(world,"Confirm",Vector3::Zero)
{
	world_ = world;
}

void Confirm::initialize()
{
	
}

void Confirm::update(float deltaTime)
{
	if (amount_ == 1.6f) isSS_ = false;
	amount_ = MathHelper::Clamp(amount_ + deltaTime,0.0f,1.6f);
	if (score_ != GameDataManager::getInstance().getScore() && scorepercent_ != 1.f) {
		scoreRete_ = scorepercent_;
		isSS_ = true;
		amount_ = 0.0f;
		score_ = GameDataManager::getInstance().getScore();//現在のスコアの表示
		scorepercent_ = MathHelper::Clamp((float)score_ / (float)clearscore_, 0.0f, 1.0f);//パーセント表示にする
	}
	lerp = MathHelper::Lerp(scoreRete_, scorepercent_, MathHelper::Smoothstep(0.0f, 1.f, amount_));
	
	change_sprite(); 
	if (isFree_ == true) return;
	//テキスト表示が終わって2秒たったら消す
	if (count > 2.f)
	{
		world_->getTextBox().Hidden_Text();
		return;
	}
	//テキストを表示する
	if (score_ >= clearscore_)
	{
		if(world_->getTextBox().isEnd()==true)count += deltaTime;
		if (world_->getTextBox().Get_Current_Text() == 5)return;
		world_->getTextBox().Set_Current_Text(5);
		world_->getTextBox().Display_Text();
	}
}

void Confirm::draw() const
{
	if (isFree_ == true)
	{
		Sprite::GetInstance().Draw(alien_, Vector2{ (float)WINDOW_WIDTH * drawX_,(float)WINDOW_HEIGHT * drawY_ });
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CONFIRM, Vector2{ (float)WINDOW_WIDTH * drawX_,(float)WINDOW_HEIGHT * drawY_ + 270.f }, Vector2{ 0.f,270.0f }, Vector2{ 1.f,lerp });//パーセントを100倍する//100.0f
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CONFIRM_FRAME, Vector2{ (float)WINDOW_WIDTH * drawX_,(float)WINDOW_HEIGHT * drawY_ });
		draw_nomber();
		return;
	}

	auto currentstate = std::static_pointer_cast<Player>(world_->findActor("Player"))->getStateType();
	if (currentstate == Player_State_ID::MapApp || (world_->findActor("Player")->isCamera() && !isSS_))return;

	world_->addDrawFunction([&] {
		Sprite::GetInstance().Draw(alien_, Vector2{ (float)WINDOW_WIDTH * drawX_,(float)WINDOW_HEIGHT * drawY_ });
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CONFIRM, Vector2{ (float)WINDOW_WIDTH * drawX_,(float)WINDOW_HEIGHT * drawY_ + 270.f }, Vector2{ 0.f,270.0f }, Vector2{ 1.f,lerp});//パーセントを100倍する//100.0f
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CONFIRM_FRAME, Vector2{ (float)WINDOW_WIDTH * drawX_,(float)WINDOW_HEIGHT * drawY_ });
		draw_nomber();
	});
}

void Confirm::draw_nomber()const
{
	float digits = 3.f;
	Sprite::GetInstance().SplitDraw(
		SPRITE_ID::SPRITE_CONFIRM_NOMBER,
		Vector2{ (float)WINDOW_WIDTH * drawX_ + 75.f + digits * drawNomberX_,(float)WINDOW_HEIGHT * drawY_ + 270.f - drawNomberY_ },
		10
	);
	digits--;
	int temp = 0;
	float score = lerp * 100.f;

	do {
		temp = (int)fmodf(score, 10.f);
		Sprite::GetInstance().SplitDraw(
			SPRITE_ID::SPRITE_CONFIRM_NOMBER,
			Vector2{ (float)WINDOW_WIDTH * drawX_ + 75.0f + digits * drawNomberX_,(float)WINDOW_HEIGHT * drawY_ + 270.f - drawNomberY_ },
			temp
		);
		score = score / 10.f;
		digits--;
	} while (score >= 1.f);
}

void Confirm::change_sprite()
{
	float score = scorepercent_ * 10.f;
	int state = (int)fmodf(score, 11);
	if (state_ == state)return;
	state_ = state;
	switch (state_)
	{
	case 0:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN0;
		break;
	case 1:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN1;
		break;
	case 2:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN2;
		break;
	case 3:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN3;
		break;
	case 4:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN4;
		break;
	case 5:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN5;
		break;
	case 6:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN6;
		break;
	case 7:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN7;
		break;
	case 8:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN8;
		break;
	case 9:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN9;
		break;
	case 10:
		alien_ = SPRITE_ID::SPRITE_CONFIRM_ALIAN10;
		break;
	}

}

void Confirm::set_world(IWorld * world, bool isFree)
{
	world_ = world;
	isFree_ = isFree;
}
