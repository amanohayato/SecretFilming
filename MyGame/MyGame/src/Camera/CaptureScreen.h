#pragma once
#include"../Math/Vector2.h"

#include<vector>
#include<string>
#include<utility>

class CaptureScreen {
	CaptureScreen();

public:
	static CaptureScreen& getInstance() {
		static CaptureScreen cap;
		return cap;
	}
	void initialize();
	//画面状態をメモリに保存
	void capture(int score=0);
	//最新画面情報を画像ファイルとして保存
	void save();
	//指定画面情報を画像ファイルとして保存
	void save(unsigned int target);
	void clear();

	int getScore() const;

	int getSize()const;

	//最新画面情報の描画
	void draw(const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)const;
	//指定画面情報の描画
	void draw(unsigned int target, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)const;
	//最新画像情報の書き込み
	void mGraph()const;
	//指定画像情報の書き込み
	void mGraph(unsigned int target)const;
	//書き込みなし描画
	void drawFarst(const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)const;

	void sortVectorToScore();

	void setResultDrawGraphHandle(int range);

	void drawResultPhoto(unsigned int target, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false) const;

private:
	std::string getFileList();

	//画像をメモリに保存する際、上限に達しているかを確認する
	void ssCollectionClean();

	int drawGraphHandle_;//描画用のメモリ確保
	std::vector<std::pair<int,int>> captureScreenCollection_{};//画像データリスト(ハンドル,スコア)
	
	std::vector<int> resultDrawGraphHandle_{};// リザルト用の描画用のメモリ確保

};