#include "DemoMovieScene.h"
#include"../Graphic/DebugDraw.h"
#include"../Define.h"
#include"../Input/InputChecker.h"

DemoMovieScene::DemoMovieScene()
{
}

void DemoMovieScene::start()
{
	// ���̃V�[���̏I���t���O��Off�ɂ���
	isEnd_ = false;

	// ���̃V�[�����g�G���g�����X�V�[���h�ɃZ�b�g����
	next_ = SceneType::SCENE_ENTRANCE;

	// �f�����[�r�[�̍Đ��J�n
	// �f�����[�r�[�̍Đ������̏��������Ə�w�̃N���X�Ŏ��K�v����

}

void DemoMovieScene::update(float deltaTime)
{
	// �_�ŃJ�E���g�̍X�V
	sinCount_ = (sinCount_ + 1) % 360;

	// A�{�^���������ꂽ��
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::DECISION_BUTTON))
	{
		// ���̃V�[���̏I��������On�ɂ���
		isEnd_ = true;
	}

	// �f�����[�r�[�̍Đ����I��������
	if (false)
	{
		// ���̃V�[���̏I��������On�ɂ���
		isEnd_ = true;
	}
}

void DemoMovieScene::draw() const
{
	// �f�����[�r�[�̕`��


	//  "�n�{�^���Ń��C�����j���[��" �̕`��
	//Sprite::GetInstance().Draw(SPRITE_ID:: , Vector2::Zero);

	// �������牺�͉��̕\��
	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100, GetColor(255, 255, 255), "���݁A�f���V�[���ł�");

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GetColor(255, 255, 255), "�f�����[�r�[���Đ���");

	DebugDraw::DebugDrawFormatString(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 100, GetColor(255, 255, 255), "�n�{�^���Ń^�C�g����");
}

void DemoMovieScene::end()
{
	// �f�����[�r�[���Đ�����Ă�����
	if (false)
	{
		// �f�����[�r�[���~����
	}
}
