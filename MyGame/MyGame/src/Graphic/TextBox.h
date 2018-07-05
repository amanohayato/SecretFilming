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

	// �`��
	
	void Draw(const Vector2& position, FONT_ID id = FONT_ID::FONT_TEXT,const Vector2& size = Vector2{ 1100.0f,150.0f }, const Vector2& padding = Vector2{20.0f,20.0f}, unsigned int color = GetColor(255, 255, 255)) const;
	void End();

	// ******************************
	// �ύX�F��ΐ��O
	// �����̓e�L�X�g�{�b�N�X���A�j���[�V���������\�����邩�̃t���O
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
	// �ύX�F��ΐ��O
	// ���͂̕\�����I��������̃t���O
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
	const int textLine{ 3 };//�s��
	const int lineMax_{ 17 };//�s�ő啶����
	std::vector<std::string> textList_{};
	int currentText_{ 0 };//���ݎQ�ƃe�L�X�g�t�@�C����
	int textCount_{ 0 };//���ݕ\��������
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