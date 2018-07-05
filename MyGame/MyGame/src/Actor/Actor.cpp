#include "Actor.h"
#include<algorithm>
#include"../Field/FieldBase.h"
#include"../Field/Building/BuildingBase.h"
#include"Body/Base/HitInfo.h"
#include"../ID/EnumIDs.h"

Actor::Actor():world_(nullptr),name_("Null"),position_(Vector3::Zero),body_(std::make_shared<DummyBody>()),children_(),group_(ActorGroup::ETCETERA_ACTOR)
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const IBodyPtr & body):
	world_(world),name_(name),position_(position),body_(body), children_(), group_(ActorGroup::ETCETERA_ACTOR)
{
}

Actor::Actor(IWorld * world, const std::string & name, const Vector3 & position, const Matrix & rotation, const IBodyPtr & body):
	world_(world), name_(name), position_(position),rotation_(rotation), body_(body), children_(), group_(ActorGroup::ETCETERA_ACTOR)
{
}


void Actor::rootInitialize()
{
	initialize();
	eachChildren([&](Actor& actor) {actor.rootInitialize(); });
}

void Actor::rootUpdate(float deltaTime)
{
	prevPosition_ = position_;
	prevRotation_ = rotation_;

	update(deltaTime);
	eachChildren([&](Actor& actor) {actor.rootUpdate(deltaTime); });
}

void Actor::rootDraw() const
{
	if(isDraw_)draw();
	eachChildren([&](const Actor& actor) {actor.rootDraw(); });

}

void Actor::rootShadowDraw() const
{
	if (isDraw_)shadowDraw();
	eachChildren([&](const Actor& actor) {actor.rootShadowDraw(); });
}

void Actor::initialize()
{
	isDead_ = false;
	isDraw_ = true;
}

void Actor::update(float deltaTime)
{
}

void Actor::draw() const
{
}

void Actor::shadowDraw() const
{
}

void Actor::end()
{
}

bool Actor::isCollide(const Actor & other)
{
	return body_->transform(getPose())->isCollide(*other.getBody()->transform(other.getPose()).get(), HitInfo());
}

void Actor::onCollide(Actor & other)
{
}

void Actor::onCollide(BuildingBase& other)
{
}

void Actor::receiveMessage(EventMessage message, void * param)
{
}

void Actor::collide(Actor& other) {
	//���g�Ɠ������Ă���
	if (isCollide(other)) {
		//���݂��ɒʒm����
		onCollide(other);
		other.onCollide(*this);
	}
	//�q���ɂ������蔻�肳����
	eachChildren([&](Actor& child) { child.collide(other); });
}

// �t�B�[���h�Ƃ̏Փ˔���
bool Actor::field(Vector3& result) {
	Vector3 hitPos;
	if (world_->getFieldOnly()->getMesh().collide_line(prevPosition_ + rotation_.Up()*(body_->length()*0.5f), position_ + rotation_.Up()*(body_->radius() + body_->length()*0.5f), (VECTOR*)&hitPos)) {
		Vector3 upVec = rotation_.Up()*(body_->radius() + body_->length()*0.5f);
		position_ = hitPos - upVec;
	}
	Vector3 hitcenter;
	if (world_->getFieldOnly()->getMesh().collide_capsule(position_ + rotation_.Up()*(body_->length()*0.5f), position_ + rotation_.Down()*(body_->length()*0.5f), body_->radius(), (VECTOR*)&hitcenter))
	{
		result = hitcenter;

		return true;
	}
	return false;
}

bool Actor::floor(Vector3 & result)
{
	Vector3 hitpos;
	if (world_->getFieldOnly()->getMesh().collide_line(position_, prevPosition_, (VECTOR*)&hitpos)) {
		position_ = hitpos+ rotation_.Up()*(body_->radius() + body_->length()*0.5f);
	}
	if (world_->getFieldOnly()->getMesh().collide_line(position_, position_ + rotation_.Down()*(body_->radius()+body_->length()*0.5f +2.f), (VECTOR*)&hitpos)) {
		result = hitpos;
		return true;
	}
	return false;
}

void Actor::addChild(ActorPtr child)
{
	children_.push_back(child);
}

void Actor::setNumber(int cn)
{
	characterNumber_ = cn;
}

int Actor::getNumber() const
{
	return characterNumber_;
}

void Actor::setGroup(ActorGroup group)
{
	group_ = group;
}

ActorGroup Actor::getGroup() const
{
	return group_;
}

std::string Actor::getName() const
{
	return name_;
}

IBodyPtr Actor::getBody() const
{
	return body_;
}

Vector3 Actor::getPosition() const
{
	return position_;
}

Vector3 & Actor::getPosition()
{
	return position_;
}

Matrix Actor::getRotation() const
{
	return rotation_;
}

Matrix Actor::getPose() const {
	return Matrix(rotation_).Translation(position_);
}

unsigned int Actor::getChildCount() const
{
	return (unsigned int)children_.size();
}

bool Actor::isDead() const
{
	return isDead_;
}
bool Actor::isAction() const
{
	return isAction_;
}
void Actor::setAction(bool isAction)
{
	isAction_ = isAction;
}
/**********************************************************************/
bool Actor::isCamera()const {
	return isCamera_;
}
void Actor::setCamera(bool isCamera)
{
	isCamera_ = isCamera;
}
/*********************************************************************/
void Actor::dead()
{
	isDead_ = true;
}

void Actor::clearChildren() {
	children_.clear();
}

// �q�̌���
ActorPtr Actor::findCildren(const std::string& name) {
	return findCildren(
		[&](const Actor& actor) { return actor.getName() == name; });
}

// �q�̌���
ActorPtr Actor::findCildren(std::function<bool(const Actor&)> fn) {
	//�������ɍ������q���������炻�������Ă���
	const auto i = std::find_if(children_.begin(), children_.end(),
		[&](const ActorPtr& child) { return fn(*child); });
	if (i != children_.end()) {
		return *i;
	}
	//�q�����X�Ɏq���������Ă����ꍇ�A���̒�������{��
	for (const auto& child : children_) {
		const auto actor = child->findCildren(fn);
		if (actor != nullptr) {
			return actor;
		}
	}
	//�Ώۂ����Ȃ�������null��Ԃ�
	return nullptr;
}
void Actor::findCildren(const std::string & name, std::list<std::weak_ptr<Actor>>& actorList)
{
	//�q�̒����疼�O�������Ă鑊������X�g�ɒǉ����Ă���
	eachChildren([&](Actor& actor) {
		if (actor.getName() == name) {
			//���g��shared_ptr��weak_ptr�̃��X�g�ɓ����
			actorList.push_back(actor.shared_from_this());
		}
	});
}

std::list<ActorPtr>& Actor::getChildren()
{
	return children_;
}

// �q������
void Actor::eachChildren(std::function<void(Actor&)>  fn) {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q������ (const�Łj
void Actor::eachChildren(std::function<void(const Actor&)> fn) const {
	std::for_each(
		children_.begin(), children_.end(),
		[&](const ActorPtr& child) { fn(*child); });
}

// �q�̏Փ˔���
void Actor::collideChildren(Actor& other) {
	eachChildren(
		[&](Actor& my) {
		other.eachChildren([&](Actor& target) { my.collide(target); });
	});
}

// �q���폜
void Actor::removeChildren() {
	removeChildren([](Actor& child) { return child.isDead(); });
	eachChildren([](Actor& child) { child.removeChildren(); });
}

// �q���폜
void Actor::removeChildren(std::function<bool(Actor&)> fn) {
	children_.remove_if(
		[&](const ActorPtr& child) { return fn(*child); });
}

void Actor::handleMessage(EventMessage message, void * param)
{
	//�S���Ƀ��b�Z�[�W�𑗂�
	eachChildren([&](Actor& actor) {
		receiveMessage(message, param);
	});
}

void Actor::setDraw(bool isDraw)
{
	isDraw_ = isDraw;
}
