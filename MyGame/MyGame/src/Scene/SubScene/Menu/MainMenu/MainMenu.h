#pragma once
#include "../Menu.h"

class MainMenu :public Menu
{
public:
	MainMenu();

	virtual void start()override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

protected:

	virtual void decisionCheck() override;

private:

	int sinCount_{ 0 };

	/*enum MenuItemType
	{
		StartGame,
		Option,
		Exit,

		Count,
	};*/
};
