#include "BgmChange.h"
#include"../../Sound/Sound.h"
#include"../../Input/InputChecker.h"
#include "../../Scene/Manager/GameDataManager.h"

BgmChange::BgmChange(IWorld * world)
{

}

void BgmChange::initialize()
{
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GETAWAY, DX_PLAYTYPE_LOOP);//�Q�[��BGM�Ɠ����ɓ����pBGM�𗬂�
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, (float)flightbgmvol_);//�{�����[����0�ɂ���
}

void BgmChange::update(float deltaTime)
{
	enemyescape_ = GameDataManager::getInstance().getEnemyEscape();//�G�l�~�[�̓�����Ԃ��擾����
	//������ԂȂ�BGM��؂�ւ���
	if (enemyescape_ == true)
	{
		gamebgmvol_ = 0.0;
		flightbgmvol_ = 1.0;
		Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, (float)gamebgmvol_);
		Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, (float)flightbgmvol_);
		bgmsmallflag_ = true;//��񂾂��������s�����߂�bool���g�p
	}
	//������Ԃ��I������Ƃ������pBGM��i�X���������ăQ�[���pBGM��i�X�傫������
	else if (bgmsmallflag_ == true)
	{
		if (gamebgmvol_ >= 1.0)
		{
			gamebgmvol_ = 1.0;
			bgmsmallflag_ = false;
		}
		else if (gamebgmvol_ != 1.0)
			gamebgmvol_ += (double)deltaTime / (double)transbgmtime_;
		Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, (float)gamebgmvol_);
		Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, (float)(flightbgmvol_ - gamebgmvol_));
	}

	/*
	//�����pBGM�����񂾂񏬂������Ă�������
	if (gamebgmvol_ > 1)
		gamebgmvol_ = 1.0f;
	else if(gamebgmvol_ != 1.0f)
		gamebgmvol_ += deltaTime / transbgmtime_;
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, gamebgmvol_);
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, flightbgmvol_ - gamebgmvol_);

	//�Q�[��BGM�����񂾂񏬂������Ă������� �����g���Ȃ�
	if (flightbgmvol_ > 1)
		flightbgmvol_ = 1.0f;
	else if(flightbgmvol_ != 1.0f)
		flightbgmvol_ += deltaTime / transbgmtime_;
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, flightbgmvol_);
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, gamebgmvol_ - flightbgmvol_);
	*/
}

void BgmChange::draw() const
{
	//DebugDraw::DebugDrawFormatString(600, 600, GetColor(255, 255, 255), "%f", flightbgmvol_);
}
