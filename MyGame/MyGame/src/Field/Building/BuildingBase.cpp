#include "BuildingBase.h"
#include "../../Graphic/DebugDraw.h"
#include"../../Actor/Body/Base/HitInfo.h"


BuildingBase::BuildingBase() : world_(nullptr), name_("NULL"), position_(Vector3::Zero), rotation_(Matrix::Identity), rotationNum_(0) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, const Vector3& position, int rotationNum) :
	world_(world), name_(name), position_(position), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), 
	colType_(ColType::Multiple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, const Vector3& position, const Triangle& triangle, int rotationNum) :
	world_(world), name_(name), position_(position), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), 
	collision_(triangle), colType_(ColType::Simple), rotationNum_(rotationNum) {
}

//** こいつを使用している **//
BuildingBase::BuildingBase(IWorld* world, const std::string& name, const Vector3& position, float horizontal, float vertical, int rotationNum) :
	world_(world), name_(name), position_(position), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), 
	collision_(position_, Vector3((-(horizontal / 2) * (float)SQUARES_WIDTH) - PLAYER_RADIUS, 0, (-(vertical / 2) * (float)SQUARES_HEIGHT) - PLAYER_RADIUS), Vector3(((horizontal / 2) * (float)SQUARES_WIDTH) + PLAYER_RADIUS, 0, ((vertical / 2) * (float)SQUARES_HEIGHT) + PLAYER_RADIUS)),
	colType_(ColType::Simple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, const Vector2& position, int rotationNum) :
	world_(world), name_(name), position_(Vector3(position.x, 0, position.y)), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), 
	colType_(ColType::Multiple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, const Vector2& position, const Triangle& triangle, int rotationNum) :
	world_(world), name_(name), position_(Vector3(position.x, 0, position.y)), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)),
	collision_(triangle), colType_(ColType::Simple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, const Vector2& position, float horizontal, float vertical, int rotationNum) :
	world_(world), name_(name), position_(Vector3(position.x, 0, position.y)), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), 
	collision_(position_, Vector3((-(horizontal / 2) * (float)SQUARES_WIDTH) - PLAYER_RADIUS, 0, (-(vertical / 2) * (float)SQUARES_HEIGHT)) - PLAYER_RADIUS, Vector3(((horizontal / 2) * (float)SQUARES_WIDTH) + PLAYER_RADIUS, 0, ((vertical / 2) * (float)SQUARES_HEIGHT) + PLAYER_RADIUS)), 
	colType_(ColType::Simple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, int rotationNum, const Vector2& offset) :
	world_(world), name_(name), position_(Vector3((widthNum * (float)SQUARES_WIDTH) + ((float)SQUARES_WIDTH / 2) + offset.x, 0, (heightNum * (float)SQUARES_HEIGHT) - ((float)SQUARES_HEIGHT / 2) + offset.y)),
	width_(widthNum), height_(heightNum), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), colType_(ColType::Multiple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, const Triangle& triangle, int rotationNum, const Vector2& offset) :
	world_(world), name_(name), position_(Vector3((widthNum * (float)SQUARES_WIDTH) + ((float)SQUARES_WIDTH / 2) + offset.x, 0, (heightNum * (float)SQUARES_HEIGHT) - ((float)SQUARES_HEIGHT / 2) + offset.y)),
	width_(widthNum), height_(heightNum), rotation_(Matrix::CreateRotationY((float)rotationNum * 90)), collision_(triangle), colType_(ColType::Simple), rotationNum_(rotationNum) {
}

BuildingBase::BuildingBase(IWorld* world, const std::string& name, int widthNum, int heightNum, float horizontal, float vertical, int rotationNum, const Vector2& offset) :
	horizontal_(rotationNum%2==0 ? horizontal:vertical), vertical_(rotationNum % 2 == 0 ? vertical : horizontal),//縦か横かで向き毎のサイズを補正する
	world_(world), name_(name), position_(Vector3((widthNum * (float)SQUARES_WIDTH) + ((horizontal_ * (float)SQUARES_WIDTH) / 2) + offset.x, 0, (heightNum * (float)SQUARES_HEIGHT) - ((vertical_ * (float)SQUARES_HEIGHT) / 2) + offset.y)),
	width_(widthNum), height_(heightNum), rotation_(Matrix(Matrix::Identity)*Matrix::CreateRotationY((float)rotationNum * 90)), collision_(position_, Vector3((-(horizontal / 2) * (float)SQUARES_WIDTH) - PLAYER_RADIUS, 0, (-(vertical / 2) * (float)SQUARES_HEIGHT) - PLAYER_RADIUS), Vector3(((horizontal / 2) * (float)SQUARES_WIDTH) + PLAYER_RADIUS, 0, ((vertical / 2) * (float)SQUARES_HEIGHT) + PLAYER_RADIUS)),
	colType_(ColType::Simple), rotationNum_(rotationNum) {
}

void BuildingBase::initialize() {
	
}

void BuildingBase::update(float deltaTime) {
	
}

void BuildingBase::draw() const {

}

void BuildingBase::end() {

}

void BuildingBase::onEvent() {

}

std::shared_ptr<BuildingBase> BuildingBase::clone() {
	return std::make_shared<BuildingBase>(world_, name_, position_, rotationNum_);
}

std::shared_ptr<BuildingBase> BuildingBase::clone(IWorld* world, const Vector3& position, int rotationNum) {
	return std::make_shared<BuildingBase>(world, "NULL", position, rotationNum);
}

std::shared_ptr<BuildingBase> BuildingBase::clone(IWorld* world, const Vector2& position, int rotationNum) {
	return std::make_shared<BuildingBase>(world, "NULL", Vector3(position.x, 0, position.y), rotationNum);
}

std::shared_ptr<BuildingBase> BuildingBase::clone(IWorld* world, int width, int height, int rotationNum, const Vector2& offset) {
	return std::make_shared<BuildingBase>(world, "NULL", width, height, rotationNum, offset);
}

void BuildingBase::onCollide(Actor& other) {

}

bool BuildingBase::isCollide(const Actor & other)
{
	Matrix pose = (Matrix::CreateRotationY(180.0f)*rotation_).Translation(position_);
	return body_->transform(pose)->isCollide(*other.getBody()->transform(other.getPose()).get(), HitInfo());
}

void BuildingBase::collide()
{
	ActorPtr player = world_->findActor("Player");

	if (player == nullptr) return;
	
	if (!isActive_)return;

	if (isCollide(*player)) {
		onCollide(*player);
	}
}
bool BuildingBase::hitCheckAndNoEntry(Vector3& position)
{
	if (!isActive_)return false;
	switch (colType_)
	{
	case BuildingBase::Simple:
		return collision_.transform(getPose()).hitCheckAndNoEntry(position);
		break;
	case BuildingBase::Multiple:
		for (auto c : colList_) {
			c.transform(getPose()).hitCheckAndNoEntry(position);
		}
		break;
	}
	return false;
}

bool BuildingBase::hitCheck(Vector3& position) {
	if (!isActive_)return false;
	switch (colType_)
	{
	case BuildingBase::Simple:
		return collision_.transform(getPose()).check(position);
		break;
	case BuildingBase::Multiple:
		for (auto c : colList_) {
			c.transform(getPose()).check(position);
		}
		break;
	}
	return false;
}

ActorPtr BuildingBase::getPlayer() {
	return world_->findActor("Player");
}

Vector3 BuildingBase::getPlayerPosition() {
	return world_->findActor("Player")->getPosition();
}

void BuildingBase::getActorStatus(Actor& other) {

}

Vector3 & BuildingBase::getPosition()
{
	return position_;
}

Vector3 BuildingBase::getPosition() const {
	return position_;
}

Matrix & BuildingBase::getRotation()
{
	return rotation_;
}

Matrix BuildingBase::getRotation() const {
	return rotation_;
}

Matrix BuildingBase::getPose() const {
	return Matrix(rotation_).Translation(position_);
}
IBodyPtr BuildingBase::getbody() const
{
	return body_;
}

bool BuildingBase::isPlay() const {
	return isPlay_;
}

void BuildingBase::Played() {
	isPlay_ = true;
}

PlayerStatus BuildingBase::getStatus() const
{
	return status_;
}


int BuildingBase::getModelHandle() const
{
	return animation_.getModelHandle();
}

EventType BuildingBase::getEvent() const {
	return eventType_;
}

void BuildingBase::callEvent() {
	switch (eventType_)
	{
	case EventType::EVENT_NULL:
		break;
	case EventType::EVENT_POLICE:
		police();
		break;
	case EventType::EVENT_TAKOYAKIYA:
		takoyakiya();
		break;
	case EventType::EVENT_BACKSTREET_RATI:
		back_street1();
		break;
	case EventType::EVENT_BACKSTREET_KAIWA:
		back_street2();
		break;
	case EventType::EVENT_JUNCTION:
		junction();
		break;
	case EventType::EVENT_VENDING:
		vending();
		break;
	case EventType::EVENT_SMOKING:
		smoking();
		break;
	case EventType::EVENT_FISHSTORE:
		fish_store();
		break;
	default:
		break;
	}
}

bool BuildingBase::isDead() const {
	return isDead_;
}

BuildingCollision& BuildingBase::getCollision() {
	return collision_;
}

std::list<BuildingCollision>& BuildingBase::getCollisions(){
	return colList_;
}

void BuildingBase::police()
{
}

void BuildingBase::takoyakiya()
{
}

void BuildingBase::back_street1()
{
}

void BuildingBase::back_street2()
{
}

void BuildingBase::junction()
{
}

void BuildingBase::vending()
{
}

void BuildingBase::smoking()
{
}

void BuildingBase::fish_store()
{
}
