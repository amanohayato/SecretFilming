#pragma once
#include<functional>
#include<list>

//回数を数えて関数を実行する(nカウント目に通知する)
//*例:count_=60 60回呼ばれたらtrue
class CallBackTimer {
public:
	CallBackTimer() :func_{} {

	}
	//回数を設定
	void setCount(int count) {
		count_ = count;
	}
	//時間を設定
	void setTime(float time) {
		count_ = (int)(time*60.0f);
	}
	//関数の設定
	void setFunc(const std::function<void()>& func) {
		func_.push_back(func);
	}
	void operator ()() {
		count_--;
		//時間になった瞬間だけ
		if (count_ == 0) {
			//関数を全実行する
			for (auto& f : func_) {
				f();
			}
			//関数のクリア
			func_.clear();
		}
	}
private:
	int count_{ 0 };//実行回数
	std::list<std::function<void()>> func_;
};