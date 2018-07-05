#include "Keyboard.h"

// �R���X�g���N�^
Keyboard::Keyboard()
{
}

void Keyboard::InputStop()
{

	for (auto& k : m_keycode) {
		k = 0;
	}
	for (auto& k : m_prevkeycode) {
		k = 0;
	}
}

// �L�[�����������̃g���K�[����
bool Keyboard::KeyTriggerDown(UINT keycode)
{
	if (m_keycode[keycode] != 0&& m_prevkeycode[keycode] == 0)	return true;
	return false;
}

// �L�[�����������̃X�e�[�g����
bool Keyboard::KeyStateDown(UINT keycode)
{
	if (m_keycode[keycode] != 0)	return true;
	return false;
}

// �L�[�𗣂������̃g���K�[����
bool Keyboard::KeyTriggerUp(UINT keycode)
{
	if (m_keycode[keycode] == 0 && m_prevkeycode[keycode] != 0)	return true;
	return false;
}

// �L�[�𗣂������̃X�e�[�g����
bool Keyboard::KeyStateUp(UINT keycode)
{
	if (m_keycode[keycode] == 0)	return true;
	return false;
}

// �����ꂩ�̃L�[�����͂��ꂽ���u�Ԃ𒲂ׂ�
bool Keyboard::AnyTriggerDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] != 0 && m_prevkeycode[i] == 0)	return true;
	}
	return false;
}

// �����ꂩ�̃L�[�����͂���Ă��邩���ׂ�
bool Keyboard::AnyStateDown()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] != 0)return true;
	}
	return false;
}

// �����ꂩ�̃L�[�����ꂽ���u�Ԃ𒲂ׂ�
bool Keyboard::AnyTriggerUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 0 && m_prevkeycode[i] != 0)	return true;
	}
	return false;
}

// �����ꂩ�̃L�[������Ă��邩���ׂ�
bool Keyboard::AnyStateUp()
{
	for (int i = 0; i < 256; i++)
	{
		if (m_keycode[i] == 0)	return true;
	}
	return false;
}

// �X�V����
void Keyboard::Update()
{
	for (int i = 0; i < 256; i++) {
		m_prevkeycode[i] = m_keycode[i];

	}
	GetHitKeyStateAll(m_keycode);

}

