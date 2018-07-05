#pragma once
#include"../Math/TwoDimensionalArray.h"
#include"../Math/Vector3.h"

class IWorld;//�e�X�g�p
class CityMap {
public:
	CityMap();
	~CityMap();
	void initialize();
	//csv�t�@�C���̓ǂݍ���
	void load(const std::string& filename, const std::string& mapfilename);
	//�ړI�n�ɂ��ǂ蒅�����߂̎��̒n�_����������
	int getNextCarPoint(int current,int goal);
	//�n�_�̍��W���擾����
	Vector3 getPosition(int point)const;
	void getWorld(IWorld* wrd);//�e�X�g
	int getSize()const;
	int getNearestPoint(const Vector3& position);
	float getFlyPointY(int indexNum)const;
	void draw()const;//�f�o�b�O�\��
private:
	TwoDimensionalArray<int> carPointMap_;//�Ԃ��ړI�n�ɓ��B���邽�߂̌o�H��ۑ�����}�b�v
	std::vector<Vector3> carPoints_;//���H�|�C���g���X�g
	std::vector<float> flyPointsy_;//��s�py�����W���X�g
	IWorld* world;//�e�X�g�p���[���h
};