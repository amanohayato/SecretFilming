#include "Skybox.h"
#include <DxLib.h>
#include "../../Math/Vector3.h"
#include "../../Define.h"
#include "../../Graphic/Shader/ShaderManager.h"
#include "../../Graphic/Model.h"

Skybox::Skybox(int skybox):
	skybox_(skybox), out_(skybox)
{
	if (skybox_ < 0) return;

	// スカイボックスの座標指定
	MV1SetPosition(skybox_, Vector3::Zero);
	// スカイボックスの拡大率指定
	MV1SetScale(skybox_, Vector3::One*2.f*15.0f);
}

void Skybox::update(float deltaTime)
{
	if (skybox_ < 0) return;
}

void Skybox::draw() const
{
	if (skybox_ < 0) return;
	// スカイボックスの描画
	MV1DrawModel(skybox_);
}

CollisionMesh & Skybox::getOutMesh()
{
	return out_.mesh_;
}
