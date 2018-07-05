#include "AnimationOutSide.h"

 AnimationOutSide::AnimationOutSide(int model) :model_(-1) {
	model_ = MV1DuplicateModel(model);

}

 AnimationOutSide::~AnimationOutSide() {
	// �O�A�j���[�V�������f�^�b�`
	MV1DetachAnim(model_, currentAnim_);
	MV1DetachAnim(model_, previousAnim_);
	MV1DeleteModel(model_);
}

//frameTime=�t���[���ύX����

 void AnimationOutSide::update(float frameTime) {


	// �O�A�j���[�V�������f�^�b�`
	MV1DetachAnim(model_, currentAnim_);
	MV1DetachAnim(model_, previousAnim_);

	// ���A�j���[�V�������A�^�b�`
	currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
	currentAnimTime_ += frameTime*animSpeed_;
	if (currentAnimTime_ >= maxAnimTime_)
	{
		isEnd_ = true;
		if (isLoop_) currentAnimTime_ = fmodf(currentAnimTime_, maxAnimTime_);
		else currentAnimTime_ = maxAnimTime_;
	}

	// �O�A�j���[�V�������A�^�b�`
	previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

	//�O�A�j���[�V���������[�v�Ή���������
	if (prevIsLoop_) {
		// �O�A�j���[�V�����X�V
		float prevMaxAnimTime = MV1GetAttachAnimTotalTime(model_, previousAnim_);
		//previousAnimTime_ += frameTime*animSpeed_;
		//previousAnimTime_ = fmodf(previousAnimTime_, prevMaxAnimTime);
		previousAnimTime_ = prevMaxAnimTime;
	}
	// �u�����h���̍X�V
	blendRate_ += RATE_TIME;
	blendRate_ = max(0.0f, min(blendRate_, 1.0f));

	// �A�j���[�V�����̃u�����h
	MV1SetAttachAnimBlendRate(model_, previousAnim_, 1.0f - blendRate_);
	MV1SetAttachAnimBlendRate(model_, currentAnim_, blendRate_);
	// �`��
	MV1SetAttachAnimTime(model_, previousAnim_, previousAnimTime_);
	MV1SetAttachAnimTime(model_, currentAnim_, currentAnimTime_);

}

 void AnimationOutSide::Draw(const Matrix & rotation) const
{

	Model::GetInstance().Draw(model_, rotation);
}

 void AnimationOutSide::changeAnimation(int key, bool isLoop, float animSpeed, float blendRate, float animTime) {
	//�A�j���[�V�������O�ƈꏏ�Ȃ�ύX���Ȃ�
	if (currentAnimKey_ == key)return;
	
	// �O�A�j���[�V�������f�^�b�`
	MV1DetachAnim(model_, currentAnim_);
	MV1DetachAnim(model_, previousAnim_);

	//�A�j���[�V�����L�[�ԍ����Z�b�g
	previousAnimKey_ = currentAnimKey_;
	currentAnimKey_ = key;

	//�A�j���[�V�������Z�b�g
	currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
	previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

	//�Đ��ʒu��ݒ�
	previousAnimTime_ = currentAnimTime_;
	currentAnimTime_ = animTime;

	//�A�j���[�V�����ő厞�Ԃ̍X�V
	maxAnimTime_ = MV1GetAttachAnimTotalTime(model_, currentAnim_);

	prevIsLoop_ = isLoop_;
	isLoop_ = isLoop;
	isEnd_ = false;
	blendRate_ = 1.0f - blendRate;//�u�����h�䗦���O�A�j���[�V�������u�����h����
	animSpeed_ = animSpeed;
	// �A�j���[�V�����̃u�����h
	MV1SetAttachAnimBlendRate(model_, previousAnim_, 1.0f - blendRate_);
	MV1SetAttachAnimBlendRate(model_, currentAnim_, blendRate_);
	// �`��
	MV1SetAttachAnimTime(model_, previousAnim_, previousAnimTime_);
	MV1SetAttachAnimTime(model_, currentAnim_, currentAnimTime_);
}

 bool AnimationOutSide::isEnd() const { return isEnd_; }

 int AnimationOutSide::getModelHandle() const {
	return model_;

}

//�A�j���[�V�����Đ����Ԃ��擾����

 float AnimationOutSide::getGetCurrentAnimTime() const {
	return currentAnimTime_;
}
