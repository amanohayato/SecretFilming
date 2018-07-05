#include "ShadowMap.h"
#include "../conv/DXConverter.h"

ShadowMap::~ShadowMap()
{
	
}

void ShadowMap::initialize()
{
	for (auto& s : m_shadowmaps) {
		DeleteShadowMap(s.second);
	}
	m_shadowmaps.clear();

}

// �V���h�E�}�b�v���Z�b�g����isize��2��n��Őݒ肷��j
void ShadowMap::Set(SHADOW_ID id, const Point& size, const Vector3& lightdirection)
{
	if (m_shadowmaps.count(id) != 0) {
		Delete(id);
	}
	m_shadowmaps[id] = MakeShadowMap(size.x, size.y);
	SetShadowMapLightDirection(m_shadowmaps[id], VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// �V���h�E�}�b�v���폜����
void ShadowMap::Delete(SHADOW_ID id)
{
	DeleteShadowMap(m_shadowmaps[id]);
	m_shadowmaps.erase(id);
}

// �z�肷�郉�C�g�̕������Z�b�g����
void ShadowMap::SetLightDirection(SHADOW_ID id, const Vector3& lightdirection) const
{
	SetShadowMapLightDirection(m_shadowmaps.at(id), VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// �V���h�E�}�b�v�ɕ`�悷��͈͂�ݒ肷��
void ShadowMap::SetRange(SHADOW_ID id,const Vector3& minpos, const Vector3& maxpos) const
{
	SetShadowMapDrawArea(m_shadowmaps.at(id), VGet(minpos.x, minpos.y, minpos.z), VGet(maxpos.x, maxpos.y, maxpos.z));
}

void ShadowMap::Enable(SHADOW_ID id, int slot) const
{
	SetUseShadowMap(slot, m_shadowmaps.at(id));
}

void ShadowMap::Disable(int slot) const
{
	SetUseShadowMap(slot, -1);
}

// �V���h�E�}�b�v���J�n����
void ShadowMap::Begin(SHADOW_ID id) const
{
	ShadowMap_DrawSetup(m_shadowmaps.at(id));
}

// �V���h�E�}�b�v���I������
void ShadowMap::End() const
{
	ShadowMap_DrawEnd();
}
