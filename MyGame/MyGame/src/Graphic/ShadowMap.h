#pragma once

#include <string>
#include <unordered_map>
#include "../math/Vector3.h"
#include "../math/Vector2.h"
#include "../math/Point.h"
#include"../ID/EnumIDs.h"

class ShadowMap
{
	ShadowMap() = default;
	~ShadowMap();
public:
	static ShadowMap& GetInstance() {
		static ShadowMap map;
		return map;
	}
	void initialize();
	///<summary>
	/// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
	///</summary>
	void Set(SHADOW_ID id, const Point& size, const Vector3& lightdirection);

	///<summary>
	/// �V���h�E�}�b�v���폜����
	///</summary>
	void Delete(SHADOW_ID id);

	///<summary>
	/// �z�肷�郉�C�g�̕������Z�b�g����
	///</summary>
	void SetLightDirection(SHADOW_ID id, const Vector3& lightdirection) const;

	///<summary>
	/// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
	///</summary>
	void SetRange(SHADOW_ID id,const Vector3& minpos, const Vector3& maxpos) const;

	//���ۂɉe���o��
	void Enable(SHADOW_ID id,int slot) const ;

	void Disable(int slot) const ;

	// �V���h�E�}�b�v�ɏ�������
	void Begin(SHADOW_ID id) const ;

	/// �V���h�E�}�b�v���I������
	void End() const ;

private:
	std::unordered_map<SHADOW_ID, int> m_shadowmaps;// �V���h�E�}�b�v�B���i�[
};