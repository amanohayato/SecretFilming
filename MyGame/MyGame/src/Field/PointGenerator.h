#pragma once
#include"../World/IWorld.h"
#include"../Resource/CsvReader.h"

class PointGenerator {
public:
	PointGenerator();
	PointGenerator(IWorld* world, const std::string& filename);

	~PointGenerator();

	//�l��ݒ肵�āA����������
	void setParameter(IWorld* world, const std::string& filename);

	//�|�C���g���̊Ď��A�|�C���g���������玟�̃|�C���g�𐶐�
	void update(float deltaTime);

	void draw()const;

	bool isEnd()const;
private:
	//�|�C���g����
	void generate();
private:
	IWorld* world_{ nullptr };//���[���h
	CsvReader reader_;//CSV�ǂݍ���
	int pointCount_{ 0 };//���������|�C���g��
	bool isEnd_{ false }; //�|�C���g��S���擾������I��

};