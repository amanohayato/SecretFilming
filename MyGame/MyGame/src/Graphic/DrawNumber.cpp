#include "DrawNumber.h"

void DrawNumber::drawNumber(int number, Vector2 position, bool drawPercent)
{
	if (drawPercent)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_NUMBER_UI, position + Vector2(50.f, 0.f), 10);
	}

	int digits = 0;
	do 
	{
		int temp = number % 10;

		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_NUMBER_UI, position - Vector2((float)digits * 50.f, 0.f), temp);

		number = number / 10;

		digits++;
	} while (number != 0);
}

void DrawNumber::drawNumber(int number, Vector2 position, const Vector2& origin, const Vector2& scale, bool drawPercent)
{
	if (drawPercent)
	{
		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_NUMBER_UI, position + Vector2(50.f, 0.f), 10, origin, scale);
	}

	int digits = 0;
	do
	{
		int temp = number % 10;

		Sprite::GetInstance().SplitDraw(SPRITE_ID::SPRITE_NUMBER_UI, position - Vector2((float)digits * 50.f, 0.f), temp, origin, scale);

		number = number / 10;

		digits++;
	} while (number != 0);
}

