#pragma once
#include<DxLib.h>
#include"../Math/Vector2.h"

class XInputGamePad {
	XInputGamePad(){}
public:
	static XInputGamePad & GetInstance() {
		static XInputGamePad xigp;
		return xigp;
	}
	void InputStop() {
		for (auto& b:xis_.Buttons) {
			b = 0;
		}
		xis_.LeftTrigger = 0;
		xis_.RightTrigger = 0;
		xis_.ThumbLX = 0;
		xis_.ThumbRX = 0;
		xis_.ThumbLY = 0;
		xis_.ThumbRY = 0;


		for (auto& b : pxis_.Buttons) {
			b = 0;
		}
		pxis_.LeftTrigger = 0;
		pxis_.RightTrigger = 0;
		pxis_.ThumbLX = 0;
		pxis_.ThumbRX = 0;
		pxis_.ThumbLY = 0;
		pxis_.ThumbRY = 0;
	}
	bool ButtonStateDown(int keyCode) const {
		return xis_.Buttons[keyCode] == 1;
	}
	bool ButtonTriggerDown(int keyCode)const {
		return ButtonStateDown(keyCode) && pxis_.Buttons[keyCode] == 0;
		
	}
	bool ButtonStateUp(int keyCode) const {
		return xis_.Buttons[keyCode] == 0;
	}
	bool ButtonTriggerUp(int keyCode)const {
		return ButtonStateUp(keyCode)&&pxis_.Buttons[keyCode] == 1;
	}
	Vector2 Stick()const {
		int x = xis_.ThumbLX;
		if (x >= 0)x++;
		float ansx = (float)x / 32768;
		int y = xis_.ThumbLY;
		if (y >= 0)y++;
		float ansy = (float)y / 32768;
		return Vector2{ ansx,ansy };
	}
	Vector2 GetPreviousStick()const {
		int x = pxis_.ThumbLX;
		if (x >= 0)x++;
		float ansx = (float)x / 32768;
		int y = pxis_.ThumbLY;
		if (y >= 0)y++;
		float ansy = (float)y / 32768;
		return Vector2{ ansx,ansy };
	}
	Vector2 RightStick()const {
		int x = xis_.ThumbRX;
		if (x >= 0)x++;
		float ansx = (float)x / 32768;
		int y = xis_.ThumbRY;
		if (y >= 0)y++;
		float ansy = (float)y / 32768;
		return Vector2{ ansx,ansy };
	}
	Vector2 GetPreviousRightStick()const {
		int x = pxis_.ThumbRX;
		if (x >= 0)x++;
		float ansx = (float)x / 32768;
		int y = pxis_.ThumbRY;
		if (y >= 0)y++;
		float ansy = (float)y / 32768;
		return Vector2{ ansx,ansy };
	}

	int GetPovAngle()const {
		int angle = 0;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_UP] == 1)angle += 1;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == 1)angle += 2;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_DOWN] == 1)angle += 4;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_LEFT] == 1)angle += 8;
		
		switch (angle)
		{
		case 1:return 0;
		case 2:return 90;
		case 3:return 45;
		case 4:return 180;
		case 6:return 135;
		case 8:return 270;
		case 9:return 315;
		case 12:return 225;
		default:
			return -1;
			break;
		}
	}
	Vector2 GetPovVector() const
	{
		int angle = GetPovAngle();
		switch (angle)
		{
		case 0:return Vector2::Up;			break;
		case 45:return Vector2::One;		break;
		case 90:return Vector2::Right;		break;
		case 135:return Vector2{ 1.f,-1.f }; break;
		case 180:return Vector2::Down;		break;
		case 225:return -Vector2::One;		break;
		case 270:return	Vector2::Left;		break;
		case 315:return Vector2{ -1.f,1.f }; break;
		default:return Vector2::Zero; break;
		}

	}
	int GetPovTriggerDownAngle()const {
		int cur = GetPovAngle();
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_UP] == 1)return -1;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == 1)return -1;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_DOWN] == 1)return -1;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_LEFT] == 1)return -1;

		return cur;
	}
	Vector2 GetPovTriggerDownVector() const {
		auto cur = GetPovVector();
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_UP] == 1)return Vector2::Zero;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_RIGHT] == 1)return Vector2::Zero;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_DOWN] == 1)return Vector2::Zero;
		if (xis_.Buttons[XINPUT_BUTTON_DPAD_LEFT] == 1)return Vector2::Zero;
		return cur;
	}
	bool AnyStateDown()const {
		bool result = false;
		for (auto& xb : xis_.Buttons) {
			if (xb == 1)result = true;
		}
		return
			LTrigger_StateDown() ||
			RTrigger_StateDown() ||
			result;

	}
	bool AnyTriggerDown()const {
		bool result = false;
		for (int i = 0; i < 16;i++) {
			if (xis_.Buttons[i] == 1 &&
				pxis_.Buttons[i] == 0)result = true;
		}
		return
			LTrigger_TriggerDown() ||
			RTrigger_TriggerDown() ||
			result;

	}
	bool LTrigger_StateDown()const {
		return xis_.LeftTrigger >= 50;
	}
	bool LTrigger_TriggerDown()const {
		return LTrigger_StateDown() && pxis_.LeftTrigger < 50;
	}
	bool LTrigger_StateUp()const {
		return xis_.LeftTrigger < 50;
	}
	bool LTrigger_TriggerUp()const {
		return LTrigger_StateUp() && pxis_.LeftTrigger >= 50;
	}

	bool RTrigger_StateDown() const {
		return xis_.RightTrigger >= 50;
	}
	bool RTrigger_TriggerDown() const {
		return RTrigger_StateDown() && pxis_.RightTrigger < 50;
	}
	bool RTrigger_StateUp() const {
		return xis_.RightTrigger < 50;
	}
	bool RTrigger_TriggerUp() const {
		return RTrigger_StateUp() && pxis_.RightTrigger >= 50;
	}
	void update() {
		pxis_ = xis_;
		GetJoypadXInputState(DX_INPUT_PAD1, &xis_);
	}

private:
	XINPUT_STATE xis_{};
	XINPUT_STATE pxis_{};

};

