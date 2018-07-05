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

// シャドウマップをセットする（sizeは2のn乗で設定する）
void ShadowMap::Set(SHADOW_ID id, const Point& size, const Vector3& lightdirection)
{
	if (m_shadowmaps.count(id) != 0) {
		Delete(id);
	}
	m_shadowmaps[id] = MakeShadowMap(size.x, size.y);
	SetShadowMapLightDirection(m_shadowmaps[id], VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// シャドウマップを削除する
void ShadowMap::Delete(SHADOW_ID id)
{
	DeleteShadowMap(m_shadowmaps[id]);
	m_shadowmaps.erase(id);
}

// 想定するライトの方向をセットする
void ShadowMap::SetLightDirection(SHADOW_ID id, const Vector3& lightdirection) const
{
	SetShadowMapLightDirection(m_shadowmaps.at(id), VGet(lightdirection.x, lightdirection.y, lightdirection.z));
}

// シャドウマップに描画する範囲を設定する
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

// シャドウマップを開始する
void ShadowMap::Begin(SHADOW_ID id) const
{
	ShadowMap_DrawSetup(m_shadowmaps.at(id));
}

// シャドウマップを終了する
void ShadowMap::End() const
{
	ShadowMap_DrawEnd();
}
