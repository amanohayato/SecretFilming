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
	//��ʏ�Ԃ��������ɕۑ�
	void capture(int score=0);
	//�ŐV��ʏ����摜�t�@�C���Ƃ��ĕۑ�
	void save();
	//�w���ʏ����摜�t�@�C���Ƃ��ĕۑ�
	void save(unsigned int target);
	void clear();

	int getScore() const;

	int getSize()const;

	//�ŐV��ʏ��̕`��
	void draw(const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)const;
	//�w���ʏ��̕`��
	void draw(unsigned int target, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)const;
	//�ŐV�摜���̏�������
	void mGraph()const;
	//�w��摜���̏�������
	void mGraph(unsigned int target)const;
	//�������݂Ȃ��`��
	void drawFarst(const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false)const;

	void sortVectorToScore();

	void setResultDrawGraphHandle(int range);

	void drawResultPhoto(unsigned int target, const Vector2& position, const Vector2& origin = Vector2::Zero, float alpha = 1.0f, const Vector2& scale = Vector2::One, float angle = 0.0f, bool trans = true, bool turn = false) const;

private:
	std::string getFileList();

	//�摜���������ɕۑ�����ہA����ɒB���Ă��邩���m�F����
	void ssCollectionClean();

	int drawGraphHandle_;//�`��p�̃������m��
	std::vector<std::pair<int,int>> captureScreenCollection_{};//�摜�f�[�^���X�g(�n���h��,�X�R�A)
	
	std::vector<int> resultDrawGraphHandle_{};// ���U���g�p�̕`��p�̃������m��

};