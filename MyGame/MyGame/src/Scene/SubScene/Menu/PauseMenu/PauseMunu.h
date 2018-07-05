#pragma once
#include "../Menu.h"

class PauseMunu : public Menu {
public:
	PauseMunu();

	virtual void start() override;
	virtual void update(float deltaTime) override;
	virtual void draw()const override;
	virtual void end() override;

protected:

	void decisionCheck();

private:

	int sinCount_{ 0 };

	/*enum MenuItemType
	{
		Return_Game,
		Option,
		Title,

		Count,
	};*/
};