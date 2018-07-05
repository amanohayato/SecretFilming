#include "AlertGauge.h"
#include"../../Graphic/Model.h"
#include"../../Graphic/Shader/ShaderManager.h"
#include<DxLib.h>
#include "../../Sound/Sound.h"
#include "../../Graphic/DxlibGraphic.h"

static constexpr float defaultSize = 5.0f;
static constexpr float speedRate = 5.0f;
static constexpr float exclamDrawCount = 1.0f*speedRate;

AlertGauge::AlertGauge(IWorld* world,std::weak_ptr<EnemyBase> enemy) :
	Actor(world, "AlertGauge", enemy.lock()->getPosition()), target_(enemy)
{
	// ピクセルシェーダー用の定数バッファを作成
	cbuff_ = CreateShaderConstantBuffer(sizeof(FLOAT4));

}

void AlertGauge::initialize()
{
	angle_ = 0.0f;
	drawRate_ = 0.0f;
	addSign = 1.0f;
	excRate_ = 0.0f;
}

void AlertGauge::update(float deltaTime)
{
	// 警戒度に応じて、心音を流す（Ho Siu Kiの追加、2018-5-29）
	if (target_.expired())	return;

	addSign = 1.0f;
	// 警戒度が0になると、心音を流さない
	if (target_.lock()->get_awareness() <= 0.0f)
	{
		//drawRate_ = 0.0f;
		addSign = -1.0f;
	}
	// 警戒度が30以上になると、心音が流れ始める
	else if (target_.lock()->get_awareness() >= 30.0f)
	{
	}

	drawRate_ += deltaTime * speedRate*addSign;
	drawRate_ = MathHelper::Clamp(drawRate_, 0.0f, 1.0f);

	if (target_.lock()->get_awareness() > 99.9f)excRate_ += deltaTime * speedRate;
	else excRate_ = 0.0f;
}

void AlertGauge::draw() const
{

	if (target_.expired())return;

	world_->addDrawFunction([&] {
		//if (target_.lock()->get_awareness() <= 0.0f)return;
		//if (target_.lock()->get_ui_target() != name_)return;
		if (world_->findActor("NoticedLine") != nullptr)return;
		
		int blendrate = (int)MathHelper::Lerp(0.0f, 255.0f, drawRate_);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendrate);

		// ゲージ出現の演出を追加（Ho Siu Kiの追加、2018-5-29）
		constexpr float upPower = 10.0f;
		auto drawPos = target_.lock()->getPosition() + Vector3::Up*upPower;
		constexpr float size = 10.f;
		float drawSize = MathHelper::Lerp(defaultSize, size, drawRate_);
		Vector2 origin = Vector2{ 0.5f, 0.0f };

		// 警戒度が100を超えた場合、ビックリマークを表示（Ho Siu Kiの追加、2018-5-22）
		if (target_.lock()->get_awareness() >= 100.0f)
		{
			float excRate = MathHelper::Clamp(excRate_ - exclamDrawCount, 0.0f, 1.0f);
			blendrate = (int)MathHelper::Lerp(255.0f, 0.0f, excRate);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendrate);
			drawSize = MathHelper::Lerp(size, defaultSize, excRate);
			Model::GetInstance().Draw2D(MODEL_ID::SPRITE_EXCLAMATION, drawPos, 0, drawSize, origin, angle_);

		}
		// 警戒度が100未満の場合、はてなマークを表示
		else
		{
			FLOAT4* f4 = (FLOAT4 *)GetBufferShaderConstantBuffer(cbuff_);
			f4->x = target_.lock()->get_awareness();
			f4->y = 0.0f;
			f4->z = 0.0f;
			f4->w = 0.0f;
			UpdateShaderConstantBuffer(cbuff_);
			SetShaderConstantBuffer(cbuff_, DX_SHADERTYPE_PIXEL, 4);

			Model::GetInstance().Draw2D(MODEL_ID::SPRITE_QUESTION_FRAME, drawPos, 0, drawSize, origin, angle_);
			//ShaderManager::getInstance().begin_px(ShaderID::GAUGE_SHADER);
			MV1SetUseOrigShader(TRUE);
			//SetUseVertexShader(ShaderManager::getInstance().getHandle(ShaderID::GAUGE_SHADER).first);
			SetUsePixelShader(ShaderManager::getInstance().getHandle(ShaderID::GAUGE_SHADER).second);
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			//Model::GetInstance().Draw(MODEL_ID::MODEL_CAR, target_.lock()->getPose());
			DrawBillboard3DToShader(drawPos, origin.x, origin.y, drawSize, angle_, Model::GetInstance().GetHandle_Sprite(MODEL_ID::SPRITE_QUESTION_GAUGE), TRUE);
			//DrawBillboard3D(drawPos, 0.5f, 0.5f, size, 0.0f, Model::GetInstance().GetHandle_Sprite(MODEL_ID::SPRITE_QUESTION_GAUGE),TRUE);
			ShaderManager::getInstance().end();
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		/*
		// 描画方法を変更（Ho Siu Kiの変更、2018-5-29）
		if (enemy_.expired())	return;							// エネミーを存在しない場合、何もしない

		if (enemy_.lock()->get_awareness() <= 0.0f)	return;		// 警戒度は0の場合、何もしない
		*/
		// 描画する座標を指定
		/*
		constexpr float upPower = 10.0f;
		auto drawPos = enemy_.lock()->getPosition() + Vector3::Up * upPower;
		constexpr float size = 10.f;				// 表示のサイズ
		Vector2 origin = Vector2{ 0.5f, 0.0f };		// 画像の中心点

		int handle = MV1LoadTexture("res/Sprite/free/exclamation.png");
		*/
		// 警戒度が100を超えた場合、ビックリマークを表示
		/*if (enemy_.lock()->get_awareness() >= 100.0f)
		{
			DrawSprite3D(drawPos, size, handle, 255, 255, 255, 255, 0.0f, 0.0f, 90.0f);
			DeleteGraph(handle);
		}
		// 警戒度が100未満の場合、はてなマークを表示
		else
		{

		}*/
		/*
		// プレーヤーの座標と回転行列を取得
		auto player = world_->findActor("Player");
		Vector3 player_position = player->getPosition();							// プレーヤーの座標
		Matrix player_rotation = player->getRotation().NormalizeRotationMatrix();	// プレーヤーの回転行列
		// プレーヤーからのエネミーの方向のベクトル
		Vector3 player_to_enemy = enemy_.lock()->getPosition() - player_position;
		// プレーヤーとエネミーの外積
		Vector3 forward_cross_target = Vector3::Cross(player_rotation.Forward(), player_to_enemy);
		// プレーヤーとエネミーの内積
		float forward_dot_target = Vector3::Dot(player_rotation.Forward(), player_to_enemy);

		// エネミーがプレーヤーより後ろにいる場合、表示しない
		if (forward_dot_target <= 0.0f)	return;

		// 描画する座標を指定
		constexpr float upPower = 10.0f;
		auto drawPos = player_to_enemy + Vector3::Up * upPower;
		constexpr float size = 10.f;				// 表示のサイズ
		Vector2 origin = Vector2{ 0.5f, 0.0f };		// 画像の中心点

		int handle = MV1LoadTexture("res/Sprite/free/exclamation.png");

		DrawSprite3D(drawPos, size, handle, 255, 255, 255, 255, 0.0f, 0.0f, 90.0f);
		DeleteGraph(handle);
		*/
	});
}