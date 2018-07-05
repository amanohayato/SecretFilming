#pragma once
#include"../Math/Vector2.h"
#include"../ID/EnumIDs.h"

#include<string>
#include <iostream>
#include<fstream>
#include<array>
#include<vector>
#include<functional>


class TextBox {
public:
	TextBox(int priority=0);
	void Init();
	void add(const std::string& filename);
	void Reset();
	void Update();

	// 描画
	
	void Draw(const Vector2& position, FONT_ID id = FONT_ID::FONT_TEXT,const Vector2& size = Vector2{ 1100.0f,150.0f }, const Vector2& padding = Vector2{20.0f,20.0f}, unsigned int color = GetColor(255, 255, 255)) const;
	void End();

	// ******************************
	// 変更：大槻嵩弘
	// 引数はテキストボックスをアニメーションさせつつ表示するかのフラグ
	void Display_Text(bool isAnimation = true);
	// ******************************

	void Hidden_Text();
	void Start_Text();
	void Stop_Text();
	bool Increment_Text();
	void Decrement_Text();
	void Set_Current_Text(int currentText);
	int Get_Current_Text();
	bool isEnd()const { return isEnd_; }

	// ******************************
	// 変更：大槻嵩弘
	// 文章の表示が終わったかのフラグ
	bool isEndPlay();
	// ******************************

	void SetIsDraw(bool flag);

	int getAlpha()const { return alpha_; }
private:
	void in();
	void out();

	void play();
	void stop();
private:
	const int textLine{ 3 };//行数
	const int lineMax_{ 17 };//行最大文字数
	std::vector<std::string> textList_{};
	int currentText_{ 0 };//現在参照テキストファイル数
	int textCount_{ 0 };//現在表示文字数
	int timeCount_{ 0 };

	bool isEnd_;
	bool display_;
	bool isPlay_;
	int alpha_;
	int isDrawAlpha;

	bool isDraw;
	std::function<void()> ctrlFunc_{};

	int _priority{ 0 };
};