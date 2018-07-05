#include "EnemyCap.h"
#include"EnemyBase.h"
#include"../../Conv/DXConverter.h"

static const Vector3 GRAVITY_POWER{ 0.0f,-0.01f,0.0f };

EnemyCap::EnemyCap(IWorld* world, std::shared_ptr<EnemyBase> enemy):
	Actor(world,"Cap",Vector3::Zero),_target(enemy),_drawFunc([] {}),_state(State::wear)
{
}

void EnemyCap::initialize()
{
	_drawFunc = [] {};
}

void EnemyCap::update(float deltaTime)
{
	switch (_state)
	{
	case EnemyCap::State::wear:wear(deltaTime);
		break;
	case EnemyCap::State::fall:fall(deltaTime);
		break;
	case EnemyCap::State::stop:stop(deltaTime);
		break;
	case EnemyCap::State::pick:pick(deltaTime);
		break;
	default:
		break;
	}
}

void EnemyCap::draw() const
{
	if (!_target.lock()->isDraw_)return;
	_drawFunc();
}

void EnemyCap::beginfall(const Vector3& dir)
{
	_fallDir = dir;
	auto FrameIndex = MV1SearchFrame(_target.lock()->get_animation().getModelHandle(), "HEAD");
	auto FrameMatrix = MV1GetFrameLocalWorldMatrix(_target.lock()->get_animation().getModelHandle(), FrameIndex);
	position_ = DXConverter::GetInstance().ToMatrix(FrameMatrix).Translation();
	rotation_ = DXConverter::GetInstance().ToMatrix(FrameMatrix).RotationMatrix();
	_state = State::fall;
}

void EnemyCap::pickcap()
{
	_state = State::pick;
}

void EnemyCap::endfall()
{
	_state = State::wear;
}

void EnemyCap::wear(float deltaTime)
{
	_drawFunc = [&] {
		auto FrameIndex = MV1SearchFrame(_target.lock()->get_animation().getModelHandle(), "HEAD");
		auto FrameMatrix = MV1GetFrameLocalWorldMatrix(_target.lock()->get_animation().getModelHandle(), FrameIndex);
		Model::GetInstance().Draw(MODEL_ID::MODEL_ENEMY_CAP, DXConverter::GetInstance().ToMatrix(FrameMatrix));
	};
}

void EnemyCap::fall(float deltaTime)
{
	_fallDir += GRAVITY_POWER;
	_fallDir.y = max(_fallDir.y, -1.0f);

	position_ += _fallDir;

	if (world_->getFieldOnly()->getMesh().collide_line(position_+Vector3::Up*2.0f,position_)) {
		_state = State::stop;
	}

	_drawFunc = [&] {
		auto FrameIndex = MV1SearchFrame(_target.lock()->get_animation().getModelHandle(), "HEAD");
		auto FrameMatrix = MV1GetFrameLocalWorldMatrix(_target.lock()->get_animation().getModelHandle(), FrameIndex);
		Matrix mat=DXConverter::GetInstance().ToMatrix(FrameMatrix).RotationMatrix().Translation(position_);
		Model::GetInstance().Draw(MODEL_ID::MODEL_ENEMY_CAP, mat);
	};

}

void EnemyCap::stop(float deltaTime)
{
	_drawFunc = [&] {
		Model::GetInstance().Draw(MODEL_ID::MODEL_ENEMY_CAP, getPose());
	};

}

void EnemyCap::pick(float deltaTime)
{
	_drawFunc = [&] {
		auto FrameIndex = MV1SearchFrame(_target.lock()->get_animation().getModelHandle(), "Gray_Kyara:L_THUMB3");
		auto FrameMatrix = MV1GetFrameLocalWorldMatrix(_target.lock()->get_animation().getModelHandle(), FrameIndex);
		auto FrameIndexH = MV1SearchFrame(_target.lock()->get_animation().getModelHandle(), "HEAD");
		auto FrameMatrixH = MV1GetFrameLocalWorldMatrix(_target.lock()->get_animation().getModelHandle(), FrameIndexH);
		Matrix mat = DXConverter::GetInstance().ToMatrix(FrameMatrixH).RotationMatrix().Translation(DXConverter::GetInstance().ToMatrix(FrameMatrix).Translation());
		Model::GetInstance().Draw(MODEL_ID::MODEL_ENEMY_CAP, mat);

	
	};

}
