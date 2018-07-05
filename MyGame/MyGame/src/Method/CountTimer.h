#pragma once

//回数を数える(nカウント目に通知する)
//*例:count_=60 60回呼ばれたらtrue
class CountTimer {
public:
	CountTimer() {

	}
	//回数を設定
	void set(int count) {
		count_ = count;
	}
	//時間を設定
	void setTime(float time) {
		count_ = (int)(time*60.0f);
	}
	//タイマーが終わったか
	bool isTime()const {
		return count_ <= 0;
	}
	//カウントダウン(結果も一緒に返却)
	bool operator ()() {
		count_--;
		return isTime();
	}
private:
	int count_{ 0 };//実行回数
};