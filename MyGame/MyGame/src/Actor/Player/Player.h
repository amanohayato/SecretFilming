#pragma once
#include"../Actor.h"
#include"../../Graphic/AnimationDx.h"
#include"../Body/BoundingCapsule.h"
#include"../../Method/CountTimer.h"
#include"Base/MatrixRotation.h"
#include"Base\Player_arm.h"
#include"Base\FPSCamera.h"
#include"State\PlayerState.h"
#include<memory>

class Player:public Actor {
public:
	enum class Player_Animation {
		Idle=0,
		Run=1,
		Jump=3,
		Slide=5,
		SlideJump=3,
		Float=3,
		Blow=7,
		Down = 8,
		GetUp = 9,
		Fly=6,
		WallRun=1,
		FloatJump = 3,
		FloatFall = 3,
		Fall=3,

	};

public:
	Player(IWorld* world, const Vector3& position, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{0.0f,0.0f,0.0f},Matrix::Identity,15.0f,4.0f));
	Player(IWorld* world, const Vector3& position,const Matrix& rotation, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	void initialize();

	void update(float deltaTime);

	void draw()const;

	virtual void onCollide(Actor& other);
	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;
	//プレイヤー状態
	Player_State_ID getStateType()const;
	//視点の取得
	FPSCamera& getFPSCamera();
	//腕の取得
	Player_arm& getArm();
private:

	//状態の更新
	bool change_State(Player_State_ID state);
	//状態の取得
	std::shared_ptr<PlayerState> getState(Player_State_ID state);
	//回避オブジェクト
	void hide_InCamera(BuildingBase& object);
	//衝突リアクション
	void hit(Vector3& dir);
	//壁と床の判定
	void collision();
	//タイルの判定
	void roadway();
private:
	//プレイヤー状態
	std::shared_ptr<PlayerState> state_;
	// カメラ用の回転行列
	Matrix cameraRotation_{ Matrix::Identity };
	//イベント用の回転行列(仮)
	Matrix mat_{Matrix::Identity};
	//獲得スコア
	int score_{ 1 };
	//イベント
	EventType type_{EventType::EVENT_NULL};
	//イベントの状態
	EventAction_State eventActionState_;
	//プレイヤー視点
	FPSCamera fpsCam_;
	//プレイヤー腕
	Player_arm arm_;

	CsvReader roadway_;//車道CSV読み込み用
	Vector3 beforpos_;//ポジションを記録
	
	bool collide{ false };
	//基本的なvelocityの乗算割合
	const float DefVelocityMult{ 0.8f };

	float velocityMultPower{ DefVelocityMult };

};