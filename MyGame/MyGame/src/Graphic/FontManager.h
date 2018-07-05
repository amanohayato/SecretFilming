#pragma once
#include<DxLib.h>

#include<map>
#include"../ID/EnumIDs.h"
class FontManager{
private:
	FontManager() = default;
	~FontManager();
public:
	static FontManager &GetInstance() {
		static FontManager f;
		return f;
	}
	void Initialize();

	//�����t�H���g�̒ǉ��Afilename�̓t�@�C���p�X�Afontname�̓t�H���g�ɐݒ肳��Ă��閼�O(�t�H���g�t�@�C�����J�����ۂɕ\�������t�H���g��)
	void AddFont(FONT_ID id,const std::string& filename,const std::string& fontname,int fontSize);

	int GetFontHandle(FONT_ID id)const;
	int GetFontSize(FONT_ID id)const;

	//�t�H���g�𗘗p����������`��
	template<class ...T>
	void DrawTextApplyFont(int x,int y,unsigned int color,FONT_ID id,const std::string& text, T ...args);

	void End();
private:
	std::map<FONT_ID, int> fontids_;
	std::map<FONT_ID, int> fontSizes_;
};

template<class ...T>
void FontManager::DrawTextApplyFont(int x, int y, unsigned int color, FONT_ID id, const std::string & text, T ...args)
{
	DrawFormatStringToHandle(x, y, color, fontids_[id], text.c_str(), args...);

	
}