#pragma once
#include<vector>

template <typename T>
class MyVector {
	MyVector() :data_(nullptr),count_(0) {

	}
	~MyVector() {
		delete []data_;
	}


	T* data_;
	//�����I�u�W�F�N�g��
	unsigned int count_;
};