#pragma once
#include"UI.h"
#include<list>
#include<vector>
#include<memory>
#include"../ID/EnumIDs.h"
#include"../Math/Vector3.h"

class IWorld;
class BuildingBase;
class FieldMap{
public:
	FieldMap(IWorld* world);
	
	//������
	void initialize();
	//�X�V
	void update(float deltaTime);
	//�`��
	void draw(const Vector2 & position) const;

	void pin_reset();//�S�s�����Z�b�g
	void targetpin_reset();//�ԃs���̑ł�����

	void pin_add(float deltaTime);//�s���̈ʒu��i�߂�
private:
	IWorld* world_;
	int colorSin_{ 0 };//�^�[�Q�b�g�{�b�N�X�̐F�ς�
	float pinPosRate_{ 0.0f };//�s���̈ʒu����
	float targetPinRate_{ 0.0f };//�ԃs���̈ʒu����
	int evpCount_{ 0 };//�C�x���g�|�C���g���ێ�
	std::list<std::weak_ptr<BuildingBase>> buildings_;
	std::list < std::tuple < SPRITE_ID, SPRITE_ID, Vector3>> drawIconList_;

};