#pragma once
#include<functional>

class TextBoxPriorityManager {
	TextBoxPriorityManager(){
		_addFunc = [&] {_max++; };
	}
public:
	static TextBoxPriorityManager& getInstance() {
		static TextBoxPriorityManager t;
		return t;
	}

	void update() { _max = 0; }
	void setNum(int num) { 
		if (num > _max) {
			_max = num;
		}
	}

	int getMax()const { return _max; }

	void addNum()const { _addFunc(); }
private:
	int _max{ 0 };

	std::function<void()> _addFunc;
};