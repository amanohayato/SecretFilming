#include "IconControl.h"
#include"../../Graphic/Sprite.h"
#include"../../Scene/Manager/GameDataManager.h"
#include"../../Define.h"
#include "../Enemy/EnemyBase.h"

IconControl::IconControl(IWorld * world)
{
	world_ = world;
}

void IconControl::initialize()
{
	_alert_alpha = 0.0f;
}

void IconControl::update(float deltaTime)
{
	deltaTime_ = deltaTime;
	// 敵の宇宙人を取得
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//点数が入る状態を取得
	score_ = std::static_pointer_cast<EnemyBase>(enemy)->getBaseScore();
	//イベントポイントが空だったらreturn
	if (std::static_pointer_cast<EnemyBase>(enemy)->GetEventPoints().empty())return;
	//イベント目的地を取得
	event_pos_ = std::static_pointer_cast<EnemyBase>(enemy)->GetEventPoints().front().position_;
	//現在の目的地が前の目的地と違っていた場合、内容を更新してポイントチェンジフラグをtrueにする
	if (before_event_pos_.x != event_pos_.x || before_event_pos_.z != event_pos_.z)
	{
		before_event_pos_ = event_pos_;
		points_change_ = true;
	}
	camera_icon_flashing();
	map_icon_flashing();
	
	constexpr float alpharate = 3.0f;
	if (enemy->get_awareness() >= 0.01f&&world_->findActor("NoticedLine") == nullptr)
		_alert_alpha = MathHelper::Clamp(_alert_alpha + deltaTime* alpharate, 0.0f, 1.0f);
	else
		_alert_alpha = MathHelper::Clamp(_alert_alpha - deltaTime* alpharate, 0.0f, 1.0f);

	//DrawFormatString(500, 400, GetColor(255, 255, 255), "%d,anime,%d", score_, animeend_);
}

void IconControl::draw() const
{
	if (world_->getMapAmount() >= 0.01f)return;
	world_->addDrawFunction([&] {
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_MAP_ICON, Vector2{ WINDOW_WIDTH*mapicon_drawX_,WINDOW_HEIGHT*mapicon_drawY_ }, map_alpha_);
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CAMERA_ICON, Vector2{ WINDOW_WIDTH*cameraicon_drawX_,WINDOW_HEIGHT*cameraicon_drawY_ }, camera_alpha_);
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_Y_PUSH, Vector2{ WINDOW_WIDTH*Yicon_drawX_,WINDOW_HEIGHT*Yicon_drawY_ }, Vector2::Zero, Vector2(0.2f, 0.2f));
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LT_PUSH, Vector2{ WINDOW_WIDTH*LTicon_drawX_,WINDOW_HEIGHT*LTicon_drawY_ }, Vector2::Zero, Vector2(0.2f, 0.2f));

		std::weak_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
		auto alert = 100.0f - enemy.lock()->get_awareness();
		auto rect = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_ALERT_GAUGE_ICON);
		auto handle = Sprite::GetInstance().GetHandle(SPRITE_ID::SPRITE_ALERT_GAUGE_ICON);

		int ypos = (int)(rect.y * alert * 0.01f);
		int rectsize = rect.y - ypos;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255.0f * _alert_alpha));
		DrawRectGraph((int)(WINDOW_WIDTH * alerticon_drawX_), (int)(WINDOW_HEIGHT * alerticon_drawY_ + rect.y - rectsize), 0, ypos, rect.x, rectsize, handle, TRUE, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_ALERT_FRAME_ICON, Vector2{ (float)WINDOW_WIDTH * alerticon_drawX_,(float) WINDOW_HEIGHT * alerticon_drawY_ }, _alert_alpha);
	});
}

void IconControl::camera_icon_flashing()
{
	//カメラアイコン点滅の処理
	if (score_ != 0 && camera_alphaup_ == false)
	{

		camera_alpha_ -= deltaTime_ * speed_;
		if (camera_alpha_ <= 0)
		{
			camera_alpha_ = 0;
			camera_alphaup_ = true;
		}
	}
	else if (score_ != 0 && camera_alphaup_ == true)
	{
		camera_alpha_ += deltaTime_ * speed_;
		if (camera_alpha_ >= 1.0f)
		{
			camera_alpha_ = 1.0f;
			camera_alphaup_ = false;
		}
	}
	else
	{
		camera_alpha_ = 1.0f;
		camera_alphaup_ = false;
	}
}

void IconControl::map_icon_flashing()
{
	//マップアイコン点滅処理
	if (flashing_count_ >= map_flashing_time_)
	{
		map_alpha_ = 1.0f;
		map_alphaup_ = false;
		points_change_ = false;
		flashing_count_ = 0.f;
	}
	else if (points_change_ == true && map_alphaup_ == false)
	{
		map_alpha_ -= deltaTime_ * speed_;
		flashing_count_ += deltaTime_ * speed_;
		if (map_alpha_ <= 0.f)
		{
			map_alpha_ = 0.f;
			map_alphaup_ = true;
		}
	}
	else if (points_change_ == true && map_alphaup_ == true)
	{
		map_alpha_ += deltaTime_ * speed_;
		flashing_count_ += deltaTime_ * speed_;
		if (map_alpha_ >= 1.0f)
		{
			map_alpha_ = 1.0f;
			map_alphaup_ = false;
		}
	}
}
