#pragma once
#include"../Actor.h"

class IconControl : public Actor
{
public:

	IconControl(IWorld * world);

	void initialize();

	void update(float deltaTime) override;

	void draw()const;

	void camera_icon_flashing();

	void map_icon_flashing();

	//メッセージの受信
	//virtual void receiveMessage(EventMessage message, void* param) override;


private:
	const float Yicon_drawX_{ 0.06f };//マップアイコンの座標調節用
	const float Yicon_drawY_{ 0.01f };
	const float LTicon_drawX_{ 0.16f };//カメラアイコンの座標調節用
	const float LTicon_drawY_{ 0.01f };
	const float mapicon_drawX_{ 0.01f };//マップアイコンの座標調節用
	const float mapicon_drawY_{ 0.03f };
	const float cameraicon_drawX_{ 0.11f };//カメラアイコンの座標調節用
	const float cameraicon_drawY_{ 0.03f };
	const float alerticon_drawX_{ 0.21f };//アラートアイコンの座標調節用
	const float alerticon_drawY_{ 0.03f };//アラートアイコンの座標調節用
	int score_{ 0 };//エネミーのスコア状態を取得
	float map_alpha_{ 1.f };//マップのアルファ値
	float camera_alpha_{ 1.f };//カメラのアルファ値
	bool camera_alphaup_{ false };//カメラのアルファ値をプラスするフラグ
	bool map_alphaup_{ false };//マップのアルファ値をプラスするフラグ
	const float speed_{ 3.f };//点滅のスピード
	const float map_flashing_time_{ 10.0f };//マップアイコンが点滅している時間を設定
	bool points_change_{ false };//目的地が切り替わったとき用のフラグ
	float flashing_count_{ 0.f };//マップアイコンが点滅している時間をカウント
	Vector3 event_pos_{ 0.f, 0.f, 0.f };//eventposition取得用
	Vector3 before_event_pos_{ 0.f, 0.f, 0.f };////eventposition比較用
	float deltaTime_;

	float _alert_alpha{ 0.0f };
};