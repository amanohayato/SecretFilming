#ifndef ENEMY_MOVE_POINT_CHOOSER_H_
#define ENEMY_MOVE_POINT_CHOOSER_H_

#include "../../Math/Vector3.h"
#include <vector>

class IWorld;

// �G�l�~�[�p�`�ړ����W�w��N���X
// ����ҁFHo Siu Ki�i�����Q�j

class EnemyMovePointChooser
{
public:
	// �R���X�g���N�^
	EnemyMovePointChooser(IWorld* world, const Vector3& position, int walk_sheet_type);
	// ���݂̃|�C���g��ݒ�
	void set_point(const Vector3& position);
	// ���̖ړI�n������i�����_���j
	void choose_goal();
	// ���̃|�C���g���擾
	int get_next_point()const;
	// 
	Vector3 operator()(const Vector3& position, bool& is_end);

private:
	int walk_sheet_type_;	// ���񂷂�ΏۃV�[�g
	IWorld* world_;
	int current_point_;		// ����̌o�H�̊J�n�n�_
	int goal_;				// �ړI�n�_
	std::vector<int> path_;	// �ړ����[�g
};

#endif // !ENEMY_MOVE_POINT_CHOOSER_H_