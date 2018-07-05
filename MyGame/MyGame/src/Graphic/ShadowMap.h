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
	/// シャドウマップをセットする（sizeは2のn乗で設定する）
	///</summary>
	void Set(SHADOW_ID id, const Point& size, const Vector3& lightdirection);

	///<summary>
	/// シャドウマップを削除する
	///</summary>
	void Delete(SHADOW_ID id);

	///<summary>
	/// 想定するライトの方向をセットする
	///</summary>
	void SetLightDirection(SHADOW_ID id, const Vector3& lightdirection) const;

	///<summary>
	/// シャドウマップに描画する範囲を設定する
	///</summary>
	void SetRange(SHADOW_ID id,const Vector3& minpos, const Vector3& maxpos) const;

	//実際に影を出す
	void Enable(SHADOW_ID id,int slot) const ;

	void Disable(int slot) const ;

	// シャドウマップに書き込む
	void Begin(SHADOW_ID id) const ;

	/// シャドウマップを終了する
	void End() const ;

private:
	std::unordered_map<SHADOW_ID, int> m_shadowmaps;// シャドウマップ達を格納
};