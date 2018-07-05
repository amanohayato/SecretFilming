#ifndef ENEMY_BASE_H_
#define ENEMY_BASE_H_

#include <map>
#include "../Actor.h"
#include "../../Graphic/AnimationOutSide.h"
#include "../Body/BoundingCapsule.h"
#include "../../ID/EnumIDs.h"
#include "EnemyMovePointChooser.h"
#include "../../Field/Building/SendEventToEnemy.h"
#include "../../Event/RandomEvent/RandomEventManager/RandomEventManager.h"
#include "EnemyCap.h"
#include "../EventActor/EventEnemy/EnemyHatManager/EnemyHatManager.h"
#include"../UIActor/TextActor.h"

// エネミーベースクラス
// 担当：Ho Siu Ki（何兆祺）

class EnemyBase : public Actor
{
	friend class EnemyCap;

public:
	// エネミーの状態
	enum class EnemyState
	{
		Idle,				// 静止
		Move,				// 移動
		Escape,				// 逃走
		Goal,				// ゴール到達
		PoliceBox,			// 交番イベント
		Takoyakiya,			// たこ焼き屋イベント
		BackStreet1,		// 路地裏でのイベント1
		BackStreet2,		// 路地裏でのイベント2
		Junction,			// 交差点でのイベント
		VendingMachine,		// 自販機でのイベント
		SmokingArea,		// 喫煙所でのイベント
		FishMonger,			// 魚屋イベント
		RandomEvent1,		// ランダムイベント1
		RandomEvent2,		// ランダムイベント2
		RandomEvent3,		// ランダムイベント3
		//PreAction,		// 予備動作
		Stop,				// 停止
		DiscoveryStart,		// プレイヤー発見開始
		Discovery,			// プレイヤー発見
		DiscoveryEnd,		// プレイヤー発見終了
		Aware,				// 警戒
		LookBack,			// 振り返る
		ToPlayer,			// 振り返る
	};
	// エネミーのアニメーション
	enum class EnemyAnimation
	{
		Idle = 0,			// 静止
		Move = 1,			// 移動
		Escape = 2,			// 逃走
		Angry = 5,			// 怒り
		Goal = 0,			// ゴールイベント
		PoliceBox = 4,		// 交番イベント
		Takoyakiya = 5,     // たこ焼き屋イベント
		BackStreet1 = 6,	// 路地裏でのイベント1
		BackStreet2 = 4,	// 路地裏でのイベント2
		Junction = 3,		// 交差点でのイベント
		VendingMachine = 8, // 自販機でのイベント
		VendingMachine_Poi = 9,
		SmokingArea = 10,   // 喫煙所でのイベント
		FishMonger = 4,	    // 魚屋イベント
		RandomEvent1 = 12,	// ランダムイベント1
		RandomEvent2 = 12,	// ランダムイベント2
		RandomEvent3 = 12,	// ランダムイベント3
		PreAction = 11,		// 事前動作
		Stop = 0,			// 停止
		Aware = 11,			// 警戒
		Hat = 12,			// 帽子つける
		Me_Mogaki = 3,		// 目のもがき
		Nod = 12,
		LOOK_UP = 13,		// UFOを見上げる
		UDEKUMI = 14,		// 腕組
		Manhole_Rescue = 7,	// レスキュー		
		Manhole_Fall = 16,	// マンホール落下
		FallDown = 17,      // 転ぶ
		RisingHat = 18,     // 起き上がる
		Gaze1 = 19,			// のぞき開始
		Gaze2 = 20,			// のぞき動き
		Gaze3 = 21,			// のぞき終了
		Memory_Delete = 22,	// 記憶消去
		Kaiwa = 23,         // 会話
		LookBack = 24,		// 振り返る
		LookLeft = 25,
		LookRight = 26,
	};

	// アニメーションの再生設定
	struct AnimStyle
	{
		AnimStyle(bool isloop, EnemyAnimation anim) :is_loop(isloop), animation(anim) { }
		bool is_loop;
		EnemyAnimation animation;
	};

public:
	// コンストラクタ
	EnemyBase(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));
	virtual ~EnemyBase();
	// 初期化
	void initialize() override;
	// 更新
	void update(float delta_time) override;
	// 描画
	void draw() const override;
	void shadowDraw() const override;
	// 接触判定
	virtual void onCollide(Actor& other) override;
	// メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param = nullptr) override;
	// イベントの取得
	void get_event();
	// 回転行列の取得
	Matrix& get_rotation();
	// アニメーションクラスの取得
	AnimationOutSide& get_animation();
	// イベントフラグの設定
	EnemyState get_state()const { return state_; }
	void set_is_event(bool is_event);
	bool get_is_event()const;

	std::list<EventPoint>& GetEventPoints();
	//担当者以外追加分
	/*******************************************************/
	float get_awareness()const;
	void set_awareness(const float &awareness);//クリアイベント演出用
	std::string get_ui_target()const;
	int getBaseScore()const;
	void setBaseScore(int score);
	Vector3 getHeadPos()const;
	void on_Barrier(ActorPtr target, ActorPtr enemy, bool isStop = false);//バリア
	std::array<Vector3, 3> getHeadVertex()const;

	bool isPathEnd()const;

	//どっちが近いパスかを返す
	std::vector<Vector3> GetNearPath(const std::vector<Vector3>& p1, const std::vector<Vector3>& p2);


	std::vector<Vector3> getPath()const;

	std::shared_ptr<EnemyHatManager> GetEnemyHat();

	void setNextEvent();

	void fallcap();
	void pickcap();
	void wearcap();
	/*******************************************************/
protected:
	// 状態の変更
	void change_state(EnemyState state);
	// アニメーションの変更
	void change_animation(EnemyAnimation animID, float anim_frame = 0.0f, float anim_speed = 1.0f, bool is_loop = true, float blend_rate = 1.0f);
	// 静止状態の処理
	void idle(float delta_time);
	// 移動状態の処理
	void move(float delta_time);
	// 逃走状態の処理
	void escape(float delta_time);
	// ゴールイベント処理
	void goal(float delta_time);
	// 停止状態の処理
	void stop(float delta_time);
	//プレイヤー発見開始の処理
	void discoveryStart(float delta_time);
	//プレイヤー発見時の処理
	void discovery(float delta_time);
	//プレイヤー発見終了の処理
	void discoveryEnd(float delta_time);
	// 警戒状態の処理
	void aware(float delta_time);
	// 振り返る処理
	void look_back(float delta_time);
	// 振り返る時間の設定
	void set_look_back_time();

	void to_player(float deltaTime);

	// プレーヤーが見える距離内にいるか
	bool is_player_in_viewing_distance();
	// プレーヤーが見える視野角内にいるか
	bool is_player_in_viewing_angle();
	// プレーヤーが見えるか
	bool can_see_player();
	// プレーヤー方向の角度を求める
	float player_position_angle() const;

	// 次の目的地への経路探索
	void next_destinstion();

	// 警戒度処理
	void awareness(float delta_time);
	// 警戒ゲージの表示
	void show_awareness();

	// 交番でのイベント処理
	virtual void police_box(float delta_time);
	// たこ焼き屋でのイベント処理
	virtual void takoyakiya(float delta_time);
	// 路地裏でのイベント1処理
	virtual void back_street_1(float delta_time);
	// 路地裏でのイベント2処理
	virtual void back_street_2(float delta_time);
	// 交差点でのイベント処理
	virtual void junction(float delta_time);
	// 自販機でのイベント処理
	virtual void vending_machine(float delta_time);
	// 喫煙所でのイベント処理
	virtual void smoking_area(float delta_time);
	// 魚屋でのイベント処理
	virtual void fish_monger(float delta_time);

	// ランダムイベント1処理
	virtual void random_event1(float delta_time);
	// ランダムイベント2処理
	virtual void random_event2(float delta_time);
	// ランダムイベント3処理
	virtual void random_event3(float delta_time);

	//事前動作処理
	//virtual void pre_action(float delta_time);

	//目的イベントを次のイベントに設定
	void setNextEventPath();
	void setNextEventPath_Reset();

	void setText(const std::string& text);
protected:

	std::shared_ptr<EnemyHatManager> mEnemyHatManager;
	AnimationOutSide animation_;		// アニメーション
	EnemyState state_;					// エネミーの状態

	std::weak_ptr<Actor> player_;		// プレーヤーの参照
	float viewing_distance_{ 120.0f };	// 視線距離
	float viewing_angle_{ 40.0f };		// 視野角（度）

	float timer_{ 10.0f };				// タイマー（秒）
	float normal_speed_{ 0.0f };		// 通常時の移動速度
	float escape_speed_{ 0.0f };		// 逃走時の移動速度

	float look_back_timer_;				// 振り返るタイマー

	float escape_timer_{ 10.0f };		// 逃走状態タイマー
	float goal_timer_{ 0.0f };			// ゴールタイマー（ゲームオーバーシーンに移行までの時間）
	float goal_time_{ 10.0f };      //ゲームオーバーシーンに移行するまでの時間をここで定義する

	float awareness_{ 0.0f };			// 警戒度
	float aware_up_rate_{ 0.2f };		// 警戒度上昇量
	float aware_down_rate_{ 0.2f };		// 警戒度減少量
	float awareness_timer_{ 0.0f };		// 警戒度減少タイマー
	float aware_state_timer_{ 0.0f };	// 警戒状態タイマー

	bool is_goal_{ false };				// ゴールに到達したか
	bool is_event_{ false };			// イベント状態であるか
	bool is_aware_{ false };			// 警戒中であるか
	bool is_performance_{ false }; //クリア演出前演出中かあるか

	float delta_time_ = 10.0f;

	Vector3 player_position_{ Vector3::Zero };

	std::weak_ptr<EnemyCap> cap_;

	Vector3 head_pos{ Vector3::Zero };//頭の位置
	std::array<Vector3, 3> head_vertex{ Vector3::Zero,Vector3::Zero,Vector3::Zero };//頭のサイズ
	std::function<void()> change_state_;
	std::function<void()> last_walk_path_;
	// 目的地リスト
	std::list<EventPoint> event_points_;
	// 次の目的地への経路
	std::vector<Vector3> path_;

	int score_{ 0 };

	// ****************************************
	// 大槻嵩弘追加分
	// 警戒時のメッセージを表示するかフラグ
	bool displayWarningText_{ true };

	// ランダムイベントの発生フラグ
	bool randomEventFlag_{ true };
	// ****************************************

	// エネミーの状態とアニメーションの関連付け
	const std::map<EnemyState, AnimStyle> AnimConverter
	{
		{ EnemyState::Idle, AnimStyle{ true, EnemyAnimation::Idle } },						// 静止
		{ EnemyState::Move, AnimStyle{ true, EnemyAnimation::Move } },						// 移動
		{ EnemyState::Escape, AnimStyle{ true, EnemyAnimation::Escape } },					// 逃走
		{ EnemyState::Goal, AnimStyle{ false, EnemyAnimation::Goal } },						// ゴールイベント
		{ EnemyState::PoliceBox, AnimStyle{ false, EnemyAnimation::PoliceBox } },			// 交番イベント
		{ EnemyState::Takoyakiya, AnimStyle{ false, EnemyAnimation::Takoyakiya } },			// たこ焼き屋イベント
		{ EnemyState::BackStreet1, AnimStyle{ false, EnemyAnimation::BackStreet1 } },		// 路地裏イベント1
		{ EnemyState::BackStreet2, AnimStyle{ false, EnemyAnimation::BackStreet2 } },		// 路地裏イベント2
		{ EnemyState::Junction, AnimStyle{ false, EnemyAnimation::Junction } },				// 交差点イベント
		{ EnemyState::VendingMachine, AnimStyle{ false, EnemyAnimation::VendingMachine } },	// 自販機イベント
		{ EnemyState::SmokingArea, AnimStyle{ false, EnemyAnimation::SmokingArea } },		// 喫煙所イベント
		{ EnemyState::FishMonger, AnimStyle{ false, EnemyAnimation::FishMonger } },			// 魚屋イベント
		{ EnemyState::RandomEvent1, AnimStyle{ false, EnemyAnimation::RandomEvent1 } },		// ランダムイベント1
		{ EnemyState::RandomEvent2, AnimStyle{ false, EnemyAnimation::RandomEvent2 } },		// ランダムイベント2
		{ EnemyState::RandomEvent3, AnimStyle{ false, EnemyAnimation::RandomEvent3 } },		// ランダムイベント3
		//{ EnemyState::PreAction, AnimStyle{ false, EnemyAnimation::PreAction } },			// 事前動作
		{ EnemyState::Stop, AnimStyle{ true, EnemyAnimation::Stop } },						// 停止
		{ EnemyState::DiscoveryStart, AnimStyle{ false, EnemyAnimation::Gaze1 } },			// プレイヤー発見開始
		{ EnemyState::Discovery, AnimStyle{ true, EnemyAnimation::Gaze2 } },				// プレイヤー発見
		{ EnemyState::DiscoveryEnd, AnimStyle{ false, EnemyAnimation::Gaze3 } },			// プレイヤー発見終了
		{ EnemyState::Aware, AnimStyle{ true, EnemyAnimation::Aware } },					// 警戒
		{ EnemyState::LookBack, AnimStyle{ false, EnemyAnimation::LookBack } },				// 振り返る
		{ EnemyState::ToPlayer, AnimStyle{ true, EnemyAnimation::Move } },						// 移動
	};

private:
	std::shared_ptr<RandomEventManager>eventManager_;

	std::weak_ptr<TextActor> _text{};
};

#endif // !ENEMY_BASE_H_