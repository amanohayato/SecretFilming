#pragma once
#include "../Menu.h"


class DecisionMenu :public Menu 
{
public:
	DecisionMenu(SceneType afterScene, SubSceneType beforeSubScene, SPRITE_ID mainLabel);

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void end()override;

protected:

	virtual void decisionCheck() override;

private:

	int sinCount_{ 0 };

	//// ƒƒjƒ…[‚Ìí—Ş
	//enum MenuItemType
	//{
	//	Yes,
	//	No,

	//	Count,
	//};

	SceneType afterScene_;

	SubSceneType beforeSubScene_;

	SPRITE_ID mainLabelType_;
};