#pragma once
#include"AnimLoader.h"
#include"../ID/EnumIDs.h"
#include"../Math/Matrix.h"
#include"../Graphic/Model.h"

class AnimationOutSide {
public:

	explicit AnimationOutSide(int model);
	~AnimationOutSide();

	//frameTime=�t���[���ύX����
	void update(float frameTime);
	void Draw(const Matrix& rotation) const;

	void changeAnimation(int key, bool isLoop = true, float animSpeed = 1.0f, float blendRate = 1.0f, float animTime = 0.0f);

	bool isEnd()const;
	int getModelHandle() const;
	//�A�j���[�V�����Đ����Ԃ��擾����
	float getGetCurrentAnimTime()const;
private:
	int model_;//���f���n���h��
	
	int currentAnimKey_{ -1 };//���A�j���[�V�����L�[
	int previousAnimKey_{ -1 };//�O�A�j���[�V�����L�[

	int currentAnim_{ -1 };//���A�j���[�V����
	int previousAnim_{ -1 };//�O�A�j���[�V����
	
	float currentAnimTime_{ 0.0f };//���A�j���[�V�����Đ��ʒu
	float previousAnimTime_{ 0.0f };//�O�A�j���[�V�����Đ��ʒu

	float blendRate_{ 0.0f };//�u�����h�䗦
	float animSpeed_{ 0.0f };//�A�j���[�V�����Đ��{��

	float maxAnimTime_{ 0.0f };//�A�j���[�V�����ő厞��

	bool isLoop_{ true };//���[�v���邩
	bool prevIsLoop_{ true };//�O�A�j���[�V���������[�v���邩

	bool isEnd_{ false };//�I�������
private:
	const float RATE_TIME = 0.1f;// �u�����h���[�g�^�C��

};