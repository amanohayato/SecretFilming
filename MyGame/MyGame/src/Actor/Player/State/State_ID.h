#pragma once
enum class Player_State_ID {
	Null=0,//なし
	Idle,//待機
	Fall,//落下
	Launch,//衝突時の打ち上げ
	SetUp,//カメラを構える
	Dash,//ダッシュ
	Event_Before,//イベントアクション前
	EventAction,//イベントアクション
	Event_After,//イベントアクション後
	MapApp,//マップアプリを起動する
	ActionReset,//視界のリセット
};