#pragma once
#include"../Actor.h"
#include"../../Graphic/TextBox.h"
#include"../../Method/MethodTimer.h"

class TextActor:public Actor {
public:
	TextActor(IWorld* world, const Vector2& boxSize = Vector2{1000,150},int priority=1) :Actor(world, "Text", Vector3::Zero), _text(priority), _boxSize(boxSize) {

	}
	virtual void initialize()override {
		_text.Init();
		_text.Display_Text();
		_text.Start_Text();
		_timer.Initialize();
		_timerFunc = [] {};

	}
	void setTime(int frame) {
		_timer.AddEmpty(frame);
		_timer.Add([&] {dead(); });

	}
	void add(const std::string& filename) {
		_text.add(filename);
	}

	virtual void update(float deltaTime) override {
		_timerFunc();
		_text.Update();
		if (_text.isEnd()) {
			if (!_text.Increment_Text()) {
				_text.Hidden_Text();
				if (_text.getAlpha() <= 0)dead();
			}
		}
	}

	virtual void draw()const override {
		if (world_->getCameraAmount() >= 0.01f)return;
		if (world_->getMapAmount() >= 0.01f)return;
		Vector2 pos = Vector2{ 200,800 };
		world_->addDrawFunction([&,pos] {
			_text.Draw(pos, FONT_ID::FONT_TEXT, _boxSize);
		});
	}

private:
	TextBox _text;
	MethodTimer _timer{};
	std::function<void()> _timerFunc;
	Vector2 _boxSize;
};