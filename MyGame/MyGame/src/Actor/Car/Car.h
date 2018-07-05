#pragma once
#include"../Actor.h"
#include"../Body/BoundingCapsule.h"
#include"../../ID/EnumIDs.h"
//#include"PointChooser.h"

//町を巡回する車クラス
class Car :public Actor {
private:
	enum class CarState {
		Idle,
		Move
	};
public:
	Car(IWorld* world,std::string name, MODEL_ID id1, MODEL_ID id2, MODEL_ID id3, int type,bool is_front, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix(Matrix::Identity)*Matrix::CreateRotationX(90.0f), 40.0f, 10.5f));

	void update(float deltaTime);

	void draw()const;
	void shadowDraw()const override;

	//接触時
	virtual void onCollide(Actor& other);

	virtual void receiveMessage(EventMessage message, void * param) override;

	void change_State(CarState state);

	void hit_Enemy(const Vector3& dir);

	void move();
	//止まっている状態
	void Idle();
	void Signal();
	//信号の状態をセット
	void setsignal(bool signal);
private:
	static const int deadpos_y_ = 1024;

	MODEL_ID modelid_;
	MODEL_ID modelid_move1_;
	MODEL_ID modelid_move2_;
	MODEL_ID modelid_lamp_;
	std::list<Vector3> path_;//ルート
	int type_;//
	bool enemyhitflag_ =false;//エネミーと当たったか
	bool signal_ = false;//信号が青or赤黄か
	CsvReader crosswalk_;//車道CSV読み込み
	CarState carstate_;//車の状態
	bool is_front_;//正面向きかどうかのフラグ
	Vector3 velocity_{ Vector3::Zero };
	float count_ = 0;
	float delta_time_;
};