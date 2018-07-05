#include "ShaderManager.h"

ShaderManager::ShaderManager() {

}

ShaderManager::~ShaderManager() {}

void ShaderManager::initialize() {
	InitShader();
	shaderHandleMap_.clear();
	InitShaderConstantBuffer();
	cbuffHandleMap_.clear();
}

void ShaderManager::LoadShader(ShaderID id,const std::string & vertexShader, const std::string & pixelShader)
{
	int vertex = LoadVertexShader(vertexShader.c_str());
	int pixel = LoadPixelShader(pixelShader.c_str());

	shaderHandleMap_[id] = std::make_pair(vertex, pixel);
}

void ShaderManager::LoadShader(ShaderID id, const std::string & pixelShader)
{
	int pixel = LoadPixelShader(pixelShader.c_str());

	shaderHandleMap_[id] = std::make_pair(-1, pixel);
}

void ShaderManager::CreateCBuff(ShaderID id, unsigned long long size)
{
	cbuffHandleMap_[id] = CreateShaderConstantBuffer((int)size);
}

void ShaderManager::begin(ShaderID id) {
	MV1SetUseOrigShader(TRUE);
	SetUseVertexShader(shaderHandleMap_.at(id).first);
	SetUsePixelShader(shaderHandleMap_.at(id).second);

}

void ShaderManager::begin_px(ShaderID id)
{
	MV1SetUseOrigShader(TRUE);
	SetUsePixelShader(shaderHandleMap_.at(id).second);

}

std::pair<int, int> ShaderManager::getHandle(ShaderID id)
{
	return shaderHandleMap_[id];
}

void ShaderManager::end() {
	SetUseVertexShader(-1);
	SetUsePixelShader(-1);
	MV1SetUseOrigShader(FALSE);
}
