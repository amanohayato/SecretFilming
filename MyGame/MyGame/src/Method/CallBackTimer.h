#pragma once
#include<functional>
#include<list>

//�񐔂𐔂��Ċ֐������s����(n�J�E���g�ڂɒʒm����)
//*��:count_=60 60��Ă΂ꂽ��true
class CallBackTimer {
public:
	CallBackTimer() :func_{} {

	}
	//�񐔂�ݒ�
	void setCount(int count) {
		count_ = count;
	}
	//���Ԃ�ݒ�
	void setTime(float time) {
		count_ = (int)(time*60.0f);
	}
	//�֐��̐ݒ�
	void setFunc(const std::function<void()>& func) {
		func_.push_back(func);
	}
	void operator ()() {
		count_--;
		//���ԂɂȂ����u�Ԃ���
		if (count_ == 0) {
			//�֐���S���s����
			for (auto& f : func_) {
				f();
			}
			//�֐��̃N���A
			func_.clear();
		}
	}
private:
	int count_{ 0 };//���s��
	std::list<std::function<void()>> func_;
};