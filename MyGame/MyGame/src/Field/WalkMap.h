#pragma once
#include"../Math/TwoDimensionalArray.h"
#include"../Math/Vector3.h"

class WalkMap {
public:
	WalkMap();
	void initialize();
	//csv�t�@�C���̓ǂݍ���
	void load(const std::string& pointfilename, const std::string& mapfilename);
	//�ړI�n�ɂ��ǂ蒅�����߂̎��̒n�_����������
	int getNextWalkPoint(int target,int current, int goal);
	//�n�_�̍��W���擾����
	Vector3 getPosition(int target,int point)const;
	int getSize(int target)const;
	int getNearestPoint(int target,const Vector3& position);

private:
	int size{ 0 };
	std::vector<TwoDimensionalArray<int>> walkPointMap_;//�Ԃ��ړI�n�ɓ��B���邽�߂̌o�H��ۑ�����}�b�v
	std::vector<std::vector<Vector3>> walkPoints_;//���H�|�C���g���X�g

};