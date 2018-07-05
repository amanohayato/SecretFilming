#ifndef ENEMY_H_
#define ENEMY_H_

#include <map>
#include "../Actor.h"
#include "../../Graphic/AnimationDx.h"
#include "../Body/BoundingCapsule.h"
#include "../../ID/EnumIDs.h"
#include "EnemyMovePointChooser.h"

// エネミークラス（ベースクラス）
// 制作者：Ho Siu Ki（何兆祺）
class Enemy : public Actor
{
private:
	enum class EnemyState
	{
		Idle,			// 静止
		Move,			// 移動
		Kouban,			// 交番イベント
		Takoyakiya,     // たこ焼き屋イベント
		Alley,			// 路地裏でのイベント
		Crossroad,      // 交差点でのイベント
		VendingMachine, // 自販機でのイベント
		SmokingArea,    // 喫煙所でのイベント
		Sakanaya,        // 魚屋イベント
		RandomEvent1,	// ランダムイベント1
		RandomEvent2,	// ランダムイベント2
		RandomEvent3,	// ランダムイベント3
		RandomEvent4	// ランダムイベント4
	};

	enum class EnemyAnimation
	{
		Idle = 0,			// 静止
		Move = 1,			// 移動
		Kouban = 2,			// 交番イベント
		Takoyakiya = 3,     // たこ焼き屋イベント
		Alley = 4,			// 路地裏でのイベント
		Crossroad = 5,      // 交差点でのイベント
		VendingMachine = 6, // 自販機でのイベント
		SmokingArea = 7,    // 喫煙所でのイベント
		Sakanaya = 8,	    // 魚屋イベント
		RandomEvent1 = 0,	// ランダムイベント1
		RandomEvent2 = 7,	// ランダムイベント2
		RandomEvent3 = 8,	// ランダムイベント3
		RandomEvent4 = 9	// ランダムイベント4
	};

	struct AnimStyle {
		AnimStyle(bool isloop, EnemyAnimation anim) :is_loop(isloop), animation(anim) { }
		bool is_loop;
		EnemyAnimation animation;
	};

public:
	// コンストラクタ
	Enemy(IWorld* world, const Vector3& position, int type, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	// 初期化
	void initialize() override;
	// 更新
	void update(float delta_time) override;
	// 描画
	void draw() const override;
	// 接触判定
	void onCollide(Actor& other) override;
	// メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;

private:
	// 状態の変更
	void change_state(EnemyState state);
	// アニメーションの変更
	void change_Animation(EnemyAnimation animID, float anim_frame = 0.0f, float anim_speed = 1.0f, bool is_loop = true, float blend_rate = 1.0f);
	// 静止状態の処理
	void idle(float delta_time);
	// 移動状態の処理
	void move(float delta_time);

	// 交番でのイベント
	void kouban(float delta_time);
	// たこ焼き屋でのイベント
	void takoyakiya(float delta_time);
	// 路地裏でのイベント
	void alley(float delta_time);
	// 交差点でのイベント
	void crossroad(float delta_time);
	// 自販機でのイベント
	void vending_machine(float delta_time);
	// 喫煙所でのイベント
	void smoking_area(float delta_time);
	// 魚屋でのイベント
	void sakanaya(float delta_time);

	// ランダムイベント1
	virtual void random_event1(float delta_time);
	// ランダムイベント2
	virtual void random_event2(float delta_time);
	// ランダムイベント3
	virtual void random_event3(float delta_time);
	// ランダムイベント4
	virtual void random_event4(float delta_time);

private:
	AnimationDx animation_;			// アニメーション
	EnemyMovePointChooser chooser_;	// 移動座標指定
	EnemyState state_;				// エネミーの状態
	float timer_{ 10.0f };			// タイマー

	// エネミーの状態とアニメーションの関連付け
	const std::map<EnemyState, AnimStyle> AnimConverter
	{
		{ EnemyState::Idle, AnimStyle{ true, EnemyAnimation::Idle } },
		{ EnemyState::Move, AnimStyle{ true, EnemyAnimation::Move } },
		{ EnemyState::Kouban, AnimStyle{ false, EnemyAnimation::Kouban } },
		{ EnemyState::Takoyakiya, AnimStyle{ false, EnemyAnimation::Takoyakiya } },
		{ EnemyState::Alley, AnimStyle{ false, EnemyAnimation::Alley } },
		{ EnemyState::Crossroad, AnimStyle{ false, EnemyAnimation::Crossroad } },
		{ EnemyState::VendingMachine, AnimStyle{ false, EnemyAnimation::VendingMachine } },
		{ EnemyState::SmokingArea, AnimStyle{ false, EnemyAnimation::SmokingArea } },
		{ EnemyState::Sakanaya, AnimStyle{ false, EnemyAnimation::Sakanaya } },
		{ EnemyState::RandomEvent1, AnimStyle{ false, EnemyAnimation::RandomEvent1 } },
		{ EnemyState::RandomEvent2, AnimStyle{ false, EnemyAnimation::RandomEvent2 } },
		{ EnemyState::RandomEvent3, AnimStyle{ false, EnemyAnimation::RandomEvent3 } },
		{ EnemyState::RandomEvent4, AnimStyle{ false, EnemyAnimation::RandomEvent4 } }
	};
};

#endif // !TEST_ENEMY_H_