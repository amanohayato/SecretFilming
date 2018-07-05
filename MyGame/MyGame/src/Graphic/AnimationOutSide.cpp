#include "AnimationOutSide.h"

 AnimationOutSide::AnimationOutSide(int model) :model_(-1) {
	model_ = MV1DuplicateModel(model);

}

 AnimationOutSide::~AnimationOutSide() {
	// 前アニメーションをデタッチ
	MV1DetachAnim(model_, currentAnim_);
	MV1DetachAnim(model_, previousAnim_);
	MV1DeleteModel(model_);
}

//frameTime=フレーム変更割合

 void AnimationOutSide::update(float frameTime) {


	// 前アニメーションをデタッチ
	MV1DetachAnim(model_, currentAnim_);
	MV1DetachAnim(model_, previousAnim_);

	// 今アニメーションをアタッチ
	currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
	currentAnimTime_ += frameTime*animSpeed_;
	if (currentAnimTime_ >= maxAnimTime_)
	{
		isEnd_ = true;
		if (isLoop_) currentAnimTime_ = fmodf(currentAnimTime_, maxAnimTime_);
		else currentAnimTime_ = maxAnimTime_;
	}

	// 前アニメーションをアタッチ
	previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

	//前アニメーションがループ対応だったら
	if (prevIsLoop_) {
		// 前アニメーション更新
		float prevMaxAnimTime = MV1GetAttachAnimTotalTime(model_, previousAnim_);
		//previousAnimTime_ += frameTime*animSpeed_;
		//previousAnimTime_ = fmodf(previousAnimTime_, prevMaxAnimTime);
		previousAnimTime_ = prevMaxAnimTime;
	}
	// ブレンド率の更新
	blendRate_ += RATE_TIME;
	blendRate_ = max(0.0f, min(blendRate_, 1.0f));

	// アニメーションのブレンド
	MV1SetAttachAnimBlendRate(model_, previousAnim_, 1.0f - blendRate_);
	MV1SetAttachAnimBlendRate(model_, currentAnim_, blendRate_);
	// 描画
	MV1SetAttachAnimTime(model_, previousAnim_, previousAnimTime_);
	MV1SetAttachAnimTime(model_, currentAnim_, currentAnimTime_);

}

 void AnimationOutSide::Draw(const Matrix & rotation) const
{

	Model::GetInstance().Draw(model_, rotation);
}

 void AnimationOutSide::changeAnimation(int key, bool isLoop, float animSpeed, float blendRate, float animTime) {
	//アニメーションが前と一緒なら変更しない
	if (currentAnimKey_ == key)return;
	
	// 前アニメーションをデタッチ
	MV1DetachAnim(model_, currentAnim_);
	MV1DetachAnim(model_, previousAnim_);

	//アニメーションキー番号をセット
	previousAnimKey_ = currentAnimKey_;
	currentAnimKey_ = key;

	//アニメーションをセット
	currentAnim_ = MV1AttachAnim(model_, 0, currentAnimKey_);
	previousAnim_ = MV1AttachAnim(model_, 0, previousAnimKey_);

	//再生位置を設定
	previousAnimTime_ = currentAnimTime_;
	currentAnimTime_ = animTime;

	//アニメーション最大時間の更新
	maxAnimTime_ = MV1GetAttachAnimTotalTime(model_, currentAnim_);

	prevIsLoop_ = isLoop_;
	isLoop_ = isLoop;
	isEnd_ = false;
	blendRate_ = 1.0f - blendRate;//ブレンド比率分前アニメーションをブレンドする
	animSpeed_ = animSpeed;
	// アニメーションのブレンド
	MV1SetAttachAnimBlendRate(model_, previousAnim_, 1.0f - blendRate_);
	MV1SetAttachAnimBlendRate(model_, currentAnim_, blendRate_);
	// 描画
	MV1SetAttachAnimTime(model_, previousAnim_, previousAnimTime_);
	MV1SetAttachAnimTime(model_, currentAnim_, currentAnimTime_);
}

 bool AnimationOutSide::isEnd() const { return isEnd_; }

 int AnimationOutSide::getModelHandle() const {
	return model_;

}

//アニメーション再生時間を取得する

 float AnimationOutSide::getGetCurrentAnimTime() const {
	return currentAnimTime_;
}
