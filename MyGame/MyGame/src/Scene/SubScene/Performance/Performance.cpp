#include "Performance.h"
#include"../../../Scene/Manager/GameDataManager.h"
//#include"../../../Define.h"
#include"../../../Graphic/Sprite.h"

static constexpr float drawX_ = 200.0f;
static constexpr float drawY_ = 800.0f;

Performance::Performance()
{
}

void Performance::start()
{
	textBox_.Init();
	textBox_.add("gameover.txt");
	textBox_.add("gameclear.txt");
	textBox_.Start_Text();
	textBox_.Display_Text();
	count = 0;
	confirm_ = static_cast<Confirm*>(world_->findActor("Confirm").get());
}

void Performance::update(float deltaTime)
{
	if (GameDataManager::getInstance().getGameStop() == false)return;
	if (textBox_.Get_Current_Text() != 1&& GameDataManager::getInstance().getScore() >= 100)textBox_.Increment_Text();

	
	
	//GameDataManager::getInstance().setGameStop(true);
	textBox_.Update();
	//confirm_.update(deltaTime);
	
	if (textBox_.isEnd() == false)return;

	count += deltaTime;
	
	if (count > 1)textBox_.Hidden_Text();
	
	if (count > 2)GameDataManager::getInstance().setGameStop(false);
}

void Performance::draw() const
{
	if (GameDataManager::getInstance().getGameStop() == false)return;
	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLIND, Vector2::Zero);
	textBox_.Draw(Vector2{ drawX_,drawY_ });
	confirm_->draw();

	//Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_BLACK, Vector2::Zero);//,alfa_
}

void Performance::end()
{
}

void Performance::setWorld(IWorld* world)
{
	world_ = world;
}
