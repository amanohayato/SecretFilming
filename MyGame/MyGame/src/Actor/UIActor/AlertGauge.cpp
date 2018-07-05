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
	// �s�N�Z���V�F�[�_�[�p�̒萔�o�b�t�@���쐬
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
	// �x���x�ɉ����āA�S���𗬂��iHo Siu Ki�̒ǉ��A2018-5-29�j
	if (target_.expired())	return;

	addSign = 1.0f;
	// �x���x��0�ɂȂ�ƁA�S���𗬂��Ȃ�
	if (target_.lock()->get_awareness() <= 0.0f)
	{
		//drawRate_ = 0.0f;
		addSign = -1.0f;
	}
	// �x���x��30�ȏ�ɂȂ�ƁA�S��������n�߂�
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

		// �Q�[�W�o���̉��o��ǉ��iHo Siu Ki�̒ǉ��A2018-5-29�j
		constexpr float upPower = 10.0f;
		auto drawPos = target_.lock()->getPosition() + Vector3::Up*upPower;
		constexpr float size = 10.f;
		float drawSize = MathHelper::Lerp(defaultSize, size, drawRate_);
		Vector2 origin = Vector2{ 0.5f, 0.0f };

		// �x���x��100�𒴂����ꍇ�A�r�b�N���}�[�N��\���iHo Siu Ki�̒ǉ��A2018-5-22�j
		if (target_.lock()->get_awareness() >= 100.0f)
		{
			float excRate = MathHelper::Clamp(excRate_ - exclamDrawCount, 0.0f, 1.0f);
			blendrate = (int)MathHelper::Lerp(255.0f, 0.0f, excRate);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, blendrate);
			drawSize = MathHelper::Lerp(size, defaultSize, excRate);
			Model::GetInstance().Draw2D(MODEL_ID::SPRITE_EXCLAMATION, drawPos, 0, drawSize, origin, angle_);

		}
		// �x���x��100�����̏ꍇ�A�͂Ăȃ}�[�N��\��
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
		// �`����@��ύX�iHo Siu Ki�̕ύX�A2018-5-29�j
		if (enemy_.expired())	return;							// �G�l�~�[�𑶍݂��Ȃ��ꍇ�A�������Ȃ�

		if (enemy_.lock()->get_awareness() <= 0.0f)	return;		// �x���x��0�̏ꍇ�A�������Ȃ�
		*/
		// �`�悷����W���w��
		/*
		constexpr float upPower = 10.0f;
		auto drawPos = enemy_.lock()->getPosition() + Vector3::Up * upPower;
		constexpr float size = 10.f;				// �\���̃T�C�Y
		Vector2 origin = Vector2{ 0.5f, 0.0f };		// �摜�̒��S�_

		int handle = MV1LoadTexture("res/Sprite/free/exclamation.png");
		*/
		// �x���x��100�𒴂����ꍇ�A�r�b�N���}�[�N��\��
		/*if (enemy_.lock()->get_awareness() >= 100.0f)
		{
			DrawSprite3D(drawPos, size, handle, 255, 255, 255, 255, 0.0f, 0.0f, 90.0f);
			DeleteGraph(handle);
		}
		// �x���x��100�����̏ꍇ�A�͂Ăȃ}�[�N��\��
		else
		{

		}*/
		/*
		// �v���[���[�̍��W�Ɖ�]�s����擾
		auto player = world_->findActor("Player");
		Vector3 player_position = player->getPosition();							// �v���[���[�̍��W
		Matrix player_rotation = player->getRotation().NormalizeRotationMatrix();	// �v���[���[�̉�]�s��
		// �v���[���[����̃G�l�~�[�̕����̃x�N�g��
		Vector3 player_to_enemy = enemy_.lock()->getPosition() - player_position;
		// �v���[���[�ƃG�l�~�[�̊O��
		Vector3 forward_cross_target = Vector3::Cross(player_rotation.Forward(), player_to_enemy);
		// �v���[���[�ƃG�l�~�[�̓���
		float forward_dot_target = Vector3::Dot(player_rotation.Forward(), player_to_enemy);

		// �G�l�~�[���v���[���[�����ɂ���ꍇ�A�\�����Ȃ�
		if (forward_dot_target <= 0.0f)	return;

		// �`�悷����W���w��
		constexpr float upPower = 10.0f;
		auto drawPos = player_to_enemy + Vector3::Up * upPower;
		constexpr float size = 10.f;				// �\���̃T�C�Y
		Vector2 origin = Vector2{ 0.5f, 0.0f };		// �摜�̒��S�_

		int handle = MV1LoadTexture("res/Sprite/free/exclamation.png");

		DrawSprite3D(drawPos, size, handle, 255, 255, 255, 255, 0.0f, 0.0f, 90.0f);
		DeleteGraph(handle);
		*/
	});
}