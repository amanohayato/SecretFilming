#include "PointGenerator.h"
#include"../ID/EnumIDs.h"
#include"../Actor/Other/CheckPoint.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"

#include"../Graphic/FontManager.h"

PointGenerator::PointGenerator():world_(nullptr),reader_()
{
}

PointGenerator::PointGenerator(IWorld * world,const std::string& filename)
	:world_(world), reader_(filename){
	generate();
}

void PointGenerator::setParameter(IWorld * world, const std::string & filename)
{
	//������
	pointCount_ = 0;
	isEnd_ = false;

	//�l�̐ݒ�
	world_ = world;
	reader_.load(filename);

	for (int i = 0; i < reader_.rows();i++) {//����
		generate();
	}
}

PointGenerator::~PointGenerator()
{
	world_ = nullptr;
}

void PointGenerator::update(float deltaTime)
{
	//if (world_ == nullptr)return;//���[���h�������ĂȂ������琶�����Ȃ�

	//if (isEnd_)return;//�S���o���I����Ă�������������Ȃ�
	
	//�|�C���g�����Ȃ��Ȃ��Ă���A�Q�[���N���A
	if (world_->getActorCount(ActorGroup::POINT_ACTOR) == 0) {
		isEnd_ = true;
	//	generate();
	}
}

void PointGenerator::draw() const
{
	//int t = reader_.rows() - pointCount_ + 1;
	int t = world_->getActorCount(ActorGroup::POINT_ACTOR);
	FontManager::GetInstance().DrawTextApplyFont(WINDOW_WIDTH / 2, 0, GetColor(255, 255, 255), FONT_ID::FONT_COUNT, "%d", t);
}

bool PointGenerator::isEnd() const
{
	return isEnd_;
}

void PointGenerator::generate()
{
	//�S���o������I���
	if (reader_.rows() <= pointCount_) {
		isEnd_ = true;
		pointCount_++;
		return;
	}
	Vector3 position;
	position.x = reader_.getf(pointCount_, 0);
	position.y = reader_.getf(pointCount_, 1);
	position.z = reader_.getf(pointCount_, 2);

	// world_->addActor(ActorGroup::POINT_ACTOR, std::make_shared<Enemy>(world_, position));

	pointCount_++;
}
