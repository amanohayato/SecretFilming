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
	//所持オブジェクト数
	unsigned int count_;
};