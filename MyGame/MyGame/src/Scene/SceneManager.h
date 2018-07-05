#pragma once
#include<map>
#include<memory>
#include"../ID/EnumIDs.h"
class Scene;

class TransitionsAnimation;

//シーンの管理を行う、Game及びその派生クラスで利用する
class SceneManager {
public:
	SceneManager();
	void start();
	void update(float deltaTime);
	void draw();
	//シーンが終了しているかを確認し、必要であれば次のシーンに遷移する
	void checkIsEnd();
	//次のシーンへ遷移する
	void next(TransitionsAnimeType transitionsAnimation);

	bool isGameEnd() const { return isGameEnd_; }

private:

	void changeNextScene();

private:

	// シーン遷移アニメーションが再生されているかのフラグ
	bool isTransitionsAnimation_{ false };

	//シーン一覧
	std::map<SceneType, std::shared_ptr<Scene>> scenes_;
	//現在のシーン
	SceneType currentScene_;

	std::map<TransitionsAnimeType, std::shared_ptr<TransitionsAnimation>> transitionsAnimations_;
	TransitionsAnimeType currentAnime_;

	bool isGameEnd_{ false };
};