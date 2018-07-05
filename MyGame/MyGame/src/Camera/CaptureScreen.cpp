#include "CaptureScreen.h"
#include"../Define.h"
#include"../Graphic/Sprite.h"
#include "../Scene/Manager/GameDataManager.h"

#include<DxLib.h>
#include<assert.h>
#include<list>
#include<functional>
#include <algorithm>

#define CREATE_FILE_NAME(text,num,fileNameExtension) text+std::to_string(num)+fileNameExtension

static const std::string defaultSSPath = "res/capture/";
static constexpr unsigned int MaxSSSize{ 30U };

CaptureScreen::CaptureScreen()
{
	drawGraphHandle_ = MakeGraph(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void CaptureScreen::initialize()
{
	clear();
}

void CaptureScreen::capture(int score)
{	
	GameDataManager::getInstance().addPhotoCount();

	int handle = MakeSoftImage(WINDOW_WIDTH, WINDOW_HEIGHT);
	GetDrawScreenSoftImage(0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, handle);

	captureScreenCollection_.push_back(std::make_pair(handle,score));

	ssCollectionClean();
}

void CaptureScreen::save()
{
	save((unsigned int)(captureScreenCollection_.size() - 1));
}

void CaptureScreen::save(unsigned int target)
{
	if (target >= captureScreenCollection_.size())return;//�Ώۂ����݂��Ȃ��Ȃ珈�����Ȃ�

	auto savePath = defaultSSPath + getFileList();
	SaveSoftImageToPng(savePath.c_str(), captureScreenCollection_.at(target).first, 5);
}

void CaptureScreen::clear()
{
	for (auto i : captureScreenCollection_) {
		DeleteSoftImage(i.first);
	}
	captureScreenCollection_.clear();

	for (auto i : resultDrawGraphHandle_) {
		DeleteSoftImage(i);
	}
	resultDrawGraphHandle_.clear();
}

int CaptureScreen::getScore() const
{
	int result = 0;
	for (auto cs : captureScreenCollection_) {
		result += cs.second;
	}
	return result;
}

int CaptureScreen::getSize() const
{
	return (int)captureScreenCollection_.size();
}

void CaptureScreen::draw(const Vector2 & position, const Vector2 & origin, float alpha, const Vector2 & scale, float angle, bool trans, bool turn) const
{
	draw((unsigned int)(captureScreenCollection_.size() - 1), position, origin, alpha, scale, angle, trans, turn);
}

void CaptureScreen::draw(unsigned int target, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn) const
{
	if (captureScreenCollection_.size() <= target) return;
	ReCreateGraphFromSoftImage(captureScreenCollection_.at(target).first, drawGraphHandle_);

	Sprite::GetInstance().Draw(drawGraphHandle_, position, origin, alpha, scale, angle, trans, turn);
}
/*************************************************************************************************************************************************************************/
void CaptureScreen::mGraph() const{
	mGraph((unsigned int)(captureScreenCollection_.size() - 1));
}
void CaptureScreen::mGraph(unsigned int target) const{
	if (captureScreenCollection_.size() <= target) return;
	ReCreateGraphFromSoftImage(captureScreenCollection_.at(target).first, drawGraphHandle_);
}
void CaptureScreen::drawFarst(const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn) const {
	Sprite::GetInstance().Draw(drawGraphHandle_, position, origin, alpha, scale, angle, trans, turn);
}

void CaptureScreen::sortVectorToScore()
{
	std::sort(captureScreenCollection_.begin(), captureScreenCollection_.end(), [](const std::pair<int, int>& left, const std::pair<int, int>& right) { return (left.second > right.second); });
}
void CaptureScreen::setResultDrawGraphHandle(int range)
{
	for (int i = 0; i < range; i++)
	{
		if (captureScreenCollection_.size() <= i) break;

		int tempHandle = MakeGraph(WINDOW_WIDTH, WINDOW_HEIGHT);

		ReCreateGraphFromSoftImage(captureScreenCollection_.at(i).first, tempHandle);

		resultDrawGraphHandle_.push_back(tempHandle);
	}
}
void CaptureScreen::drawResultPhoto(unsigned int target, const Vector2& position, const Vector2& origin, float alpha, const Vector2& scale, float angle, bool trans, bool turn) const
{
	Sprite::GetInstance().Draw(resultDrawGraphHandle_[target], position, origin, alpha, scale, angle, trans, turn);
}
/*************************************************************************************************************************************************************************/
std::string CaptureScreen::getFileList()
{
	std::string filename{ "capture_game_screenshot" };
	std::string filename_extension{ ".png" };
	std::string filepath{ defaultSSPath + filename + "*" + filename_extension };
	constexpr int defaultCount = 1;//�����l

	WIN32_FIND_DATA data;//�t�@�C�������܂Ƃ߂��\����
	auto handle = FindFirstFile(filepath.c_str(), &data);//�Ώۃp�X�̐擪�t�@�C���������o��
	if (handle == INVALID_HANDLE_VALUE)return CREATE_FILE_NAME(filename, defaultCount, filename_extension);//������Ȃ��������f�[�^��Ԃ�
	
	std::list<int> numList{};

	do {
		if (data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) continue;//�f�B���N�g���͖���

		std::string current = data.cFileName;//���݂̑Ώۃt�@�C����
		current = current.substr(filename.size());
		current = current.substr(0, current.size() - filename_extension.size());
		int result = atoi(current.c_str());//�t�@�C��������ԍ��݂̂����o��
		if (result == 0)continue;//�ԍ������݂��Ȃ������疳��
		numList.push_back(result);


	} while (FindNextFile(handle, &data));
	
	if (numList.empty())return CREATE_FILE_NAME(filename, defaultCount, filename_extension);//�ԍ��t�@�C�������Ȃ��������f�[�^��Ԃ�


	numList.sort(std::greater<int>());

	
	return CREATE_FILE_NAME(filename, ++numList.front(), filename_extension);//���݂̍ő�+1�̒l�Ńt�@�C�������쐬
	
}

void CaptureScreen::ssCollectionClean()
{
	//�ۑ�����łȂ���΍폜�͍s��Ȃ�
	if (MaxSSSize >= captureScreenCollection_.size())return;

	//�Œ�X�R�A�Ƃ��̑Ώۂ�ێ�
	int minScore = captureScreenCollection_.front().second;
	int deleteCell = 0;

	for (int i = 0; i < captureScreenCollection_.size(); i++) {
		int score = captureScreenCollection_.at(i).second;

		//�X�R�A0�������������_�ł�����폜
		if (score == 0) {
			deleteCell = i;
			break;
		}

		//���Œ�l��������������폜�Ώۂɂ���
		if (score >= minScore)continue;
		minScore = score;
		deleteCell = i;
	}
	DeleteGraph((captureScreenCollection_.begin() + deleteCell)->first);
	captureScreenCollection_.erase(captureScreenCollection_.begin() + deleteCell);

}
