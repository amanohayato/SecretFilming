#pragma once
#include<map>
#include<DxLib.h>

//シェーダーID
enum class ShaderID {
	TEST_SHADER,
	SKYBOX_SHADER,//スカイボックス用シェーダー
	GAUGE_SHADER,
	TILING_SHADER,
};

//シェーダーを管理するクラス
class ShaderManager {
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager& getInstance() {
		static ShaderManager manager;
		return manager;
	}
	//初期化
	void initialize();
	//シェーダーの読み込み
	void LoadShader(ShaderID id, const std::string& vertexShader, const std::string& pixelShader);
	void LoadShader(ShaderID id, const std::string& pixelShader);
	
	void CreateCBuff(ShaderID id, unsigned long long size);
	template<typename T>
	void UpdateCBuff(ShaderID id, const T& buff, int slot);

	int getCBuff(ShaderID id) {
		return cbuffHandleMap_[id];
	}
	//シェーダーの有効化
	void begin(ShaderID id);
	void begin_px(ShaderID id);

	std::pair<int, int> getHandle(ShaderID id);
	//シェーダーの無効化
	void end();
private:

	std::map<ShaderID, std::pair<int, int>> shaderHandleMap_;//ハンドル一覧
	std::map<ShaderID, int> cbuffHandleMap_;//ハンドル一覧

};

template<typename T>
void ShaderManager::UpdateCBuff(ShaderID id, const T & buff,int slot)
{
			T* cb = (T*)GetBufferShaderConstantBuffer(cbuffHandleMap_[id]);
			*cb = buff;
	
			UpdateShaderConstantBuffer(cbuffHandleMap_[id]);
			SetShaderConstantBuffer(cbuffHandleMap_[id], DX_SHADERTYPE_PIXEL, slot);

}
