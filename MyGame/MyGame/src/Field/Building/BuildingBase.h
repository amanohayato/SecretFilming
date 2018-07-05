#ifndef BUILDING_BASE_H_
#define BUILDING_BASE_H_

#include "../../World/IWorld.h"
#include "BuildingCollision.h"
#include "../../Actor/Actor.h"
#include "../../ID/EnumIDs.h"
#include "../../Graphic/AnimationDx.h"

#include <functional>

#define SQUARES_WIDTH		16.5f		// マス目の横サイズ
#define SQUARES_HEIGHT		16.5f		// マス目の縦サイズ

#define ROAD_WIDTH			20			// 道路の幅

#define PLAYER_RADIUS		4			// プレイヤーの半径
static constexpr int sliceSize = 3;
//プレイヤーの回避時のステータス
struct PlayerStatus
{
	Vector3 position_{ Vector3::Zero };
	Matrix rotation_{ Matrix::Identity };
	Vector3 getPosition()const { return position_; }
	Matrix getRotation()const { return rotation_; }
	void setPosition(const Vector3& position) { position_ = position; }
	void setRotation(const Matrix& rotation) { rotation_ = rotation; }
};

class BuildingBase {
public:
	enum ColType {
		Simple,
		Multiple
	};
public:
	// デフォルト
	BuildingBase();
	// Vector3で位置を決める
	BuildingBase(IWorld* world, const std::string& name, const Vector3& position, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector3& position, const Triangle& triangle, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector3& position, float horizontal, float vertical, int rotationNum = 0);
	// Vector2で位置を決める
	BuildingBase(IWorld* world, const std::string& name, const Vector2& position, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector2& position, const Triangle& triangle, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector2& position, float horizontal, float vertical, int rotationNum = 0);
	// マス目に位置を合わせる
	BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, const Triangle& triangle, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, float horizontal, float vertical, int rotationNum = 0, const Vector2& offset = Vector2::Zero);


	virtual ~BuildingBase() {}

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void end();

	// 建物毎のイベント
	virtual void onEvent();

	virtual std::shared_ptr<BuildingBase> clone();
	virtual std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum = 0);
	virtual std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum = 0);
	virtual std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);

	// アクターと当たった時
	virtual void onCollide(Actor& other);
	bool isCollide(const Actor & other);
	void collide();
	// アクターとの当たり判定
	bool hitCheckAndNoEntry(Vector3& position);
	bool hitCheck(Vector3& position);

	// Playerの情報取得
	ActorPtr getPlayer();
	// Playerの位置を取得
	Vector3 getPlayerPosition();
	// アクターのステータスを取得
	void getActorStatus(Actor& other);

	Vector3& getPosition();
	Vector3 getPosition()const;
	Matrix& getRotation();
	Matrix getRotation()const;
	Matrix BuildingBase::getPose() const;
	IBodyPtr getbody()const;

	//メッセージの送信
	virtual void message(EventMessage eventMessage, void* param=nullptr) {}

	bool isPlay() const;
	void Played();

	PlayerStatus getStatus()const;

	int getModelHandle()const;
	EventType getEvent() const;
	virtual void callEvent();

	bool isDead() const;
	virtual void setTexture(int type){}
	// 当たり判定を取得
	BuildingCollision& getCollision();
	std::list<BuildingCollision>& getCollisions();

	AnimationDx& getAnimation() {
		return animation_;
	}

	//当たり判定の有効化,無効化
	void setActive(bool isActive) { isActive_ = isActive; }
	bool getActive()const { return isActive_; }
	float getHorizonal()const { return horizontal_; }
	float getVertical()const { return vertical_; }
protected:
	// 仮のイベント関数
	virtual void police();
	virtual void takoyakiya();
	virtual void back_street1();
	virtual void back_street2();
	virtual void junction();
	virtual void vending();
	virtual void smoking();
	virtual void fish_store();

protected:
	// 識別マス番号
	int width_{ -1 };
	int height_{ -1 };

	float horizontal_{ -1 };
	float vertical_{ -1 };
	// 回転番号(0=0°1=90°2=180°3=270°)
	int rotationNum_{ 0 };

	IWorld*	world_{ nullptr };
	std::string name_;
	Vector3 position_{ Vector3::Zero };
	Matrix  rotation_{ Matrix::Identity };
	bool isDead_{ false };

	PlayerStatus status_;


	ColType colType_{ ColType::Simple };
	// 建物の衝突判定
	BuildingCollision collision_;
	AnimationDx animation_{};

	EventType eventType_{ EventType::EVENT_NULL };
	//回避オブジェクトの衝突判定
	IBodyPtr body_{ std::make_shared<DummyBody>() };

	using CollisionList = std::list<BuildingCollision>; 
	CollisionList colList_;

	int num_{ 0 }; // 建物番号

	// Eventが発生したか
	bool isPlay_{ false };

	//当たり判定の有効フラグ
	bool isActive_{ true };
};

#endif // !BUILDING_BASE_H_

