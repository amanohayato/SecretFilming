#include "EnemyMovePointChooser.h"
#include "../../World/IWorld.h"
#include "../../Field/WalkMap.h"
#include "../../Math/Random.h"
#include "../../Field/WalkPath.h"
#include <assert.h>

// �G�l�~�[�p�`�ړ����W�w��N���X
// ����ҁFHo Siu Ki�i�����Q�j

// �R���X�g���N�^
EnemyMovePointChooser::EnemyMovePointChooser(IWorld* world, const Vector3& position, int walk_sheet_type)
	: world_(world), walk_sheet_type_(walk_sheet_type)
{
	set_point(position);
}

// ���݂̃|�C���g��ݒ�
void EnemyMovePointChooser::set_point(const Vector3& position)
{
	current_point_ = world_->getWalkMap().getNearestNode(walk_sheet_type_, position);
	goal_ = current_point_;
}

// ���̖ړI�n������i�����_���j
void EnemyMovePointChooser::choose_goal()
{
	current_point_ = goal_;
	int goal = Random::GetInstance().Range(0, (int)world_->getWalkMap().node_count(walk_sheet_type_) - 2);
	if (goal < goal_)goal_ = goal;
	else goal_ = goal + 1;

	auto path = WalkPath::find_path(world_->getWalkMap(), walk_sheet_type_, current_point_, goal_);
	path_.clear();
	path_.assign(path.rbegin(), path.rend());
}

// ���̃|�C���g���擾
int EnemyMovePointChooser::get_next_point() const
{
	assert(!path_.empty());
	return path_.front();
}

// 
Vector3 EnemyMovePointChooser::operator()(const Vector3& position, bool& is_end)
{
	is_end = false;
	Vector3 next = world_->getWalkMap().getNode(walk_sheet_type_, get_next_point()).position;	// ���̖ړI�n���擾
	next.y = position.y;				// y���͖���
	if (Vector3::Distance(position, next) <= 10.0f)		// �ړI�n�ɓ��B������
	{
		if (path_.front() == goal_)						// �ŏI�ړI�n�ɓ��B������
		{
			is_end = true;				// �I����������
			return position;			// �ړ����Ȃ�
		}
		path_.erase(path_.begin());		// ���̖ړI�n�ֈړ�
	}
	return world_->getWalkMap().getNode(walk_sheet_type_, get_next_point()).position;			// ���̖ړI�n��n��
}