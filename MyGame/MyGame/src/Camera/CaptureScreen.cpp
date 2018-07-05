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
	if (target >= captureScreenCollection_.size())return;//対象が存在しないなら処理しない

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
	constexpr int defaultCount = 1;//初期値

	WIN32_FIND_DATA data;//ファイル情報をまとめた構造体
	auto handle = FindFirstFile(filepath.c_str(), &data);//対象パスの先頭ファイル情報を取り出す
	if (handle == INVALID_HANDLE_VALUE)return CREATE_FILE_NAME(filename, defaultCount, filename_extension);//見つからなかったら空データを返す
	
	std::list<int> numList{};

	do {
		if (data.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) continue;//ディレクトリは無視

		std::string current = data.cFileName;//現在の対象ファイル名
		current = current.substr(filename.size());
		current = current.substr(0, current.size() - filename_extension.size());
		int result = atoi(current.c_str());//ファイル名から番号のみを取り出す
		if (result == 0)continue;//番号が存在しなかったら無視
		numList.push_back(result);


	} while (FindNextFile(handle, &data));
	
	if (numList.empty())return CREATE_FILE_NAME(filename, defaultCount, filename_extension);//番号ファイルがいなかったら空データを返す


	numList.sort(std::greater<int>());

	
	return CREATE_FILE_NAME(filename, ++numList.front(), filename_extension);//現在の最大+1の値でファイル名を作成
	
}

void CaptureScreen::ssCollectionClean()
{
	//保存上限でなければ削除は行わない
	if (MaxSSSize >= captureScreenCollection_.size())return;

	//最低スコアとその対象を保持
	int minScore = captureScreenCollection_.front().second;
	int deleteCell = 0;

	for (int i = 0; i < captureScreenCollection_.size(); i++) {
		int score = captureScreenCollection_.at(i).second;

		//スコア0が発生した時点でそれを削除
		if (score == 0) {
			deleteCell = i;
			break;
		}

		//現最低値を下回った物を削除対象にする
		if (score >= minScore)continue;
		minScore = score;
		deleteCell = i;
	}
	DeleteGraph((captureScreenCollection_.begin() + deleteCell)->first);
	captureScreenCollection_.erase(captureScreenCollection_.begin() + deleteCell);

}
