#pragma once
#include"../../Actor.h"
#include"../../../Graphic/AnimationDx.h"
#include"../../Body/BoundingCapsule.h"
#include"../../../ID/EnumIDs.h"
//#include"../CityWalkPointChooser.h"
#include<map>
#include<list>


class EventPolice :public Actor {
private:
	enum class State {
		Walk,
		Idle,
		Down,
	};
	enum class Animation {
		Walk = 0,
		Idle = 1,
		Down = 2,
	};
	struct AnimStyle {
		AnimStyle(bool isloop, Animation anim) :isLoop(isloop), animation(anim) {

		}
		bool isLoop;
		Animation animation;
	};
public:
	EventPolice(IWorld* world, MODEL_ID id, int type, const IBodyPtr& body = std::make_shared<BoundingCapsule>(Vector3{ 0.0f,0.0f,0.0f }, Matrix::Identity, 15.0f, 4.0f));

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void shadowDraw()const;
	//死亡時
	virtual void end();
	//接触時
	virtual void onCollide(Actor& other) override;

	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param) override;

	void change_Animation(Animation animID, float animFrame = 0.0f, float animSpeed = 1.0f, bool isLoop = true, float blendRate = 1.0f);
	void change_State(State state);
private:
	void idle(float deltaTime);
	void walk(float deltaTime);
	void down(float deltaTime);

	//経路情報を登録する
	void setPath();
	//自身の向きを強制的に前に補正する
	void toForward();
private:
	AnimationDx animation_;//モデル及びアニメーションの管理

	MODEL_ID modelid_;//使用モデルのID

	State state_;//状態

	int type_;

	std::vector<Vector3> path_;

	Vector3 prevPath_;
	bool extrudedflag_ = false;
	const std::map<State, AnimStyle> AnimConverter{//ステートとアニメーションの関連付け
		{ State::Idle,AnimStyle{ false,Animation::Idle } },
	{ State::Walk,AnimStyle{ true,Animation::Walk } },
	{ State::Down,AnimStyle{ false,Animation::Down } }
	};
};