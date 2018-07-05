#include "BgmChange.h"
#include"../../Sound/Sound.h"
#include"../../Input/InputChecker.h"
#include "../../Scene/Manager/GameDataManager.h"

BgmChange::BgmChange(IWorld * world)
{

}

void BgmChange::initialize()
{
	Sound::GetInstance().PlayBGM(BGM_ID::SOUND_GETAWAY, DX_PLAYTYPE_LOOP);//ゲームBGMと同時に逃走用BGMを流す
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, (float)flightbgmvol_);//ボリュームを0にする
}

void BgmChange::update(float deltaTime)
{
	enemyescape_ = GameDataManager::getInstance().getEnemyEscape();//エネミーの逃走状態を取得する
	//逃走状態ならBGMを切り替える
	if (enemyescape_ == true)
	{
		gamebgmvol_ = 0.0;
		flightbgmvol_ = 1.0;
		Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, (float)gamebgmvol_);
		Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, (float)flightbgmvol_);
		bgmsmallflag_ = true;//一回だけ処理を行うためにboolを使用
	}
	//逃走状態を終わったとき逃走用BGMを段々小さくしてゲーム用BGMを段々大きくする
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
	//逃走用BGMをだんだん小さくしていく処理
	if (gamebgmvol_ > 1)
		gamebgmvol_ = 1.0f;
	else if(gamebgmvol_ != 1.0f)
		gamebgmvol_ += deltaTime / transbgmtime_;
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GAME, gamebgmvol_);
	Sound::GetInstance().SetBGMVolume(BGM_ID::SOUND_GETAWAY, flightbgmvol_ - gamebgmvol_);

	//ゲームBGMをだんだん小さくしていく処理 もし使うなら
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
