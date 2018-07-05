#include "SceneManager.h"
#include"Scenes.h"
#include "TransitionsAnimation/TransitionsAnimations.h"

//ローディングシーンから開始
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_LOADING) {
	//利用するシーンを作成し、シーンリストに追加する
	scenes_[SceneType::SCENE_LOADING] = std::make_shared<LoadingScene>();
	scenes_[SceneType::SCENE_ENTRANCE] = std::make_shared<EntranceScene>();
	scenes_[SceneType::SCENE_DEMOMOVIE] = std::make_shared<DemoMovieScene>();
	scenes_[SceneType::SCENE_TUTORIAL] = std::make_shared<TutorialScene>();
	scenes_[SceneType::SCENE_GAMEPLAY] = std::make_shared<GamePlayScene>();
	scenes_[SceneType::SCENE_RESULT] = std::make_shared<ResultScene>();

	transitionsAnimations_[TransitionsAnimeType::FadeAnimation] = std::make_shared<FadeAnimation>(1.0f);
}

void SceneManager::start() {
	
	SetMouseDispFlag(false);

	scenes_[currentScene_]->start();

	isTransitionsAnimation_ = false;
}

void SceneManager::update(float deltaTime) {

	if (isTransitionsAnimation_)
	{
		transitionsAnimations_[currentAnime_]->update(deltaTime);

		if (transitionsAnimations_[currentAnime_]->isChangeScene()) changeNextScene();

		if (transitionsAnimations_[currentAnime_]->isEnd()) isTransitionsAnimation_ = false;
			
		if (!transitionsAnimations_[currentAnime_]->canUpdateScene()) return;
	}

	scenes_[currentScene_]->update(deltaTime);
	isGameEnd_ = scenes_[currentScene_]->isGameEnd();
}

void SceneManager::draw() {

	scenes_[currentScene_]->draw();
	scenes_[currentScene_]->lateDraw();

	if (isTransitionsAnimation_)
	{
		transitionsAnimations_[currentAnime_]->draw();
	}
}

//シーンが終了しているかを確認し、必要であれば次のシーンに遷移する

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next(scenes_.at(currentScene_)->transitionsAnimeType());

}

//次のシーンへ遷移する

void SceneManager::next(TransitionsAnimeType transitionsAnimation) {

	if (transitionsAnimation == TransitionsAnimeType::None)
	{
		//シーンを終了して
		scenes_[currentScene_]->end();
		SceneType nextScene = scenes_[currentScene_]->nextScene();
		currentScene_ = nextScene;
		//次のシーンを開始する
		scenes_[currentScene_]->baseInit();
		scenes_[currentScene_]->start();

		return;
	}

	if (!isTransitionsAnimation_)
	{
		currentAnime_ = transitionsAnimation;
		transitionsAnimations_[currentAnime_]->start();
		isTransitionsAnimation_ = true;
	}
}

void SceneManager::changeNextScene()
{
	//シーンを終了して
	scenes_[currentScene_]->end();
	SceneType nextScene = scenes_[currentScene_]->nextScene();
	currentScene_ = nextScene;
	//次のシーンを開始する
	scenes_[currentScene_]->baseInit();
	scenes_[currentScene_]->start();
}
