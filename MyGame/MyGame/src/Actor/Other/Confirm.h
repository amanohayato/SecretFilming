#pragma once
#include"../Actor.h"

class Confirm : public Actor
{
public:
	Confirm();

	Confirm(IWorld * world);

	void initialize();

	void update(float deltaTime) override;

	void draw()const;

	//メッセージの受信
	//virtual void receiveMessage(EventMessage message, void* param) override;

	void draw_nomber()const;

	void change_sprite();

	void set_world(IWorld * world, bool isFree);

private:
	static const int clearscore_{ 100 };//クリアスコアを定義する

	SPRITE_ID alien_{ SPRITE_ID::SPRITE_CONFIRM_ALIAN0 };

	int score_{ 0 };
	int state_{ 0 };
	float count{ 0.0f };
	float scorepercent_{ 0.f };
	float scoreRete_{ 0.f };
	float lerp{ 0.0f };
	float amount_{ 1.0f };
	bool isSS_{ false };
	const float drawX_{ 0.8f };
	const float drawY_{ 0.05f };
	const float drawNomberX_{ 28.f };
	const float drawNomberY_{ 38.f };
	bool isFree_{ false };//マップアプリ中にも表示するかのフラグ
};