#include "TextBox.h"
#include"FontManager.h"
#include"TextBoxPriorityManager.h"

#include "../Math/MathHelper.h"

static constexpr int textStopSpeed = 3;
static constexpr int alphaSpeed = 5;

//ctrlFuncを空にする
#define FUNC_RESET ctrlFunc_ = [] {}

TextBox::TextBox(int priority) :_priority(priority)
{
}

void TextBox::Init()
{
	isEnd_ = true;
	display_ = false;
	isPlay_ = false;
	isDraw = true;
	alpha_ = 0;
	isDrawAlpha = 0;

	textCount_ = 0;
	timeCount_ = 0;
	//データを初期化
	textList_.clear();
	currentText_ = 0;

	FUNC_RESET;


}

void TextBox::add(const std::string & filename)
{
	//ファイルを読んでくる
	std::ifstream readText_("res/Text/" + filename);
	readText_.seekg(0, std::ios_base::end);
	std::size_t size = (std::size_t)readText_.tellg();//文字サイズを確認
	readText_.seekg(0, std::ios_base::beg);
	std::vector<char> charbuf(size);//文字列を全て格納する配列
	readText_.read(&charbuf[0], size);

	std::string strbuf;
	strbuf.assign(charbuf.begin(), charbuf.end());

	textList_.push_back(strbuf);

}

void TextBox::Reset()
{
	textCount_ = 0;
	timeCount_ = 0;
}

void TextBox::Update()
{
	if (isDraw)	display_ ? in() : out();
	isPlay_ ? play() : stop();

	if (!isDraw)alpha_ -= alphaSpeed;

	alpha_ = MathHelper::Clamp(alpha_, 0, 255);
	if (alpha_ > 0 && !textList_.empty()) {
		TextBoxPriorityManager::getInstance().setNum(_priority);
	}
}
void TextBox::Draw(const Vector2 & position, FONT_ID id, const Vector2& size, const Vector2& padding, unsigned int color) const
{
	if (textList_.empty())return;
	if (TextBoxPriorityManager::getInstance().getMax() > _priority)return;
	if (alpha_ > 0)TextBoxPriorityManager::getInstance().addNum();
	auto sizeVec = position + size;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	DrawBox((int)(position.x - padding.x),(int)( position.y - padding.y), (int)(sizeVec.x + padding.x),(int)( sizeVec.y + padding.y), GetColor(0, 0, 200), FALSE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(alpha_*0.5f));
	DrawFillBox((int)(position.x - padding.x), (int)(position.y - padding.y), (int)(sizeVec.x + padding.x), (int)(sizeVec.y + padding.y), GetColor(0, 0, 100));
	auto text = textList_.at(currentText_).substr(0, textCount_);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_);
	FontManager::GetInstance().DrawTextApplyFont((int)position.x, (int)position.y, color, id, text);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TextBox::End()
{
}

void TextBox::in()
{
	constexpr int MAX_ALPHA = 255;
	alpha_ += alphaSpeed;

	if (alpha_ >= MAX_ALPHA) {
		ctrlFunc_();
		FUNC_RESET;
	}

	alpha_ = min(alpha_, 255);
}

void TextBox::out()
{
	alpha_ -= alphaSpeed;
	alpha_ = max(alpha_, 0);

}

void TextBox::play()
{
	if (textList_.empty())return;

	timeCount_++;
	if (timeCount_%textStopSpeed == 0) {
		auto str = textList_.at(currentText_).substr(textCount_);
		if (str.empty())return;
		auto ch = str.front();
		auto len = _mbclen((BYTE*)&ch);
		textCount_ += (int)len;
		timeCount_ = 0;
	}
	if (textList_.at(currentText_).size() <= textCount_) {
		textCount_ = (int)textList_.at(currentText_).size();
		isEnd_ = true;
		return;
	}
}

void TextBox::stop()
{
}

void TextBox::Display_Text(bool isAnimation)
{
	constexpr int MAX_ALPHA = 255;

	if (!isAnimation) alpha_ = MAX_ALPHA;

	display_ = true;
}

void TextBox::Hidden_Text()
{
	display_ = false;
}

void TextBox::Start_Text()
{
	isEnd_ = false;
	ctrlFunc_ = [&] {isPlay_ = true; };
}

void TextBox::Stop_Text()
{
	isPlay_ = false;
}

bool TextBox::Increment_Text()
{
	if (currentText_ >= textList_.size() - 1)return false;
	currentText_++;
	Reset();
	return true;
}

void TextBox::Decrement_Text()
{
	if (currentText_ <= 0)return;
	currentText_--;
	Reset();
}

void TextBox::Set_Current_Text(int currentText)
{
	currentText_ = currentText;
	Reset();
}

int TextBox::Get_Current_Text()
{
	return currentText_;
}

bool TextBox::isEndPlay()
{
	return (textCount_ >= textList_.at(currentText_).length());
}
void TextBox::SetIsDraw(bool flag)
{
	isDraw = flag;
}
