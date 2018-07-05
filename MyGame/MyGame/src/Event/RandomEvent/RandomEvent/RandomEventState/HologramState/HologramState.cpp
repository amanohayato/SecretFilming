#include "HologramState.h"
#include"../../../../../Sound/Sound.h"

HologramState::HologramState(IWorld & world) {
	world_ = &world;
}

void HologramState::Initialize()
{
	isEnd_ = false;
	count_ = 0.0f;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	//イベント中
	enemyBase_.lock()->set_is_event(true);
	// アニメーション再生
	enemyBase_.lock()->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Kaiwa), false);
	_scoreUpFunc = [&] {
		//状態がStopになったら帽子を落としてスコアを設定します
		if (enemyBase_.lock()->get_state() == EnemyBase::EnemyState::Stop) {
			enemyBase_.lock()->setBaseScore(20);
			return true;
		}
		return false;
	};

	anim_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_GRAY_HOLO));
	anim_.ChangeAnim(0, 0.0f, 1.0f, true, 1.0f, true);
}

void HologramState::Update()
{
	//スコア設定関数を呼び出し
	if (_scoreUpFunc()) {
		_scoreUpFunc = [] {return false; };
	}
	auto blue = 0.4f*MathHelper::Abs((float)std::sin(count_));
	count_ += 0.1f;

	if (count_ >= 12.0f && count_ <= 34.0f) {
		// 黄色く発光
		MV1SetMaterialEmiColor(enemyBase_.lock()->get_animation().getModelHandle(), 0, GetColorF(0.6f, 0.6f, blue, 1.0f));
	}
	else {
		MV1SetMaterialEmiColor(enemyBase_.lock()->get_animation().getModelHandle(), 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
	}
	if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() >= 47.0f) {
		anim_.Update(0.5f);
	}

	// ポケットをあさるSE
	if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() == 20.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::HOLOGRAM_ALEN_START, (VECTOR*)&enemyBase_.lock()->getPosition());
	}
	// ホログラムを出すSE
	else if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() == 60.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::HOLOGRAM_ALEN_TALK, (VECTOR*)&enemyBase_.lock()->getPosition());
	}
	// ホログラムと会話をする宇宙人のSE
	else if (enemyBase_.lock()->get_animation().getGetCurrentAnimTime() == 70.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::NEKO_GRAY_VOICE_SE, (VECTOR*)&enemyBase_.lock()->getPosition());
	}

	// スコア加算のチャンス
	//アニメーション終わったかどうか 
	if (enemyBase_.lock()->get_animation().isEnd()) {
		enemyBase_.lock()->setBaseScore(0);
		isEnd_ = true;
	}
}

void HologramState::Draw() const
{
	if (count_ >= 12.0f&&count_ <= 34.0f&&std::rand() % 8 >= 1) {
		auto FrameIndex = MV1SearchFrame(enemyBase_.lock()->get_animation().getModelHandle(), "R_MIDDLE1");
		auto FrameMatrix = DXConverter::GetInstance().ToMatrix(MV1GetFrameLocalWorldMatrix(enemyBase_.lock()->get_animation().getModelHandle(), FrameIndex));

		anim_.Draw(Matrix(enemyBase_.lock()->getRotation()).Translation(FrameMatrix.Translation()));

	}
}

bool HologramState::IsEnd() const
{
	return isEnd_;
}

void HologramState::End()
{
}

RandomEvent HologramState::Next() const
{
	return RandomEvent::LookAround_State;
}
