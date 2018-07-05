#pragma once
#include<memory>
#include"../World/IWorld.h"
#include"../Math/Math.h"
#include"Body/Base/IBodyPtr.h"
#include"Body/Base/DummyBody.h"
#include"../Field/Building/BuildingBase.h"
#include<functional>

//�L�����N�^�[���N���X
class Actor:public std::enable_shared_from_this<Actor> {
public:
	Actor();
	Actor(IWorld* world, const std::string& name, const Vector3& position, const IBodyPtr& body = std::make_shared<DummyBody>());
	Actor(IWorld* world, const std::string& name, const Vector3& position,const Matrix& rotation, const IBodyPtr& body = std::make_shared<DummyBody>());
	virtual ~Actor() {}
	//�q��������
	void rootInitialize();
	//�q���X�V
	void rootUpdate(float deltaTime);
	//�q��`��
	void rootDraw()const;
	void rootShadowDraw()const;
	

	//������
	virtual void initialize();
	virtual void update(float deltaTime);
	virtual void draw()const;
	virtual void shadowDraw()const;
	//���S��
	virtual void end();
	virtual bool isCollide(const Actor& other);
	virtual void onCollide(Actor& other);
	virtual void onCollide(BuildingBase& other);
	//���b�Z�[�W�̎�M
	virtual void receiveMessage(EventMessage message, void* param=nullptr);

	// �Փˏ���
	void collide(Actor& other);
	//�X�e�[�W�Ƃ̋��ʓ����蔻��
	bool field(Vector3& result);
	//�X�e�[�W���ʌ��蓖���蔻��
	bool floor(Vector3& result);
	//�q����ǉ�����
	void addChild(ActorPtr child);
	//���ʔԍ��̐ݒ�
	void setNumber(int cn);
	//���ʔԍ��̎擾
	int getNumber()const;
	//��ނ̐ݒ�
	void setGroup(ActorGroup group);
	//��ނ̎擾
	ActorGroup getGroup()const;
	//���O�̎擾
	std::string getName()const;
	//����̎擾
	IBodyPtr getBody()const;
	//�ʒu�̎擾
	Vector3 getPosition()const;
	Vector3& getPosition();
	//��]�s��̎擾
	Matrix getRotation()const;
	// �ϊ��s��̎擾
	Matrix Actor::getPose() const;
	//�q���̐����擾
	unsigned int getChildCount()const;
	//����ł邩
	bool isDead()const;
	bool isAction() const;
	void setAction(bool isAction);
	bool isCamera()const;
	void setCamera(bool isCamera);
	//���S������
	virtual void dead();
	//�q��S�ď���
	void clearChildren();
	//���O����Ɍ������s��
	ActorPtr findCildren(const std::string& name);
	//�֐��̏����ɍ������Ώۂ̂�����ԑ�������������������Ă���
	ActorPtr findCildren(std::function<bool(const Actor&)> fn);
	void findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList);

	std::list<ActorPtr>& getChildren();

	// �q������
	void eachChildren(std::function<void(Actor&)>  fn);
	// �q������ (const�Łj
	void eachChildren(std::function<void(const Actor&)> fn) const;
	
	void collideChildren(Actor& other);

	//�q�̍폜
	void removeChildren();
	//�q�̍폜
	void removeChildren(std::function<bool(Actor&)> fn);

	void handleMessage(EventMessage message, void* param);

	void setDraw(bool isDraw);
protected:
	//�L�����N�^�[���ʔԍ�
	int characterNumber_{ -1 };
	//���g�̎��
	ActorGroup group_;
	// ���[���h
	IWorld*	world_{ nullptr };
	// ���O
	std::string	name_;
	// ���W
	Vector3	position_{ Vector3::Zero };
	//1�t���[�����̈ړ���
	Vector3 velocity_{ Vector3::Zero };
	//�O�t���[���̍��W
	Vector3 prevPosition_{ Vector3::Zero };
	Matrix prevRotation_{ Matrix::Identity };
	// ��]
	Matrix	rotation_{ Matrix::Identity };
	// �Փ˔���
	IBodyPtr body_;

	bool isDead_{ false };
	bool isDraw_{ true };
	//�J�����̃t���O
	bool isCamera_{ false };

	//�A�N�V�����t���O
	bool isAction_{ false };
	// �q�A�N�^�[
	std::list<ActorPtr> children_;
};