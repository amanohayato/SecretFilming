#pragma once
#include"AnimLoader.h"
#include"../ID/EnumIDs.h"
#include"../Math/Matrix.h"
#include"../Graphic/Model.h"

class AnimationOutSide {
public:

	explicit AnimationOutSide(int model);
	~AnimationOutSide();

	//frameTime=フレーム変更割合
	void update(float frameTime);
	void Draw(const Matrix& rotation) const;

	void changeAnimation(int key, bool isLoop = true, float animSpeed = 1.0f, float blendRate = 1.0f, float animTime = 0.0f);

	bool isEnd()const;
	int getModelHandle() const;
	//アニメーション再生時間を取得する
	float getGetCurrentAnimTime()const;
private:
	int model_;//モデルハンドル
	
	int currentAnimKey_{ -1 };//現アニメーションキー
	int previousAnimKey_{ -1 };//前アニメーションキー

	int currentAnim_{ -1 };//現アニメーション
	int previousAnim_{ -1 };//前アニメーション
	
	float currentAnimTime_{ 0.0f };//現アニメーション再生位置
	float previousAnimTime_{ 0.0f };//前アニメーション再生位置

	float blendRate_{ 0.0f };//ブレンド比率
	float animSpeed_{ 0.0f };//アニメーション再生倍率

	float maxAnimTime_{ 0.0f };//アニメーション最大時間

	bool isLoop_{ true };//ループするか
	bool prevIsLoop_{ true };//前アニメーションがループするか

	bool isEnd_{ false };//終わったか
private:
	const float RATE_TIME = 0.1f;// ブレンドレートタイム

};