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

	int sinCount_{ 0 };//点滅カウント

	int cameraSens_ { 5 };//カメラ感度の値

	int bgmVolume_ { 5 };//BGMの音量の値

	int seVolume_{ 5 };//SEの音量の値

	
};