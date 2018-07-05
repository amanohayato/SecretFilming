#pragma once
#include<map>
#include<DxLib.h>

//�V�F�[�_�[ID
enum class ShaderID {
	TEST_SHADER,
	SKYBOX_SHADER,//�X�J�C�{�b�N�X�p�V�F�[�_�[
	GAUGE_SHADER,
	TILING_SHADER,
};

//�V�F�[�_�[���Ǘ�����N���X
class ShaderManager {
private:
	ShaderManager();
	~ShaderManager();
public:
	static ShaderManager& getInstance() {
		static ShaderManager manager;
		return manager;
	}
	//������
	void initialize();
	//�V�F�[�_�[�̓ǂݍ���
	void LoadShader(ShaderID id, const std::string& vertexShader, const std::string& pixelShader);
	void LoadShader(ShaderID id, const std::string& pixelShader);
	
	void CreateCBuff(ShaderID id, unsigned long long size);
	template<typename T>
	void UpdateCBuff(ShaderID id, const T& buff, int slot);

	int getCBuff(ShaderID id) {
		return cbuffHandleMap_[id];
	}
	//�V�F�[�_�[�̗L����
	void begin(ShaderID id);
	void begin_px(ShaderID id);

	std::pair<int, int> getHandle(ShaderID id);
	//�V�F�[�_�[�̖�����
	void end();
private:

	std::map<ShaderID, std::pair<int, int>> shaderHandleMap_;//�n���h���ꗗ
	std::map<ShaderID, int> cbuffHandleMap_;//�n���h���ꗗ

};

template<typename T>
void ShaderManager::UpdateCBuff(ShaderID id, const T & buff,int slot)
{
			T* cb = (T*)GetBufferShaderConstantBuffer(cbuffHandleMap_[id]);
			*cb = buff;
	
			UpdateShaderConstantBuffer(cbuffHandleMap_[id]);
			SetShaderConstantBuffer(cbuffHandleMap_[id], DX_SHADERTYPE_PIXEL, slot);

}
