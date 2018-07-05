#pragma once
#include "../Menu.h"

class Option : public Menu
{
public:
	Option(SubSceneType nextSubScene);

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void end() override;

protected:

	virtual void decisionCheck() override;

private:

	void changeParameter(int value);

private:

	/*enum MenuItemType
	{
		CameraSens,
		BgmVolume,
		SeVolume,
		BackToMenu,

		Count,
	};*/

	int sinCount_{ 0 };//�_�ŃJ�E���g

	int cameraSens_ { 5 };//�J�������x�̒l

	int bgmVolume_ { 5 };//BGM�̉��ʂ̒l

	int seVolume_{ 5 };//SE�̉��ʂ̒l

	
};