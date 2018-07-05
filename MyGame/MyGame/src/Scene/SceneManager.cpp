#include "SceneManager.h"
#include"Scenes.h"
#include "TransitionsAnimation/TransitionsAnimations.h"

//���[�f�B���O�V�[������J�n
SceneManager::SceneManager() :currentScene_(SceneType::SCENE_LOADING) {
	//���p����V�[�����쐬���A�V�[�����X�g�ɒǉ�����
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

//�V�[�����I�����Ă��邩���m�F���A�K�v�ł���Ύ��̃V�[���ɑJ�ڂ���

void SceneManager::checkIsEnd() {
	if (scenes_.at(currentScene_)->isEnd()) next(scenes_.at(currentScene_)->transitionsAnimeType());

}

//���̃V�[���֑J�ڂ���

void SceneManager::next(TransitionsAnimeType transitionsAnimation) {

	if (transitionsAnimation == TransitionsAnimeType::None)
	{
		//�V�[�����I������
		scenes_[currentScene_]->end();
		SceneType nextScene = scenes_[currentScene_]->nextScene();
		currentScene_ = nextScene;
		//���̃V�[�����J�n����
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
	//�V�[�����I������
	scenes_[currentScene_]->end();
	SceneType nextScene = scenes_[currentScene_]->nextScene();
	currentScene_ = nextScene;
	//���̃V�[�����J�n����
	scenes_[currentScene_]->baseInit();
	scenes_[currentScene_]->start();
}
