#pragma once

#include"DxLib.h"
#include"Sprite.h"
#include"../ID/EnumIDs.h"
#include<list>
#include<string>

class DrawNumber
{
public:
	static void drawNumber(int number, Vector2 position, bool drawPercent);

	static void drawNumber(int number, Vector2 position, const Vector2& origin, const Vector2& scale, bool drawPercent);
};