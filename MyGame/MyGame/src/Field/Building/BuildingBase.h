#ifndef BUILDING_BASE_H_
#define BUILDING_BASE_H_

#include "../../World/IWorld.h"
#include "BuildingCollision.h"
#include "../../Actor/Actor.h"
#include "../../ID/EnumIDs.h"
#include "../../Graphic/AnimationDx.h"

#include <functional>

#define SQUARES_WIDTH		16.5f		// �}�X�ڂ̉��T�C�Y
#define SQUARES_HEIGHT		16.5f		// �}�X�ڂ̏c�T�C�Y

#define ROAD_WIDTH			20			// ���H�̕�

#define PLAYER_RADIUS		4			// �v���C���[�̔��a
static constexpr int sliceSize = 3;
//�v���C���[�̉�����̃X�e�[�^�X
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
	// �f�t�H���g
	BuildingBase();
	// Vector3�ňʒu�����߂�
	BuildingBase(IWorld* world, const std::string& name, const Vector3& position, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector3& position, const Triangle& triangle, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector3& position, float horizontal, float vertical, int rotationNum = 0);
	// Vector2�ňʒu�����߂�
	BuildingBase(IWorld* world, const std::string& name, const Vector2& position, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector2& position, const Triangle& triangle, int rotationNum = 0);
	BuildingBase(IWorld* world, const std::string& name, const Vector2& position, float horizontal, float vertical, int rotationNum = 0);
	// �}�X�ڂɈʒu�����킹��
	BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, const Triangle& triangle, int rotationNum = 0, const Vector2& offset = Vector2::Zero);
	BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, float horizontal, float vertical, int rotationNum = 0, const Vector2& offset = Vector2::Zero);


	virtual ~BuildingBase() {}

	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void end();

	// �������̃C�x���g
	virtual void onEvent();

	virtual std::shared_ptr<BuildingBase> clone();
	virtual std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector3& position, int rotationNum = 0);
	virtual std::shared_ptr<BuildingBase> clone(IWorld* world, const Vector2& position, int rotationNum = 0);
	virtual std::shared_ptr<BuildingBase> clone(IWorld* world, int width, int height, int rotationNum = 0, const Vector2& offset = Vector2::Zero);

	// �A�N�^�[�Ɠ���������
	virtual void onCollide(Actor& other);
	bool isCollide(const Actor & other);
	void collide();
	// �A�N�^�[�Ƃ̓����蔻��
	bool hitCheckAndNoEntry(Vector3& position);
	bool hitCheck(Vector3& position);

	// Player�̏��擾
	ActorPtr getPlayer();
	// Player�̈ʒu���擾
	Vector3 getPlayerPosition();
	// �A�N�^�[�̃X�e�[�^�X���擾
	void getActorStatus(Actor& other);

	Vector3& getPosition();
	Vector3 getPosition()const;
	Matrix& getRotation();
	Matrix getRotation()const;
	Matrix BuildingBase::getPose() const;
	IBodyPtr getbody()const;

	//���b�Z�[�W�̑��M
	virtual void message(EventMessage eventMessage, void* param=nullptr) {}

	bool isPlay() const;
	void Played();

	PlayerStatus getStatus()const;

	int getModelHandle()const;
	EventType getEvent() const;
	virtual void callEvent();

	bool isDead() const;
	virtual void setTexture(int type){}
	// �����蔻����擾
	BuildingCollision& getCollision();
	std::list<BuildingCollision>& getCollisions();

	AnimationDx& getAnimation() {
		return animation_;
	}

	//�����蔻��̗L����,������
	void setActive(bool isActive) { isActive_ = isActive; }
	bool getActive()const { return isActive_; }
	float getHorizonal()const { return horizontal_; }
	float getVertical()const { return vertical_; }
protected:
	// ���̃C�x���g�֐�
	virtual void police();
	virtual void takoyakiya();
	virtual void back_street1();
	virtual void back_street2();
	virtual void junction();
	virtual void vending();
	virtual void smoking();
	virtual void fish_store();

protected:
	// ���ʃ}�X�ԍ�
	int width_{ -1 };
	int height_{ -1 };

	float horizontal_{ -1 };
	float vertical_{ -1 };
	// ��]�ԍ�(0=0��1=90��2=180��3=270��)
	int rotationNum_{ 0 };

	IWorld*	world_{ nullptr };
	std::string name_;
	Vector3 position_{ Vector3::Zero };
	Matrix  rotation_{ Matrix::Identity };
	bool isDead_{ false };

	PlayerStatus status_;


	ColType colType_{ ColType::Simple };
	// �����̏Փ˔���
	BuildingCollision collision_;
	AnimationDx animation_{};

	EventType eventType_{ EventType::EVENT_NULL };
	//����I�u�W�F�N�g�̏Փ˔���
	IBodyPtr body_{ std::make_shared<DummyBody>() };

	using CollisionList = std::list<BuildingCollision>; 
	CollisionList colList_;

	int num_{ 0 }; // �����ԍ�

	// Event������������
	bool isPlay_{ false };

	//�����蔻��̗L���t���O
	bool isActive_{ true };
};

#endif // !BUILDING_BASE_H_

