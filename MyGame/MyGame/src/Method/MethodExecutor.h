#pragma once
#include<functional>
#include<vector>


template < typename >
class MethodExecutor{};

//�o�^���ꂽ�֐����ꊇ���s����N���X
template<typename VALUE, typename ...T>
class MethodExecutor<VALUE(T...)> {
public:
	MethodExecutor() {
		methods_.clear();
	}
	~MethodExecutor() {
		methods_.clear();
	}
	//�֐��̒ǉ�
	void add(const std::function<VALUE(T...)>& func) {
		methods_.push_back(func);
	}
	//�֐��̍폜
	void sub(const std::function<VALUE(T...)>& func) {
		
		//std::find(methods_.begin(), methods_.end(), func);
		//if (target == methods_.end())return;

		//methods_.erase(target);
	}

	//�֐��̎��s
	VALUE execute(T... arg) {
		VALUE result;
		for (auto& method : methods_) {
			result = method(arg...);
		}
		return result;
	}

	MethodExecutor& operator +=(const std::function<VALUE(T...)>& func) {
		add(func);
		return *this;
	}

	MethodExecutor& operator -=(const std::function<VALUE(T...)>& func) {
		sub(func);
		return *this;
	}


	MethodExecutor(const MethodExecutor& other) = delete;
	MethodExecutor& operator =(const MethodExecutor& other) = delete;

private:

	std::vector<std::function<VALUE(T...)>> methods_;
};

//�o�^���ꂽ�֐����ꊇ���s����N���X
template<typename ...T>
class MethodExecutor<void(T...)> {
public:
	MethodExecutor() {
		methods_.clear();
	}
	~MethodExecutor() {
		methods_.clear();
	}
	//�֐��̒ǉ�
	void add(const std::function<void(T...)>& func) {
		methods_.push_back(func);
	}
	//�֐��̍폜
	void sub(const std::function<void(T...)>& func) {

		//std::find(methods_.begin(), methods_.end(), func);
		//if (target == methods_.end())return;

		//methods_.erase(target);
	}

	//�֐��̎��s
	void execute(T... arg) {
		for (auto& method : methods_) {
			method(arg...);
		}
	}

	MethodExecutor& operator +=(const std::function<void(T...)>& func) {
		add(func);
		return *this;
	}

	MethodExecutor& operator -=(const std::function<void(T...)>& func) {
		sub(func);
		return *this;
	}


	MethodExecutor(const MethodExecutor& other) = delete;
	MethodExecutor& operator =(const MethodExecutor& other) = delete;

private:

	std::vector<std::function<void(T...)>> methods_;
};

