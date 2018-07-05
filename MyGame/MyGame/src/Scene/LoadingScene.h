#pragma once
#include"Scene.h"
#include<vector>

//リソース読み込み専用シーン
class LoadingScene :public Scene {
public:
	LoadingScene();

	void start()override;
	void update(float deltaTime) override;
	void draw()const override;
	void end()override;

private:
	//画像の読み込み
	void LoadSprite();
	//モデルの読み込み
	void LoadModel();
	//モデルの読み込み
	void LoadEffect();
	//文字フォントの読み込み
	void LoadFont();
	//BGMの読み込み
	void LoadBGM();
	//SEの読み込み
	void LoadSE();
	//シェーダーの読み込み
	void LoadShader();
	//その他ステージ等の読み込み
	void LoadEtcetera();

	void LoadSpriteAnim();
private:
	int _animCount{ 0 };

	std::vector<int> _loadAnimList;
};