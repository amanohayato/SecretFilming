#include "EnemyBase.h"
#include "../../Graphic/Model.h"
#include "../../World/World.h"
#include "../../Field/WalkGraph.h"
#include "../../Scene/Manager/GameDataManager.h"
#include "../UIActor/AlertGauge.h"
#include "../../Graphic/AnimLoader.h"
#include "../EventActor/GameClearEvent/GameClearEvent.h"
#include "../EventActor/GameOverEvent/GameOverEvent.h"
#include "EnemyBarrier.h"
#include "../../Math/Random.h"
#include"../../Define.h"

// エネミーベースクラス
// 担当：Ho Siu Ki（何兆祺）

static constexpr float rotationPower = 30.0f;
static constexpr float arriveLength = 5.0f;
static constexpr int targetFrame = 2;
static constexpr int defaultScore = 20;
static constexpr int eyePolyIndexNum = 355;
//static int headPolyIndexNum = 716;

// コンストラクタ
EnemyBase::EnemyBase(IWorld* world, const Vector3& position, const IBodyPtr& body)
	: Actor(world, "Enemy", position, body), animation_(Model::GetInstance().GetHandle(MODEL_ID::MODEL_ENEMY))
{
#ifdef _DEBUG
	normal_speed_ = 1.5f;
	//normal_speed_ = 0.4f;
#else
	normal_speed_ = 0.4f;
#endif
	escape_speed_ = 1.5f;
}

EnemyBase::~EnemyBase()
{
	MV1TerminateReferenceMesh(animation_.getModelHandle(), targetFrame, TRUE);

}

// 初期化
void EnemyBase::initialize()
{
	player_ = world_->findActor("Player");
	world_->addActor(ActorGroup::UI_ACTOR, std::make_shared<AlertGauge>(world_, std::static_pointer_cast<EnemyBase>(shared_from_this())));

	auto cap = std::make_shared<EnemyCap>(world_, std::static_pointer_cast<EnemyBase>(shared_from_this()));
	cap_ = cap;
	addChild(cap);
	cap->initialize();

	event_points_.clear();
	event_points_ = world_->getEventList();

	eventManager_ = std::make_shared<RandomEventManager>(*world_);
	eventManager_->SetPosition(position_);

	//event_points_.sort([](EventPoint& e1, EventPoint& e2) {return e1.building_.lock()->getEvent() == EventType::EVENT_VENDING; });

	//for (auto& i : event_points_) {
	//	{
	//		if (i.building_.lock()->getEvent() == EventType::EVENT_MANHORdeddjnn)
	//			event_points_.push_front(i);
	//	}
	//}


	//マンホール用のやつ
	if (event_points_.front().building_.lock()->getEvent() == EventType::EVENT_MANHORU) {
		auto path1 = world_->getWalkMap().find_path(0, position_, event_points_.front().position_);
		auto path2 = world_->getWalkMap().find_path(0, position_, event_points_.front().position2_);
		path_ = GetNearPath(path1, path2);
	}
	else
		path_ = world_->getWalkMap().find_path(0, position_, event_points_.front().position_);
	//path_ = world_->getWalkMap().find_path(0, position_, world_->getWalkMap().getNode(0, goalNodeIndexNum).position);//クリア演出テスト用に追加
	//position_ = world_->getWalkMap().getNode(0, goalNodeIndexNum).position;
	MV1SetupReferenceMesh(animation_.getModelHandle(), targetFrame, TRUE);

	change_state(EnemyState::Move);
	//change_state(EnemyState::Idle);		// テスト用

	last_walk_path_ = [] {};

	set_look_back_time();		// 次の振り返るまでの時間を乱数で設定
}

// 更新
void EnemyBase::update(float delta_time)
{
	MV1RefreshReferenceMesh(animation_.getModelHandle(), targetFrame, TRUE);
	auto enemyMesh = MV1GetReferenceMesh(animation_.getModelHandle(), targetFrame, TRUE);
	auto em = enemyMesh.Polygons[eyePolyIndexNum];

	aware_up_rate_ = (viewing_distance_ - Vector3::Distance(getPosition(), player_position_))/(viewing_distance_/0.35f);
	aware_up_rate_ = MathHelper::Clamp(aware_up_rate_, 0.2f, 0.35f);

	//auto hm = enemyMesh.Polygons[headPolyIndexNum];

	//if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP)) {
	//	while (true)
	//	{
	//		headPolyIndexNum++;
	//		hm = enemyMesh.Polygons[headPolyIndexNum];
	//		Vector3 hpos = enemyMesh.Vertexs[hm.VIndex[0]].Position;
	//		if (hpos.y >= 14.0f) {
	//			break;
	//		}
	//	}
	//}	
	//if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN)) {
	//	while (true)
	//	{
	//		headPolyIndexNum--;
	//		hm = enemyMesh.Polygons[headPolyIndexNum];
	//		Vector3 hpos = enemyMesh.Vertexs[hm.VIndex[0]].Position;
	//		if (hpos.y >= 14.0f) {
	//			break;
	//		}
	//	}
	//}
	head_pos = enemyMesh.Vertexs[em.VIndex[0]].Position;
	head_vertex[0] = enemyMesh.Vertexs[em.VIndex[0]].Position;
	head_vertex[1] = enemyMesh.Vertexs[em.VIndex[1]].Position;
	head_vertex[2] = enemyMesh.Vertexs[em.VIndex[2]].Position;


	if (randomEventFlag_) eventManager_->Update();

	
	// ゴール判定
	if (state_ != EnemyState::Goal && event_points_.empty() && path_.empty())
	{
		change_state(EnemyState::Goal);
	}

	// イベント判定（停止状態に移行）
	if (state_ != EnemyState::Stop&&is_event_)
	{
		change_state(EnemyState::Stop);
	}

	animation_.update(0.5f);	// アニメーションを更新

	// 警戒度に関する処理
	awareness(delta_time);

	// 状態に応じて処理を行う
	switch (state_)
	{
	case EnemyBase::EnemyState::Idle:
		idle(delta_time);
		break;
	case EnemyBase::EnemyState::Move:
		move(delta_time);
		break;
	case EnemyBase::EnemyState::Escape:
		escape(delta_time);
		break;
	case EnemyBase::EnemyState::Goal:
		goal(delta_time);
		break;
	case EnemyBase::EnemyState::PoliceBox:
		police_box(delta_time);
		break;
	case EnemyBase::EnemyState::Takoyakiya:
		takoyakiya(delta_time);
		break;
	case EnemyBase::EnemyState::BackStreet1:
		back_street_1(delta_time);
		break;
	case EnemyBase::EnemyState::BackStreet2:
		back_street_2(delta_time);
		break;
	case EnemyBase::EnemyState::Junction:
		junction(delta_time);
		break;
	case EnemyBase::EnemyState::VendingMachine:
		vending_machine(delta_time);
		break;
	case EnemyBase::EnemyState::SmokingArea:
		smoking_area(delta_time);
		break;
	case EnemyBase::EnemyState::FishMonger:
		fish_monger(delta_time);
		break;
	case EnemyBase::EnemyState::RandomEvent1:
		random_event1(delta_time);
		break;
	case EnemyBase::EnemyState::RandomEvent2:
		random_event2(delta_time);
		break;
	case EnemyBase::EnemyState::RandomEvent3:
		random_event3(delta_time);
		break;
		//case EnemyBase::EnemyState::PreAction:
		//	pre_action(delta_time);
		//	break;
	case EnemyBase::EnemyState::Stop:
		stop(delta_time);
		break;
	case EnemyBase::EnemyState::DiscoveryStart:
		discoveryStart(delta_time);
		break;
	case EnemyBase::EnemyState::Discovery:
		discovery(delta_time);
		break;
	case EnemyBase::EnemyState::DiscoveryEnd:
		discoveryEnd(delta_time);
		break;
	case EnemyBase::EnemyState::Aware:
		aware(delta_time);
		break;
	case EnemyBase::EnemyState::LookBack:
		look_back(delta_time);
		break;
	case EnemyBase::EnemyState::ToPlayer:
		to_player(delta_time);
	default:
		break;
	}

	// デバッグログを表示（プレーヤーが見えるかどうか）
	//OutputDebugString(("プレーヤーが見える：" + std::to_string(can_see_player()) + "\n").c_str());

	// プレーヤーの座標を更新
	player_position_ = player_.lock()->getPosition();
}

// 描画
void EnemyBase::draw() const
{
	Vector3 drawPosition = position_ + Vector3::Down * body_->length() * 0.5f - Vector3(0.0f, 2.f, 0.0f);
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down * body_->length() * 0.5f - Vector3(0.0f, 2.f, 0.0f)) * rotation_ * Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
	body_->transform(getPose())->draw();
	eventManager_->Draw();
	eventManager_->DebugDraw();
}

void EnemyBase::shadowDraw() const
{
	Vector3 drawPosition = position_ + Vector3::Down * body_->length() * 0.5f - Vector3(0.0f, 2.f, 0.0f);
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down * body_->length() * 0.5f - Vector3(0.0f, 2.f, 0.0f)) * rotation_ * Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));
}

// 接触判定
void EnemyBase::onCollide(Actor& other)
{

}

// メッセージの受信
void EnemyBase::receiveMessage(EventMessage message, void * param)
{
	switch (message)
	{
	case EventMessage::Hit_Car:
		break;
	case EventMessage::Hit_Bullet:
		break;
	case EventMessage::Hide_Object:
		break;
	case EventMessage::Hide_InCamera:
		break;
	case EventMessage::Score_None:
		score_ = 0;
		break;
	case EventMessage::Aware_None:
		awareness_ = 0.1f;
		break;
	default:
		break;
	}
}

// イベントの取得
void EnemyBase::get_event()
{
	if (event_points_.empty())
	{
		return;
	}

	auto event_type = event_points_.front().building_.lock()->getEvent();		// 建物からイベントの種類を取得

	// イベントを取得できなければ、移動状態に戻る
	if (event_type == EventType::EVENT_NULL)
	{
		change_state(EnemyState::Move);
	}

	// 建物にイベント発生を要請
	event_points_.front().building_.lock()->callEvent();

	// イベントの種類によって、処理に入る
	switch (event_type)
	{
	case EventType::EVENT_POLICE:
		//change_state_ = [&] {change_state(EnemyState::PoliceBox); };
		change_state(EnemyState::PoliceBox);
		break;
	case EventType::EVENT_TAKOYAKIYA:
		//change_state_ = [&] {change_state(EnemyState::Takoyakiya); };
		change_state(EnemyState::Takoyakiya);
		break;
	case EventType::EVENT_BACKSTREET_RATI:
		//change_state_ = [&] {change_state(EnemyState::BackStreet1); };
		change_state(EnemyState::BackStreet1);
		break;
	case EventType::EVENT_BACKSTREET_KAIWA:
		//change_state_ = [&] {change_state(EnemyState::BackStreet2); };
		change_state(EnemyState::BackStreet2);
		break;
	case EventType::EVENT_JUNCTION:
		//change_state_ = [&] {change_state(EnemyState::Junction); };
		change_state(EnemyState::Junction);
		break;
	case EventType::EVENT_VENDING:
		//change_state_ = [&] {change_state(EnemyState::VendingMachine); };
		change_state(EnemyState::VendingMachine);
		break;
	case EventType::EVENT_SMOKING:
		//change_state_ = [&] {change_state(EnemyState::SmokingArea); };
		change_state(EnemyState::SmokingArea);
		break;
	case EventType::EVENT_FISHSTORE:
		//change_state_ = [&] {change_state(EnemyState::FishMonger); };
		change_state(EnemyState::FishMonger);
		break;
	default:
		//change_state_ = [&] {change_state(EnemyState::Move); };
		change_state(EnemyState::Move);
		break;
	}
	//change_state(EnemyState::PreAction);
}

// 回転行列の取得
Matrix& EnemyBase::get_rotation()
{
	return rotation_;
}

// アニメーションクラスの取得
AnimationOutSide& EnemyBase::get_animation()
{
	return animation_;
}

// イベントフラグの設定
void EnemyBase::set_is_event(bool is_event)
{
	is_event_ = is_event;
}

bool EnemyBase::get_is_event() const
{
	return is_event_;
}

float EnemyBase::get_awareness() const
{
	return awareness_;
}

void EnemyBase::set_awareness(const float &awareness)
{
	awareness_ = awareness;
}

std::string EnemyBase::get_ui_target() const
{
	return is_event_ ? "None" : "AlertGauge";

}

int EnemyBase::getBaseScore() const
{
	return score_;
}

void EnemyBase::setBaseScore(int score)
{
	score_ = score;
}

Vector3 EnemyBase::getHeadPos() const
{
	return head_pos;
}

std::array<Vector3, 3> EnemyBase::getHeadVertex() const
{
	return head_vertex;
}

void EnemyBase::on_Barrier(ActorPtr target, ActorPtr enemy, bool isStop)
{
	if (world_->findActor("EnemyBarrier") != nullptr) {
		world_->findActor("EnemyBarrier")->dead();
	}
	// バリアを生成
	std::shared_ptr<EnemyBarrier> barrier = std::make_shared<EnemyBarrier>(target, enemy, position_, rotation_, isStop);
	world_->addActor(ActorGroup::ENEMY_ACTOR, barrier);
}

bool EnemyBase::isPathEnd() const
{
	return path_.empty();
}

std::vector<Vector3> EnemyBase::GetNearPath(const std::vector<Vector3>& p1, const std::vector<Vector3>& p2)
{
	float dis1 = 0;
	float dis2 = 0;
	for (int i = 1; i < p1.size(); i++) {
		dis1 += Vector3::Distance(p1[i], p1[i - 1]);
	}
	for (int i = 1; i < p2.size(); i++) {
		dis2 += Vector3::Distance(p2[i], p2[i - 1]);
	}
	if (dis1 > dis2)return p2;
	else return p1;
}

std::vector<Vector3> EnemyBase::getPath() const
{
	return path_;
}

void EnemyBase::setNextEvent()
{
	setNextEventPath();
}

void EnemyBase::fallcap()
{
	cap_.lock()->beginfall(rotation_.Forward()*0.1f + rotation_.Up()*0.1f + rotation_.Right()*0.04f);
}

void EnemyBase::pickcap()
{
	cap_.lock()->pickcap();
}

void EnemyBase::wearcap()
{
	cap_.lock()->endfall();
}

std::list<EventPoint>& EnemyBase::GetEventPoints()
{
	return event_points_;
}

// 状態の変更
void EnemyBase::change_state(EnemyState state)
{
	if (state_ == state) return;
	if (state_ == EnemyState::Discovery && state == EnemyState::DiscoveryStart)return;
	
	if(state_==EnemyState::ToPlayer)setNextEventPath_Reset();

	// エネミーの状態を変更
	state_ = state;

	// アニメーションを変更
	change_animation(AnimConverter.at(state).animation, 0.0f, 1.0f, AnimConverter.at(state).is_loop);

	//基本的にはスコアは0
	score_ = 0;

	// 状態変化後の処理
	switch (state_)
	{
	case EnemyBase::EnemyState::Idle:
		timer_ = 10.0f;
		break;
	case EnemyBase::EnemyState::Move:
		break;
	case EnemyBase::EnemyState::Escape:
		GameDataManager::getInstance().setEnemyEscape(true);
		setText("Aware/escape.txt");
		//escape_timer_ = 10.0f;
		break;
	case EnemyBase::EnemyState::Goal:
		event_points_.clear();
		goal_timer_ = goal_time_;
		awareness_ = 0;
		world_->findActor("Player")->receiveMessage(EventMessage::Stop_Player);
		break;
	case EnemyBase::EnemyState::PoliceBox:
	case EnemyBase::EnemyState::Takoyakiya:
	case EnemyBase::EnemyState::BackStreet1:
	case EnemyBase::EnemyState::BackStreet2:
	case EnemyBase::EnemyState::Junction:
	case EnemyBase::EnemyState::VendingMachine:
	case EnemyBase::EnemyState::SmokingArea:
	case EnemyBase::EnemyState::FishMonger:
	case EnemyBase::EnemyState::RandomEvent1:
	case EnemyBase::EnemyState::RandomEvent2:
	case EnemyBase::EnemyState::RandomEvent3:
		//score_ = defaultScore;
		break;
	case EnemyBase::EnemyState::DiscoveryStart:
		aware_state_timer_ = 6.5f;
		is_aware_ = true;
		if (displayWarningText_) setText("Aware/in_warning1.txt");

		break;
	case EnemyBase::EnemyState::Discovery:
		break;
	case EnemyBase::EnemyState::DiscoveryEnd:
		if (displayWarningText_) setText("Aware/out_warning1.txt");
		break;
	case EnemyBase::EnemyState::Aware:
		break;
	case EnemyBase::EnemyState::Stop:
		//score_ = defaultScore;
		break;
	case EnemyBase::EnemyState::LookBack:
		set_look_back_time();
		break;
	default:
		break;
	}
}

// アニメーションの変更
void EnemyBase::change_animation(EnemyAnimation animID, float anim_frame, float anim_speed, bool is_loop, float blend_rate)
{
	//追加
	if (!is_event_)
		animation_.changeAnimation(AnimLoader::getInstance().getAnimKey(MODEL_ID::MODEL_ENEMY, (int)animID), is_loop, anim_speed, blend_rate, anim_frame);
}

// 静止状態の処理
void EnemyBase::idle(float delta_time)
{

}

// 移動状態の処理
void EnemyBase::move(float delta_time)
{
	// イベント処理
	if (path_.empty())
	{
		//get_event();	// イベントを取得
		last_walk_path_();
		//if (event_points_.size() <= 1)setNextEventPath();
		return;
	}

	// 一定時間ごと振り返る
	if (look_back_timer_ <= 0.0f)
	{
		change_state(EnemyState::LookBack);
	}

	Vector3 next_destination = path_.back();	// 次の目的地を指定

	// 移動処理
	Vector3 target_position = next_destination - position_;
	target_position = target_position.Normalize();
	Vector3 check_is_left_cross_vector = Vector3::Cross(rotation_.Forward(), target_position);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), check_is_left_cross_vector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot * normal_speed_*rotationPower);
	position_ += rotation_.Forward() * normal_speed_;

	DebugDraw::DebugDrawLine3D(position_, path_.back(), GetColor(0, 255, 0));
	for (auto p : path_) {
		DebugDraw::DebugDrawSphere3D(p, 3, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), TRUE);
	}
	DebugDraw::DebugDrawSphere3D(world_->getWalkMap().getNode(0, goalNodeIndex).position, 6, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), TRUE);

	if (Vector2::Distance(Vector2{ position_.x,position_.z }, Vector2{ next_destination.x,next_destination.z }) <= arriveLength)
		//if (Vector3::Distance(position_, next_destination) <= arriveLength)
	{
		path_.pop_back();
	}

	// 振り向くタイマーを減算
	look_back_timer_ -= delta_time;
}

// 逃走状態の処理
void EnemyBase::escape(float delta_time)
{
	// 逃走時間タイマーを減算
	escape_timer_ -= delta_time;

	// 逃走時間タイマーが0になると、一回後ろに振り向く（後に移動状態に戻る）
	if (escape_timer_ <= 0.0f)
	{
		awareness_ = 0.0f;
		escape_timer_ = 10.0f;
		GameDataManager::getInstance().setEnemyEscape(false);
		// change_state(EnemyState::Move);
		change_state(EnemyState::LookBack);
	}
	// テスト用
	if (path_.empty())
	{
		setNextEventPath();
		return;
	}

	Vector3 next_destination = path_.back();	// 次の目的地を指定

	// 移動処理
	Vector3 target_position = next_destination - position_;
	target_position = target_position.Normalize();
	Vector3 check_is_left_cross_vector = Vector3::Cross(rotation_.Forward(), target_position);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), check_is_left_cross_vector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot * escape_speed_*rotationPower);
	position_ += rotation_.Forward() * escape_speed_;

	if (Vector2::Distance(Vector2{ position_.x,position_.z }, Vector2{ next_destination.x,next_destination.z }) <= arriveLength)
		//if (Vector3::Distance(position_, next_destination) <= arriveLength)
	{
		path_.pop_back();
	}
}

// ゴールイベント処理
void EnemyBase::goal(float delta_time)
{
	if (is_performance_ == false)
	{
		GameDataManager::getInstance().setGameStop(true);
		is_performance_ = true;
		return;
	}

	if (goal_timer_ == goal_time_ && GameDataManager::getInstance().getScore() >= 100)
	{
		goal_time_ = 5.0f;
		goal_timer_ = goal_time_;
		//スコアがクリア条件に達していたらクリアイベント発生
		world_->addActor(ActorGroup::EVENT_ACTOR, std::make_shared<GameClearEvent>(world_, goal_timer_, goal_time_, std::static_pointer_cast<EnemyBase>(shared_from_this())));
	}
	else if (goal_timer_ == goal_time_ && GameDataManager::getInstance().getScore() < 100)
	{
		goal_time_ = 10.0f;
		goal_timer_ = goal_time_;
		world_->addActor(ActorGroup::EVENT_ACTOR, std::make_shared<GameOverEvent>(world_, goal_timer_, goal_time_, std::static_pointer_cast<EnemyBase>(shared_from_this())));
	}
	goal_timer_ -= delta_time;

	// アニメーション再生後、ゲームオーバー判定を出す
	if (goal_timer_ <= 0.0f && animation_.isEnd())
	{
		is_goal_ = true;
		GameDataManager::getInstance().setEnemyGoal(is_goal_);
	}

}

// 停止状態の処理
void EnemyBase::stop(float delta_time)
{
	if (is_event_ == false)
	{
		change_state(EnemyState::Move);
	}
}

void EnemyBase::discoveryStart(float delta_time)
{
	if (animation_.isEnd()) {
		change_state(EnemyState::Discovery);
		return;
	}
	Vector3 dir = world_->findActor("Player")->getPosition() - position_;
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);
}

void EnemyBase::discovery(float delta_time)
{
	is_aware_ = true;
	if (awareness_timer_ <= 0.0f) {
		if(animation_.isEnd()) change_state(EnemyState::DiscoveryEnd);
		return;
	}
	if (!can_see_player()) return;
	Vector3 dir = world_->findActor("Player")->getPosition() - position_;
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);
}

void EnemyBase::discoveryEnd(float delta_time)
{
	if (animation_.isEnd()) {
		change_state(EnemyState::Move);
	}
}

// 警戒状態の処理
void EnemyBase::aware(float delta_time)
{
	// 状態タイマーを減算
	aware_state_timer_ -= delta_time;

	// プレーヤーを発見した方向に向ける
	float angle = player_position_angle();
	rotation_.CreateRotationY(angle);
	rotation_.NormalizeRotationMatrix();

	// 状態タイマーが0になると、移動状態に戻る
	if (aware_state_timer_ <= 0.0f)
	{
		if (!can_see_player())
		{
			change_state(EnemyState::Move);
		}
		else
		{
			aware_state_timer_ = 6.5f;
			aware(delta_time);
		}
	}
}

// 振り返る処理
void EnemyBase::look_back(float delta_time)
{
	// モーションが終わったら、移動処理に戻る
	if (animation_.isEnd())
	{
		constexpr float lookLength = 150.0f;
		if (Vector3::Distance(player_.lock()->getPosition(), position_) <= lookLength &&
			!world_->hitToLine(position_, player_.lock()->getPosition())) {
			change_state(EnemyState::ToPlayer);
			return;
		}
		change_state(EnemyState::Move);
	}
}

// 振り返る時間の設定
void EnemyBase::set_look_back_time()
{
	look_back_timer_ = Random::GetInstance().Range(20.0f, 40.0f);
}

void EnemyBase::to_player(float deltaTime)
{
	if (world_->hitToLine(position_, player_.lock()->getPosition())) {
		change_state(EnemyState::Move);
		return;
	}
	// プレーヤーが回避態勢を取っている場合 -> 見えない
	if (player_.lock()->isAction()) {
		change_state(EnemyState::Move);
		return;
	}

	constexpr float topRotatePower = 2.0f;
	Vector3 target_position = player_.lock()->getPosition() - position_;
	target_position = target_position.Normalize();
	Vector3 check_is_left_cross_vector = Vector3::Cross(rotation_.Forward(), target_position);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), check_is_left_cross_vector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot * escape_speed_*rotationPower*topRotatePower);
	position_ += rotation_.Forward() * normal_speed_;

}

// プレーヤーが見える距離内にいるか
bool EnemyBase::is_player_in_viewing_distance()
{
	// 自身からプレーヤーまでの距離
	float distance_to_player = Vector3::Distance(player_.lock()->getPosition(), position_);

	// デバッグログを表示（プレーヤーとの距離）
	//OutputDebugString(("プレーヤーとの距離：" + std::to_string(distance_to_player) + "\n").c_str());

	// プレーヤーが見える距離内にいるかどうかを返却
	return (distance_to_player <= viewing_distance_);
}

// プレーヤーが見える視野角内にいるか
bool EnemyBase::is_player_in_viewing_angle()
{
	// 自分からプレーヤーへの方向ベクトル
	Vector3 direction_to_player = player_.lock()->getPosition() - position_;

	//モデルのアニメーションに連動して視界を変更する
	//使用するポリゴンのインデックス番号は、モデルデータ.mv1から調べて使う

	auto enemyMesh = MV1GetReferenceMesh(animation_.getModelHandle(), targetFrame, TRUE);

	/*
	for (int i = 0; i < 260; i++)
	{

		auto em = enemyMesh.Polygons[eyePolyIndexNum + test_i];
		if (InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::A)) {
			test_i = 988;
			while (true) {
				test_i++;
				em = enemyMesh.Polygons[eyePolyIndexNum + test_i];
				auto polyV0 = enemyMesh.Vertexs[em.VIndex[0]].Position;
				if (polyV0.y >= 12.0f)return false;
			}
		}
		if(InputChecker::GetInstance().KeyTriggerDown(InputChecker::Input_Key::B))test_i=1816;

		auto polyV0 = enemyMesh.Vertexs[em.VIndex[0]].Position;
		auto polyV1 = enemyMesh.Vertexs[em.VIndex[1]].Position;
		auto polyV2 = enemyMesh.Vertexs[em.VIndex[2]].Position;

		Vector3 polyNormal = Vector3::Cross(polyV1 - polyV0, polyV2 - polyV1).Normalize();

		DrawLine3D(polyV0, polyV0 + polyNormal * 1000.0f, GetColor(255, 0, 0));
	}
	*/

	auto em = enemyMesh.Polygons[eyePolyIndexNum];

	auto polyV0 = enemyMesh.Vertexs[em.VIndex[0]].Position;
	auto polyV1 = enemyMesh.Vertexs[em.VIndex[1]].Position;
	auto polyV2 = enemyMesh.Vertexs[em.VIndex[2]].Position;
	head_pos = polyV0;//頭座標の更新
	Vector3 polyNormal = Vector3::Cross(polyV1 - polyV0, polyV2 - polyV1).Normalize();
	//目のポリゴンの前向きベクトルを使って視界を調べる
	float angle_to_player = Vector3::Angle(polyNormal, direction_to_player);

	DebugDraw::DebugDrawLine3D(position_, position_ + polyNormal * 1000.0f, GetColor(255, 0, 0));

	// 自分の正面向きベクトルとプレーヤーへの方向ベクトルの差分角度
	//float angle_to_player = Vector3::Angle(rotation_.Forward(), direction_to_player);

	// デバッグログを表示（プレーヤーとの距離）
	//OutputDebugString(("プレーヤーからの角度：" + std::to_string(MathHelper::Abs(angle_to_player)) + "\n").c_str());

	// プレーヤーが見える視野角の範囲内にいるかどうかを返却
	return (MathHelper::Abs(angle_to_player) <= viewing_angle_);
}

// プレーヤーが見えるか
bool EnemyBase::can_see_player()
{
	/*
	float test = 0;
	OutputDebugString(("プレーヤーが見える：" + std::to_string(test) + "\n").c_str());

	return false;
	*/

	// 見える距離内にプレーヤーがいない場合 -> 見えない
	if (!is_player_in_viewing_distance())	return false;

	// 見える角度内にプレーヤーがいない場合 -> 見えない
	if (!is_player_in_viewing_angle()) return false;

	// プレーヤーが回避態勢を取っている場合 -> 見えない
	if (player_.lock()->isAction())	return false;

	if (world_->hitToLine(player_.lock()->getPosition(), position_)) return false;

	// ここまで到達したら、見えるということ
	return true;
}

// プレーヤー方向の角度を求める
float EnemyBase::player_position_angle() const
{
	// 自分からプレーヤーへの方向ベクトル
	Vector3 direction_to_player = player_position_ - position_;

	// 自分の正面向きベクトルとプレーヤーへの方向ベクトルの差分角度
	float angle_to_player = Vector3::Angle(rotation_.Forward(), direction_to_player);

	return angle_to_player;
}

// 次の目的地への経路探索
void EnemyBase::next_destinstion()
{

}

// 警戒度処理
void EnemyBase::awareness(float delta_time)
{
	if (state_ == EnemyState::Goal)	return;		// ゴールにいる場合は処理しない
	if (awareness_ <= 0.0f)	is_aware_ = false;	// 警戒度は0以下の場合、警戒判定をfalseにする

	// 警戒維持時間減算
	awareness_timer_ -= delta_time;
	awareness_timer_ = MathHelper::Clamp(awareness_timer_, 0.0f, 10.0f);
	awareness_ = MathHelper::Clamp(awareness_, 0.0f, 100.0f);

	// プレーヤー未発見の場合、警戒ゲージが減少（逃走状態は減少しない、状態終了時に0に戻る）
	if (!can_see_player() && awareness_timer_ <= 0.0f && state_ != EnemyState::Escape)
	{
		awareness_ -= aware_down_rate_;
	}

	// プレーヤーを発見している場合、警戒モーションを再生し、警戒ゲージを加算
	if (can_see_player())
	{
		// 未発見状態であれば
		if (!is_aware_)
		{
			if (state_ != EnemyState::Escape&&state_ != EnemyState::DiscoveryStart && !is_event_)change_state(EnemyState::DiscoveryStart);
		}
		awareness_ += aware_up_rate_;

		// 6.5秒間警戒状態を維持
		awareness_timer_ = 6.5f;
	}
	else {
		is_aware_ = false;
	}

	// 警戒度が0より高い場合、警戒ゲージを表示
	if (awareness_ > 0.0f)
	{
		show_awareness();
	}

	// 警戒度が100以上越えると、逃走状態に移行
	if (state_ != EnemyState::Escape && !is_event_&&awareness_ >= 100.0f)
	{
		GameDataManager::getInstance().addEscapeCount();
		change_state(EnemyState::Escape);
	}
}

// 警戒ゲージの表示
void EnemyBase::show_awareness()
{

}

// 交番でのイベント処理
void EnemyBase::police_box(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// たこ焼き屋でのイベント処理
void EnemyBase::takoyakiya(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// 路地裏でのイベント1処理
void EnemyBase::back_street_1(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// 路地裏でのイベント2処理
void EnemyBase::back_street_2(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// 交差点でのイベント処理
void EnemyBase::junction(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// 自販機でのイベント処理
void EnemyBase::vending_machine(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// 喫煙所でのイベント処理
void EnemyBase::smoking_area(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// 魚屋でのイベント処理
void EnemyBase::fish_monger(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// ランダムイベント1処理
void EnemyBase::random_event1(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// ランダムイベント2処理
void EnemyBase::random_event2(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

// ランダムイベント3処理
void EnemyBase::random_event3(float delta_time)
{
	/*
	if (animation_.isEnd())
	{
		change_state(EnemyState::Move);
	}
	*/
}

//void EnemyBase::pre_action(float delta_time)
//{
//	change_state_();
//}

void EnemyBase::setNextEventPath()
{
	//空になる状態なら
	if (event_points_.size() <= 1) {
		Vector3 pos = world_->getWalkMap().getNode(0, goalNodeIndex).position;
		if (Vector2::Distance(Vector2{ position_.x,position_.z }, Vector2{ pos.x,pos.z }) <= arriveLength) {
			change_state(EnemyState::Goal);
		}
		else {
			last_walk_path_ = [&, pos] {
				if (Vector2::Distance(Vector2{ position_.x,position_.z }, Vector2{ pos.x,pos.z }) <= arriveLength) {
					change_state(EnemyState::Goal);
				}
			};
			event_points_.clear();
			path_ = world_->getWalkMap().find_path(0, position_, world_->getWalkMap().getNode(0, goalNodeIndex).position);
		}
		return;
	}
	event_points_.pop_front();

	//マンホール用のやつ
	if (event_points_.front().building_.lock()->getEvent() == EventType::EVENT_MANHORU) {
		auto path1 = world_->getWalkMap().find_path(0, position_, event_points_.front().position_);
		auto path2 = world_->getWalkMap().find_path(0, position_, event_points_.front().position2_);
		path_ = GetNearPath(path1, path2);
	}
	else
		path_ = world_->getWalkMap().find_path(0, position_, event_points_.front().position_);
	//path_ = world_->getWalkMap().find_path(0, position_, world_->getWalkMap().getNode(0, goalNodeIndexNum).position);//クリア演出テスト用に追加

}

void EnemyBase::setNextEventPath_Reset()
{
	if (path_.empty())return;
	auto path = world_->getWalkMap().find_path(0, position_, path_.back());

	path_.insert(path_.end(), path.begin(), path.end());
}

void EnemyBase::setText(const std::string & text)
{
	if (!_text.expired())_text.lock()->dead();
	auto txtPtr = std::make_shared<TextActor>(world_);
	_text = txtPtr;
	world_->addActor(ActorGroup::UI_ACTOR, txtPtr);
	txtPtr->add(text);
}
