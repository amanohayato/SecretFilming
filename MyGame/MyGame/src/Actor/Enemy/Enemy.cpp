#include "Enemy.h"
#include"../../Graphic/Model.h"

// テスト用エネミークラス
// 制作者：Ho Siu Ki（何兆祺）

// コンストラクタ
Enemy::Enemy(IWorld* world, const Vector3& position, int type, const IBodyPtr& body)
	: Actor(world, "Enemy", position, body), animation_(), chooser_(world, position, type)
{
	animation_.SetHandle(Model::GetInstance().GetHandle(MODEL_ID::MODEL_PLAYER));
	// change_state(EnemyState::Move);		// 状態を設定
	change_state(EnemyState::RandomEvent1);
}

// 初期化
void Enemy::initialize()
{
}

// 更新
void Enemy::update(float delta_time)
{
	animation_.Update(1.0f);	// アニメーションを更新

	// 状態に応じて処理を行う
	switch (state_)
	{
	case Enemy::EnemyState::Idle:
		idle(delta_time);
		break;
	case Enemy::EnemyState::Move:
		move(delta_time);
		break;
	case Enemy::EnemyState::Kouban:
		kouban(delta_time);
		break;
	case Enemy::EnemyState::Takoyakiya:
		takoyakiya(delta_time);
		break;
	case Enemy::EnemyState::Alley:
		alley(delta_time);
		break;
	case Enemy::EnemyState::Crossroad:
		crossroad(delta_time);
		break;
	case Enemy::EnemyState::VendingMachine:
		vending_machine(delta_time);
		break;
	case Enemy::EnemyState::SmokingArea:
		smoking_area(delta_time);
		break;
	case Enemy::EnemyState::Sakanaya:
		sakanaya(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent1:
		random_event1(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent2:
		random_event2(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent3:
		random_event3(delta_time);
		break;
	case Enemy::EnemyState::RandomEvent4:
		random_event4(delta_time);
		break;
	default:
		break;
	}
}

// 描画
void Enemy::draw() const
{
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f);
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
	body_->transform(getPose())->draw();
}

// 接触判定
void Enemy::onCollide(Actor & other)
{

}

// メッセージの受信
void Enemy::receiveMessage(EventMessage message, void * param)
{

}

// 状態の変更
void Enemy::change_state(EnemyState state)
{
	// エネミーの状態を変更
	state_ = state;
	// アニメーションを変更
	change_Animation(AnimConverter.at(state).animation, 0.0f, 1.0f, AnimConverter.at(state).is_loop);

	// 状態変化後の処理
	switch (state_)
	{
	case Enemy::EnemyState::Idle:
		timer_ = 10.0f;
		break;
	case Enemy::EnemyState::Move:
		chooser_.choose_goal();
		break;
	case Enemy::EnemyState::Kouban:
		break;
	case Enemy::EnemyState::Takoyakiya:
		break;
	case Enemy::EnemyState::Alley:
		break;
	case Enemy::EnemyState::Crossroad:
		break;
	case Enemy::EnemyState::VendingMachine:
		break;
	case Enemy::EnemyState::SmokingArea:
		break;
	case Enemy::EnemyState::Sakanaya:
		break;
	case Enemy::EnemyState::RandomEvent1:
		timer_ = 10.0f;
		break;
	case Enemy::EnemyState::RandomEvent2:
		break;
	case Enemy::EnemyState::RandomEvent3:
		break;
	case Enemy::EnemyState::RandomEvent4:
		break;
	default:
		break;
	}
}

// アニメーションの変更
void Enemy::change_Animation(EnemyAnimation animID, float anim_frame, float anim_speed, bool is_loop, float blend_rate)
{
	animation_.ChangeAnim((int)animID, anim_frame, anim_speed, is_loop);
}

// 静止状態の処理
void Enemy::idle(float delta_time)
{
	timer_ -= delta_time;

	if (timer_ <= 0.0f)
	{
		change_state(EnemyState::Move);
	}
}

// 移動状態の処理
void Enemy::move(float delta_time)
{
	float power = 3.0f;
	bool isEnd;

	Vector3 toTargetPosition = (chooser_(position_, isEnd) - position_).Normalize();//自身から次の地点へのベクトル
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*5.0f*power*power);
	position_ += rotation_.Forward()*0.3f*power;

	if (isEnd)
	{
		change_state(EnemyState::Idle);
	}
}

// 交番でのイベント
void Enemy::kouban(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// たこ焼き屋でのイベント
void Enemy::takoyakiya(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// 路地裏でのイベント
void Enemy::alley(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// 交差点でのイベント
void Enemy::crossroad(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// 自販機でのイベント
void Enemy::vending_machine(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// 喫煙所でのイベント
void Enemy::smoking_area(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// 魚屋でのイベント
void Enemy::sakanaya(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::Move);
	}
}

// ランダムイベント1
void Enemy::random_event1(float delta_time)
{
	timer_ -= delta_time;

	if (timer_ <= 0.0f) {
		change_state(EnemyState::RandomEvent2);
	}
}

// ランダムイベント2
void Enemy::random_event2(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::RandomEvent3);
	}
}

// ランダムイベント3
void Enemy::random_event3(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::RandomEvent4);
	}
}

// ランダムイベント4
void Enemy::random_event4(float delta_time)
{
	if (animation_.IsAnimEnd())
	{
		change_state(EnemyState::RandomEvent1);
	}
}