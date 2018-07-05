#pragma once
#include<vector>
#include"../../World/IWorld.h"

class IWorld;
class CitizenGenerateManager {
public:
	CitizenGenerateManager();
	void setWorld(IWorld* world);
	void initialize();
	void update(float deltaTime);

private:
	std::vector<float> timer_;
	IWorld* world_;
	static const int OneRouteMax_ = 1;//同じルートの同時存在可能人数
	bool Path_Size_Half_ = false;
	//Vector3 cipos_ = Vector3::Zero;
};