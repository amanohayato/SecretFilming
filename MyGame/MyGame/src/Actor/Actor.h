#pragma once
#include<memory>
#include"../World/IWorld.h"
#include"../Math/Math.h"
#include"Body/Base/IBodyPtr.h"
#include"Body/Base/DummyBody.h"
#include"../Field/Building/BuildingBase.h"
#include<functional>

//キャラクター基底クラス
class Actor:public std::enable_shared_from_this<Actor> {
public:
	Actor();
	Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<DummyBody>());
	Actor(IWorld* world, const std::string& name, const Vector3& position,const Matrix& rotation, const IBodyPtr& body = std::make_shared<DummyBody>());
	virtual ~Actor() {}
	//子を初期化
	void rootInitialize();
	//子を更新
	void rootUpdate(float deltaTime);
	//子を描画
	void rootDraw()const;
	void rootShadowDraw()const;
	

	//初期化
	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void shadowDraw()const;
	//死亡時
	virtual void end();
	virtual bool isCollide(const Actor& other);
	virtual void onCollide(Actor& other);
	virtual void onCollide(BuildingBase& other);
	//メッセージの受信
	virtual void receiveMessage(EventMessage message, void* param=nullptr);

	// 衝突処理
	void collide(Actor& other);
	//ステージとの共通当たり判定
	bool field(Vector3& result);
	//ステージ床面限定当たり判定
	bool floor(Vector3& result);
	//子供を追加する
	void addChild(ActorPtr child);
	//識別番号の設定
	void setNumber(int cn);
	//識別番号の取得
	int getNumber()const;
	//種類の設定
	void setGroup(ActorGroup group);
	//種類の取得
	ActorGroup getGroup()const;
	//名前の取得
	std::string getName()const;
	//判定の取得
	IBodyPtr getBody()const;
	//位置の取得
	Vector3 getPosition()const;
	Vector3& getPosition();
	//回転行列の取得
	Matrix getRotation()const;
	// 変換行列の取得
	Matrix Actor::getPose() const;
	//子供の数を取得
	unsigned int getChildCount()const;
	//死んでるか
	bool isDead()const;
	bool isAction() const;
	void setAction(bool isAction);
	bool isCamera()const;
	void setCamera(bool isCamera);
	//死亡させる
	virtual void dead();
	//子を全て消す
	void clearChildren();
	//名前を基準に検索を行う
	ActorPtr findCildren(const std::string& name);
	//関数の条件に合った対象のうち一番早く見つかった物を取ってくる
	ActorPtr findCildren(std::function<bool(const Actor&)> fn);
	void findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList);

	std::list<ActorPtr>& getChildren();

	// 子を巡回
	void eachChildren(std::function<void(Actor&)>  fn);
	// 子を巡回 (const版）
	void eachChildren(std::function<void(const Actor&)> fn) const;
	
	void collideChildren(Actor& other);

	//子の削除
	void removeChildren();
	//子の削除
	void removeChildren(std::function<bool(Actor&)> fn);

	void handleMessage(EventMessage message, void* param);

	void setDraw(bool isDraw);
protected:
	//キャラクター識別番号
	int characterNumber_{ -1 };
	//自身の種類
	ActorGroup group_;
	// ワールド
	IWorld*	world_{ nullptr };
	// 名前
	std::string	name_;
	// 座標
	Vector3	position_{ Vector3::Zero };
	//1フレーム毎の移動量
	Vector3 velocity_{ Vector3::Zero };
	//前フレームの座標
	Vector3 prevPosition_{ Vector3::Zero };
	Matrix prevRotation_{ Matrix::Identity };
	// 回転
	Matrix	rotation_{ Matrix::Identity };
	// 衝突判定
	IBodyPtr body_;

	bool isDead_{ false };
	bool isDraw_{ true };
	//カメラのフラグ
	bool isCamera_{ false };

	//アクションフラグ
	bool isAction_{ false };
	// 子アクター
	std::list<ActorPtr> children_;
};