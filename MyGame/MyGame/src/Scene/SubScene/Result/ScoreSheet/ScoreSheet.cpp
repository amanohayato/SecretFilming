#include "ScoreSheet.h"
#include "ScoreSheetContantPos.h"
#include "../../../../ID/EnumIDs.h"
#include "../../../Manager/GameDataManager.h"
#include "../../../../Camera/CaptureScreen.h"
#include "../../../../Graphic/Sprite.h"
#include "../../../../Graphic/DrawNumber.h"
#include "../../../../Sound/Sound.h"

ScoreSheet::ScoreSheet()
{
	sheetAnim_ = std::make_shared<ScalingSprite>(Vector2(1.01f, 1.01f), Vector2::One, 0.02f);
}

void ScoreSheet::start()
{
	baseInit();

	// �m��x�̒l���擾
	determination_ = (float)GameDataManager::getInstance().getScore();

	// �Q�[�����N���A�������̃t���O
	isClear_ = (determination_ >= 100);

	// �B�e�����ʐ^�̖������擾
	photoCount_ = GameDataManager::getInstance().getPhotoCount();

	// ������ꂽ�񐔂��擾
	escapeCount_ = GameDataManager::getInstance().getEscapeCount();

	// �{�[�i�X�v�Z�֐����Ă�
	bonusCalculation();

	// ���v�X�R�A�̎Z�o
	totalScore_ = determination_ + photoCountBonus_ + escapeCountBonus_;

	// ���v�X�R�A�ɂ���ă����N�̒l���擾
	if (totalScore_ > 120)		rank_ = Rank::S;
	else if (totalScore_ > 100)	rank_ = Rank::A;
	else if (totalScore_ > 80)	rank_ = Rank::B;
	else if (totalScore_ > 51)	rank_ = Rank::C;
	else						rank_ = Rank::D;

	displayRank_ = false;

	isAnimStart_ = false;

	isAnimReturn_ = false;
}

void ScoreSheet::update(float deltaTime)
{
	if (isAnimStart_)
	{
		sheetAnim_->update(deltaTime);

		if (sheetAnim_->isAnimationEnd())
		{
			if (isAnimReturn_)
			{
				/*displayRank_ = false;

				isAnimStart_ = false;

				isAnimReturn_ = false;

				stampStart();*/
			}
			else
			{
				Sound::GetInstance().PlaySE(SE_ID::DECISION_SE);

				sheetAnim_ = std::make_shared<ScalingSprite>(Vector2::One, Vector2(1.01f, 1.01f), 0.02f);

				isAnimReturn_ = true;
			}
		}
	}
}

void ScoreSheet::draw() const
{
	Vector2 centerPos;

	centerPos = (Vector2)Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_DOCUMENTS) / 2;

	// �X�R�A�V�[�g�̎��̕\��
	Sprite::GetInstance().Draw
	(
		SPRITE_ID::SPRITE_DOCUMENTS,
		DOCUMENTS_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale()
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSize(SPRITE_ID::Awareness) / 2) - HEADLINE_SPRITE_POS;

	SPRITE_ID headlineSprite = SPRITE_ID::SPRITE_GAME_OVER_UI;
	if (isClear_) headlineSprite = SPRITE_ID::SPRITE_GAME_CLEAR_UI;

	Sprite::GetInstance().Draw
	(
		headlineSprite,
		HEADLINE_SPRITE_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale()
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSize(SPRITE_ID::Awareness) / 2) - AWARENESS_POS;

	// �m��x�̕`��
	Sprite::GetInstance().Draw
	(
		SPRITE_ID::Awareness, 
		AWARENESS_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale()
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSplitPieceSize(SPRITE_ID::SPRITE_NUMBER_UI) / 2) - AWARENESS_NUMBER_POS;

	float showDetermination = determination_;

	if (showDetermination > 100.0f) showDetermination = 100.0f;

	DrawNumber::drawNumber
	(
		(int)showDetermination,
		AWARENESS_NUMBER_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale(),
		true
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSize(SPRITE_ID::Photo_Count) / 2) - PHOTO_COUNT_POS;

	// �B�e�񐔂̕`��
	Sprite::GetInstance().Draw
	(
		SPRITE_ID::Photo_Count,
		PHOTO_COUNT_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale()
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSplitPieceSize(SPRITE_ID::SPRITE_NUMBER_UI) / 2) - PHOTO_COUNT_NUMBER_POS;

	DrawNumber::drawNumber
	(
		photoCount_,
		PHOTO_COUNT_NUMBER_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale(),
		false
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSize(SPRITE_ID::Escape_Count) / 2) - ESCAPE_COUNT_POS;

	// �����񐔂̕`��
	Sprite::GetInstance().Draw
	(
		SPRITE_ID::Escape_Count,
		ESCAPE_COUNT_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale()
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSplitPieceSize(SPRITE_ID::SPRITE_NUMBER_UI) / 2) - ESCAPE_COUNT_NUMBER_POS;

	DrawNumber::drawNumber
	(
		escapeCount_,
		ESCAPE_COUNT_NUMBER_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale(),
		false
	);

	centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_EVALUATION_UI) / 2) - EVALUATION_POS;

	// �]���̕\��
	Sprite::GetInstance().Draw
	(
		SPRITE_ID::SPRITE_EVALUATION_UI, 
		EVALUATION_POS + centerPos,
		centerPos,
		sheetAnim_->getCurScale()
	);

	if (displayRank_)
	{
		centerPos = DOCUMENTS_CENTER + ((Vector2)Sprite::GetInstance().GetSplitPieceSize(SPRITE_ID::SPRITE_EVALUATION_WORD_UI) / 2) - EVALUATION_WORD_POS;

		Sprite::GetInstance().SplitDraw
		(
			SPRITE_ID::SPRITE_EVALUATION_WORD_UI,
			EVALUATION_WORD_POS + centerPos,
			rank_,
			centerPos,
			sheetAnim_->getCurScale()
		);
	}
}

void ScoreSheet::end()
{
}

void ScoreSheet::bonusCalculation()
{
	// �B�e�����ʐ^�̖����ɂ��{�[�i�X���擾
	if (photoCount_ <= 30)		photoCountBonus_ = 5.0f;
	else if (photoCount_ <= 35) photoCountBonus_ = 4.0f;
	else if (photoCount_ <= 40) photoCountBonus_ = 3.0f;
	else if (photoCount_ <= 45) photoCountBonus_ = 2.0f;
	else if (photoCount_ <= 50) photoCountBonus_ = 1.0f;
	else						photoCountBonus_ = 0.0f;

	// ������ꂽ�񐔂ɂ��{�[�i�X���擾
	if (escapeCount_ == 0)			escapeCountBonus_ = 15.0f;
	else if (escapeCount_ == 1)		escapeCountBonus_ = 10.0f;
	else if (escapeCount_ == 2)		escapeCountBonus_ = 5.0f;
	else							escapeCountBonus_ = 0.0f;
}

void ScoreSheet::stampStart()
{
	displayRank_ = true;

	isAnimStart_ = true;
}

void ScoreSheet::baseInit()
{
	displayRank_ = false;
	determination_ = 0.0f;
	photoCount_ = 0;
	photoCountBonus_ = 0.0f;
	escapeCount_ = 0;
	escapeCountBonus_ = 0.0f;
	totalScore_ = 0.0f;

	SubScene::baseInit();
}
