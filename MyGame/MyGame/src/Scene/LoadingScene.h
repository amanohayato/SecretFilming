#pragma once
#include"Scene.h"
#include<vector>

//���\�[�X�ǂݍ��ݐ�p�V�[��
class LoadingScene :public Scene {
public:
	LoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//�摜�̓ǂݍ���
	void LoadSprite();
	//���f���̓ǂݍ���
	void LoadModel();
	//���f���̓ǂݍ���
	void LoadEffect();
	//�����t�H���g�̓ǂݍ���
	void LoadFont();
	//BGM�̓ǂݍ���
	void LoadBGM();
	//SE�̓ǂݍ���
	void LoadSE();
	//�V�F�[�_�[�̓ǂݍ���
	void LoadShader();
	//���̑��X�e�[�W���̓ǂݍ���
	void LoadEtcetera();

	void LoadSpriteAnim();
private:
	int _animCount{ 0 };

	std::vector<int> _loadAnimList;
};