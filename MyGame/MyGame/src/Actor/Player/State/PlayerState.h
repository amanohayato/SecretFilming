#pragma once
#include"../Base/FPSCamera.h"
#include"../../../Math/Matrix.h"
#include"../../../Math/Vector3.h"
#include"../../../World/IWorld.h"
#include"../../Actor.h"
#include"State_ID.h"
#include<memory>
//プレイヤーステート基底クラス
class PlayerState : public std::enable_shared_from_this<PlayerState> {
public:
	//コンストラクタ
	PlayerState() = default;
	PlayerState(ActorPtr player);
	PlayerState(IWorld* world, ActorPtr player);
	//仮想デストラクタ
	virtual ~PlayerState() {}
	//開始
	virtual void start();
	//更新
	virtual void update(float deltaTime);
	//終了
	virtual void end();
	//入力を移動へ
	void input_to_move(float deltaTime);
	//床についているか
	void setFloor(bool prevfloor);
	//今の状態
	Player_State_ID getState()const;
	//次の状態
	Player_State_ID getNextState()const;
	//カメラ情報
	FPSCamera getFPSCam()const;
	//重力の取得
	float getGravity()const;
	//フラグ
	bool isCamera()const;
	bool isAction()const;

	void setIsWatch(const bool& isWatch);
	bool getIsWatch()const;
	//カメラ情報のセット
	void setFPSCam(FPSCamera cam);
	//イベント
	void setObjct(const Vector3& position,const Matrix& rotation);
protected:
	//ワールド
	IWorld * world_{ nullptr };
	//プレイヤー
	ActorPtr player_{nullptr};
	//今の状態
	Player_State_ID state_{Player_State_ID::Idle};
	//次の状態(デフォルトNULL)
	Player_State_ID nextState_{ Player_State_ID::Null };

	//プレイヤーの位置保管
	Vector3 playerPositionStr_{ Vector3::Zero };
	//回避オブジェクトの位置保管
	Vector3 objPositionStr_{ Vector3::Zero };
	//カメラ
	FPSCamera& fpsCam_;
	//回転行列
	Matrix rotation_{Matrix::Identity};
	Matrix objRotation_{ Matrix::Identity };
	// 移動速度の値（デフォルト100.0f）
	float moveSpeed_{ 30.0f };
	//前フレ床についてたか
	bool prevfloor_{ true };
	//カメラ状態か
	bool isCamera_{ false };
	//アクション状態か
	bool isAction_{ false };
	//オブジェクトを見ているか
	bool isWatch_{ false };
	//重力倍率
	float gravity_{ 0.0f };
};