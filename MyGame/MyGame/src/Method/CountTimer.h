#pragma once

//�񐔂𐔂���(n�J�E���g�ڂɒʒm����)
//*��:count_=60 60��Ă΂ꂽ��true
class CountTimer {
public:
	CountTimer() {

	}
	//�񐔂�ݒ�
	void set(int count) {
		count_ = count;
	}
	//���Ԃ�ݒ�
	void setTime(float time) {
		count_ = (int)(time*60.0f);
	}
	//�^�C�}�[���I�������
	bool isTime()const {
		return count_ <= 0;
	}
	//�J�E���g�_�E��(���ʂ��ꏏ�ɕԋp)
	bool operator ()() {
		count_--;
		return isTime();
	}
private:
	int count_{ 0 };//���s��
};