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

	// �Q�[�����N���A�������ǂ����̃t���O
	bool isClear_{ true };

	// ���j���[��\�����邩�̃t���O
	bool displayMenu_{ false };

	// �X�^���v�̃A�j���[�V�������I���������̃t���O�i���j
	bool isStamp_{ false };

	// �ʐ^�̕\���A�A�j���[�V�����N���X
	std::shared_ptr<DisplayPhoto> displayPhoto_;

	// �X�R�A�V�[�g�̕\���N���X
	std::shared_ptr<ScoreSheet> scoreSheet_;

	// ���胁�j���[�\���N���X
	std::shared_ptr<DecisionMenu> decisionMenu_;

	//�_�ŃJ�E���g
	int sinCount_{ 0 };
};
