#pragma once
#include<DxLib.h>
#include"../Define.h"

class BloomEffect{
public:
	BloomEffect() {}
	~BloomEffect() {
		end();
	}
	void init() {
		int width = WINDOW_WIDTH / 8;
		int height = WINDOW_HEIGHT / 8;
		HighBrightScreen_ = MakeScreen(WINDOW_WIDTH, WINDOW_HEIGHT, FALSE);
		DownScaleScreen_ = MakeScreen(width, height, FALSE);
		GaussScreen_ = MakeScreen(width, height, FALSE);
		grHandle_ = MakeGraph(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	void end() {
		DeleteGraph(HighBrightScreen_);
		DeleteGraph(DownScaleScreen_);
		DeleteGraph(GaussScreen_);
		DeleteGraph(grHandle_);

	}
	void bloom() const{
		GetDrawScreenGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, grHandle_);
		// 描画結果から高輝度部分のみを抜き出した画像を得る
		GraphFilterBlt(grHandle_, HighBrightScreen_, DX_GRAPH_FILTER_BRIGHT_CLIP, DX_CMP_LESS, 230, TRUE, GetColor(0, 0, 0), 255);
		
		// 高輝度部分を８分の１に縮小した画像を得る
		GraphFilterBlt(HighBrightScreen_, DownScaleScreen_, DX_GRAPH_FILTER_DOWN_SCALE, 8);
		// ８分の１に縮小した画像をガウスフィルタでぼかす
		GraphFilterBlt(DownScaleScreen_, GaussScreen_, DX_GRAPH_FILTER_GAUSS, 16, 900);
		SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GaussScreen_, FALSE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
private:
	int HighBrightScreen_; 
	int DownScaleScreen_;
	int GaussScreen_;
	int grHandle_;
};