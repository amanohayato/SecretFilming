#include "LookCameraIcon.h"

LookCameraIcon::LookCameraIcon(std::shared_ptr<Player> player, std::shared_ptr<TutorialEnemy> enemy)
{
	player_ = player;
	enemy_ = enemy;
}

void LookCameraIcon::onStart()
{
	finalChangeAlpa_ = false;

	blindAlpa_ = 0.0f;

	afterBlindAlpa_ = 1.0f;

	blindAlpaChangeRate_ = 0.05f;

	isWaitInput_ = false;
	
	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, false);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, false);
	
	enemy_->get_animation().changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)EnemyBase::EnemyAnimation::Kaiwa), true);
	enemy_->setBaseScore(20);

	count_ = 0.0f;

	anim_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_GRAY_HOLO));
	anim_.ChangeAnim(0, 1.0f, 1.0f, true, 1.0f, true);
}

void LookCameraIcon::onUpdate(float deltaTime)
{
	count_ = enemy_->get_animation().getGetCurrentAnimTime();

	auto blue = 0.4f*MathHelper::Abs((float)std::sin(count_));
	//count_ += 0.1f;

	if (count_ >= 53.0f && count_ <= 165.0f) {
		// 黄色く発光
		MV1SetMaterialEmiColor(enemy_->get_animation().getModelHandle(), 0, GetColorF(0.6f, 0.6f, blue, 1.0f));
	}
	else {
		MV1SetMaterialEmiColor(enemy_->get_animation().getModelHandle(), 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));
	}

	if (enemy_->get_animation().getGetCurrentAnimTime() >= 47.0f) {
		anim_.Update(0.5f);
	}
	else
	{
		anim_.ChangeAnim(0, 1.0f, 1.0f, true, 1.0f, true);
	}

	// ポケットをあさるSE
	if (enemy_->get_animation().getGetCurrentAnimTime() == 20.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::HOLOGRAM_ALEN_START, (VECTOR*)&enemy_->getPosition());
	}
	// ホログラムを出すSE
	else if (enemy_->get_animation().getGetCurrentAnimTime() == 60.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::HOLOGRAM_ALEN_TALK, (VECTOR*)&enemy_->getPosition());
	}
	// ホログラムと会話をする宇宙人のSE
	else if (enemy_->get_animation().getGetCurrentAnimTime() == 70.0f) {
		Sound::GetInstance().Play3DSE(SE_ID::NEKO_GRAY_VOICE_SE, (VECTOR*)&enemy_->getPosition());
	}

	blindAlpa_ += blindAlpaChangeRate_;

	bool isEndChangeAlpa = false;

	// 変化幅がプラスならば
	if (blindAlpaChangeRate_ > 0)
	{
		if (blindAlpa_ < afterBlindAlpa_) return;
		blindAlpa_ = afterBlindAlpa_;
	}
	else
	{
		if (blindAlpa_ > afterBlindAlpa_) return;
		blindAlpa_ = afterBlindAlpa_;
	}

	displayA_Push_ = false;
	displayLT_Push_ = false;

	if (!textBox_.isEndPlay()) return;

	if (finalChangeAlpa_) isCommandEnd_ = true;

	if (isWaitInput_)
	{
		displayLT_Push_ = true;

		if (player_->getStateType() == Player_State_ID::SetUp)
		{
			finalChangeAlpa_ = true;

			afterBlindAlpa_ = 0.0f;

			blindAlpaChangeRate_ = -0.05f;
		}
	}
	else
	{
		if (textBox_.Get_Current_Text() < 2)
		{
			displayA_Push_ = true;

			if (InputChecker::GetInstance().KeyStateDown(Operation_Type::DECISION_BUTTON))
			{
				// セレクトSEを再生
				Sound::GetInstance().PlaySE_IsNotPlay(SE_ID::DECISION_SE);

				textBox_.Increment_Text();
			}
		}
		else
		{
			textBox_.Increment_Text();

			InputChecker::GetInstance().ChangeActive(Operation_Type::HOLD_CAMERA_BUTTON, true);
			isWaitInput_ = true;
		}
	}
}

void LookCameraIcon::onDraw() const
{
	if (count_ >= 53.0f&&count_ <= 165.0f && std::rand() % 8 >= 1) {
		auto FrameIndex = MV1SearchFrame(enemy_->get_animation().getModelHandle(), "R_MIDDLE1");
		auto FrameMatrix = DXConverter::GetInstance().ToMatrix(MV1GetFrameLocalWorldMatrix(enemy_->get_animation().getModelHandle(), FrameIndex));

		anim_.Draw(Matrix(enemy_->getRotation()).Translation(FrameMatrix.Translation()));
	}

	Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_LOOK_CAMERA_ICON, Vector2::Zero, blindAlpa_);
}

void LookCameraIcon::onEnd()
{
	MV1SetMaterialEmiColor(enemy_->get_animation().getModelHandle(), 0, GetColorF(0.0f, 0.0f, 0.0f, 0.0f));

	InputChecker::GetInstance().ChangeActive(Operation_Type::PLAYER_MOVE_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::CHANGE_VIEW_POINT_STICK, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::TAKE_SHUTTER_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::SHOW_MAP_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::DASH_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::HIDE_BUTTON, true);
	InputChecker::GetInstance().ChangeActive(Operation_Type::RETURN_VIEW_POINT_BUTTON, true);
}

void LookCameraIcon::setText()
{
	textBox_.add("TutorialText/04_LookCameraIcon/LookCameraIcon_1.txt");
	textBox_.add("TutorialText/04_LookCameraIcon/LookCameraIcon_2.txt");
	textBox_.add("TutorialText/04_LookCameraIcon/LookCameraIcon_3.txt");
}
