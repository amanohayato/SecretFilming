#pragma once
#include<vector>

class IWorld;
class CarGenerateManager {
public:
	CarGenerateManager();
	void setWorld(IWorld* world);
	void initialize();
	void update(float deltaTime);

private:
	std::vector<float> timer_;
	IWorld* world_;
	static const int OneRouteMax_ = 1;//同じルートの同時存在可能人数
};