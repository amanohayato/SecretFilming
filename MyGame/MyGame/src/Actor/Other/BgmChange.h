#pragma once
#include"../Actor.h"

class BgmChange : public Actor
{
public:

	BgmChange(IWorld * world);

	void initialize();

	void update(float deltaTime) override;

	void draw()const;

	//メッセージの受信
	//virtual void receiveMessage(EventMessage message, void* param) override;


private:
	static const int transbgmtime_ = 5;//BGMが遷移してから逃走BGMが完全に消えるまでの時間(秒)

	double flightbgmvol_ = 0.0;//逃走BGMボリューム(%)
	double gamebgmvol_ = 1.0;//ゲームBGMボリューム(%)
	bool enemyescape_ = false;//エネミーが逃走状態かどうか
	bool bgmsmallflag_ = false;//BGMを小さくするフラグ
};