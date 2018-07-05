#pragma once
#include "../Scene.h"
#include "../SubScene/Result/ScoreSheet/ScoreSheet.h"
#include "../SubScene/Result/DisplayPhoto/DisplayPhoto.h"
#include "../SubScene/Menu/DecisionMenu/DecisionMenu.h"
#include <map>


class ResultScene : public Scene
{
public:
	ResultScene();

	virtual void start()override;
	virtual void update(float deltaTime)override;
	virtual void draw()const override;
	virtual void end() override;

private:

	// ゲームをクリアしたかどうかのフラグ
	bool isClear_{ true };

	// メニューを表示するかのフラグ
	bool displayMenu_{ false };

	// スタンプのアニメーションが終了したかのフラグ（仮）
	bool isStamp_{ false };

	// 写真の表示、アニメーションクラス
	std::shared_ptr<DisplayPhoto> displayPhoto_;

	// スコアシートの表示クラス
	std::shared_ptr<ScoreSheet> scoreSheet_;

	// 決定メニュー表示クラス
	std::shared_ptr<DecisionMenu> decisionMenu_;

	//点滅カウント
	int sinCount_{ 0 };
};
