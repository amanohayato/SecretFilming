//#pragma once
//#include<functional>
//#include<vector>
//
////�o�^���ꂽ�֐����ꊇ���s����N���X
//template<typename VALUE,typename ...T>
//class FunctionExecutor {
//public:
//	FunctionExecutor() {
//		methods_.clear();
//	}
//	~FunctionExecutor() {
//		methods_.clear();
//	}
//	//�֐��̒ǉ�
//	void add(std::function<VALUE(T...)>* func) {
//		methods_.push_back(func);
//	}
//	//�֐��̍폜
//	void sub(std::function<VALUE(T...)>* func) {
//
//		auto target = std::find(methods_.begin(), methods_.end(), func);
//		if (target == methods_.end())return;
//
//		methods_.erase(target);
//	}
//
//	//�֐��̎��s
//	VALUE execute(T... arg) {
//		VALUE result;
//		for (auto method : methods_) {
//			std::function<VALUE(T...)> func = *method;
//			result = func(arg...);
//		}
//		return result;
//	}
//
//	//�֐��̎��s
//	template<typename ...T>
//	void execute<void>(T... arg) {
//		for (auto method : methods_) {
//			std::function<VALUE(T...)> func = *method;
//			result = func(arg...);
//		}
//	}
//
//	FunctionExecutor& operator +=(std::function<VALUE(T...)>& func) {
//		add(&func);
//		return *this;
//	}
//
//	FunctionExecutor& operator -=(std::function<VALUE(T...)>& func) {
//		sub(&func);
//		return *this;
//	}
//
//
//	FunctionExecutor(const FunctionExecutor& other) = delete;
//	FunctionExecutor& operator =(const FunctionExecutor& other) = delete;
//
//private:
//
//	std::vector<std::function<VALUE(T...)>*> methods_;
//};