//#pragma once
//#include<functional>
//#include<vector>
//
////登録された関数を一括実行するクラス
//template<typename VALUE,typename ...T>
//class FunctionExecutor {
//public:
//	FunctionExecutor() {
//		methods_.clear();
//	}
//	~FunctionExecutor() {
//		methods_.clear();
//	}
//	//関数の追加
//	void add(std::function<VALUE(T...)>* func) {
//		methods_.push_back(func);
//	}
//	//関数の削除
//	void sub(std::function<VALUE(T...)>* func) {
//
//		auto target = std::find(methods_.begin(), methods_.end(), func);
//		if (target == methods_.end())return;
//
//		methods_.erase(target);
//	}
//
//	//関数の実行
//	VALUE execute(T... arg) {
//		VALUE result;
//		for (auto method : methods_) {
//			std::function<VALUE(T...)> func = *method;
//			result = func(arg...);
//		}
//		return result;
//	}
//
//	//関数の実行
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