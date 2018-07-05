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

	//文字フォントの追加、filenameはファイルパス、fontnameはフォントに設定されている名前(フォントファイルを開いた際に表示されるフォント名)
	void AddFont(FONT_ID id,const std::string& filename,const std::string& fontname,int fontSize);

	int GetFontHandle(FONT_ID id)const;
	int GetFontSize(FONT_ID id)const;

	//フォントを利用した文字列描画
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
