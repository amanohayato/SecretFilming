#include "Citizen.h"
#include"../../Graphic/Model.h"
#include"../../Graphic/DebugDraw.h"
#include"../../Field/WalkGraph.h"
#include"WalkPathReader.h"
#include"../../Scene/Manager/GameDataManager.h"
#include "../../Graphic/AnimLoader.h"
#include "../Enemy/EnemyBase.h"
#include"../Player/Player.h"



static constexpr float FOV = 30.0f;
static constexpr float MAX_AVOID_SPACE = 33.0f;
Citizen::Citizen(IWorld * world, MODEL_ID id,int type, const IBodyPtr & body):
	Actor(world,"Citizen",Vector3::Zero,body), animation_(Model::GetInstance().GetHandle(id)),modelid_(id),state_(State::Idle), type_(type)
	
{
	roadway_.load("res/Data/roadway.csv");
	crosswalk_.load("res/Data/citizencrosswalk.csv");
}

void Citizen::initialize()
{
	change_State(State::Walk);
	setPath();
}

void Citizen::update(float deltaTime)
{
	//プレイヤーのポジションを取得
	playerpos_ = world_->findActor("Player")->getPosition();
	//前回のフレームのポジションを記憶する
	beforpos_ = position_;
	//歩行者信号の状態の取得
	signal_ = GameDataManager::getInstance().getCitizenSignal();
	//アニメーションの更新
	animation_.update(MathHelper::Sign(deltaTime)*0.5f);
	switch (state_)
	{
	case Citizen::State::Idle:
		idle(deltaTime);
		break;
	case Citizen::State::Walk:
		walk(deltaTime);
		break;
	case Citizen::State::Down:
		down(deltaTime);
		break;
	case Citizen::State::Jump:
		jump(deltaTime);
		break;
	case Citizen::State::Dash:
		dash(deltaTime);
		break;
	case Citizen::State::Surprised:
		surprised(deltaTime);
		break;
	}
	//車道の処理
	roadway();

	switch (state_)
	{
	case Citizen::State::Jump:
		return;
		break;
	case Citizen::State::Dash:
		return;
		break;
	case Citizen::State::Surprised:
		return;
	case Citizen::State::Down:
		return;
		break;
	}

	// 敵の宇宙人を取得
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	//点数が入る状態を取得
	int score = std::static_pointer_cast<EnemyBase>(enemy)->getBaseScore();
	enemypos_ = enemy->getPosition();
	//エネミーとの距離が一定未満でエネミーがスコア獲得可能状態であればびっくり状態に移行する
	if (score != 0 && position_.Distance(position_, enemypos_) < enemy_destance_)//enemy_destance_ //test用1500
	{
		//change_State(State::Dash);
		change_State(State::Surprised);
	}
	/*
	if (type_ != 2)return;
	DrawFormatString(500, 550, GetColor(255, 255, 255), "%f", position_.x);
	DrawFormatString(500, 570, GetColor(255, 255, 255), "%f", position_.z);
	*/
}

void Citizen::draw() const
{
	//描画位置を合わせる(最後のVector3はモデル自身のズレ)
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));//*Matrix::CreateScale(Vector3{ 1.0f, 1.0f, 1.0f })
	//当たり判定の描画
	//body_->transform(getPose())->draw();
	//目的地のデバック表示
	for (auto& i : path_) {
		DebugDraw::DebugDrawSphere3D(i, 3.f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	}
	//ダッシュ状態のビックリマークの描画
	if (state_ == State::Dash)
	{
		auto currentstate = std::static_pointer_cast<Player>(world_->findActor("Player"))->getStateType();
		if (currentstate == Player_State_ID::MapApp || currentstate == Player_State_ID::SetUp)return;
		Vector3 drawPos = position_;
		drawPos.y = 19.0f;
		Vector2 origin = Vector2{ 0.5f, 0.0f };
		Model::GetInstance().Draw2D(MODEL_ID::SPRITE_EXCLAMATION, drawPos, 0, 10, origin, 0);
	}

	
	
}
void Citizen::shadowDraw() const
{
	Vector3 drawPosition = position_ + Vector3::Down*body_->length()*0.5f;
	//前後を合わせる
	animation_.Draw(Matrix(Matrix::Identity).Translation(Vector3::Down*body_->length()*0.5f - Vector3(0.0f, 2.f, 0.0f))*rotation_*Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f).Translation(position_));//*Matrix::CreateScale(Vector3{ 1.0f, 1.0f, 1.0f })
}

void Citizen::end()
{
}

void Citizen::onCollide(Actor & other)
{
	Vector3 hitdir = (other.getPosition() - position_);
	other.receiveMessage(EventMessage::Hit_Citizen, (void*)&hitdir);
}

void Citizen::receiveMessage(EventMessage message, void * param)
{
	
	if (message == EventMessage::Hit_Player || message == EventMessage::Hit_Enemy)
	{
		hit_Player(*(Vector3*)param);
	}
	//オブジェクトに当たったときの処理
	if (message == EventMessage::Hit_Object)
	{
		hit_Obj();
	}
}

void Citizen::change_Animation(Animation animID, float animFrame, float animSpeed, bool isLoop, float blendRate) {
	//animation_.ChangeAnim((int)animID, animFrame, animSpeed, isLoop);

	animation_.changeAnimation(AnimLoader::getInstance().getAnimKey(modelid_, (int)animID), isLoop, animSpeed, blendRate, animFrame);
}

void Citizen::change_State(State state)
{
	state_ = state;
	change_Animation(AnimConverter.at(state).animation, 0.0f, 1.0f, AnimConverter.at(state).isLoop);

	switch (state_)
	{
	case Citizen::State::Idle:
		break;
	case Citizen::State::Walk:
		movepower_ = 0.5f;
		break;
	case Citizen::State::Down:
		break;
	case Citizen::State::Jump:
		break;
	case Citizen::State::Dash:
		movepower_ = 1.0f;
		break;
	case Citizen::State::Surprised:
		break;
	default:
		break;
	}
}

void Citizen::hit_Player(Vector3 & dir)
{
	dir.y = 0;
	//velocity_ += dir * 0.02f;//衝突量
	velocity_ = dir * 0.1f;//衝突量
	extrudedflag_ = true;//吹き飛びのフラグをtrueにする
	change_State(State::Jump);
}

void Citizen::hit_Obj()
{
	//xとzのうち、近いほうの座標を選択して合わせる
	float x, z;
	x = std::abs(path_.front().x - position_.x);
	z = std::abs(path_.front().z - position_.z);
	//1回のみ判定 目的地を新たに設定する
	if (x < z && obj_hit_flag_ == false)
	{
		prevPath_ = position_;
		path_.push_front(Vector3(path_.front().x, 10, position_.z));
	}
	else if (obj_hit_flag_ == false)
	{
		prevPath_ = position_;
		path_.push_front(Vector3(position_.x, 10, path_.front().z));
	}
	//オブジェクトに当たったらヒットフラグをtrueにする
	obj_hit_flag_ = true;
	//ハマりがないかのデバッグ表示
	//DebugDraw::DebugDrawFormatString(500, 400, GetColor(255, 255, 255), "%f,%f", position_.x, position_.z);
}

bool Citizen::Get_Path_Size_Half()
{
	float a;
	if (path_.size() != 0)//0を割らない処理
		a = (float)first_path_size_ / (float)path_.size();
	else
		return true;//0だったらtrue
	if (a >= 2)//Pathサイズが初期サイズの半分以下ならtrueを返す
		return true;
	else//全てに当てはまらなければfalseを返す
		return false;
}

int Citizen::Get_Type()
{
	return type_;
}

void Citizen::idle(float deltaTime){
	

	//playerpos_ = world_->findActor("Player")->getPosition();
	change_State(State::Walk);
	if (position_.Distance(position_, playerpos_) < player_distance_)//プレイヤーとの距離が200未満ならループする
	{
		setLoop();
		return;
	}
	//市民の生存フラグをfalseにして送る
	GameDataManager::getInstance().setCiAlive(false, type_);
	GameDataManager::getInstance().removeCitizenList(this->shared_from_this());//生きている市民のポインタを格納してるリストから自身を削除
	GameDataManager::getInstance().removeAvoidTarget(this->shared_from_this());//ターゲットから自身を削除
	dead();//自身を消す処理 ループさせる際はコメントアウト
	return;
	//else
	//setPath();//ループさせるときはコメントアウトを解除
	//dead();
	//return;
	//if (animation_.IsAnimEnd()) {
}
void Citizen::walk(float deltaTime){

	
	if (path_.empty()) {
		change_State(State::Idle);
		return;
	}
	
	//float power = 3.0f;
	Vector3 toTargetPosition = (path_.front()- position_).Normalize();//自身から次の地点へのベクトル
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toTargetPosition);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	//OutputDebugString((std::to_string(checkIsLeftDot) + ":").c_str());


	avoid(deltaTime);


	Vector3 forwardVector = path_.front() - prevPath_;//経路の前方ベクトル
	Vector2	forwardVectorv2 = Vector2{ forwardVector.x,forwardVector.z };
	Vector3 leftVector = Matrix::CreateWorld(path_.front(), forwardVector, Vector3::Up).Left();//経路の横方向ベクトル
	Vector2 leftVectorv2 = Vector2{ leftVector.x,leftVector.z };
	Vector3 toCitizen = position_ - path_.front();//経路から自身に向かうベクトル
	Vector2 toCitizenv2 = Vector2{ toCitizen.x,toCitizen.z };

	if (Vector2::Angle(Vector2{ rotation_.Forward().x,rotation_.Forward().z }, forwardVectorv2) >= 90.0f) {//自身の向きが経路に対して横以上(逆向き)になったら
		toForward();//強制的に前を向く
	}

	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*30.0f);//スムーズに曲がってもらうために*13.0fを追加
	//if (extrudedflag_ == false)
	position_ += rotation_.Forward()*movepower_;//テストのために0.3f→1.0fに変更

	if (Vector2::Cross(leftVectorv2, toCitizenv2) >= 0.0f){//ポイント上に横線を引き、そのラインを越えたら


	//if (Vector3::Distance(position_, path_.front()) <= 1.f) {

		//次のポイントを設定
		prevPath_ = path_.front();
		path_.pop_front();
		obj_hit_flag_ = false;
	}
	/*
	if (dash_count_ != 0 && state_ != State::Dash)
		change_State(State::Dash);
		*/
}

void Citizen::down(float deltaTime)
{
	if (position_.y > 10.0f)
		position_ -= velocity_;//衝突用の力
	else if(signal_ == true)
	{
		//ジャンプ中にダウン状態に移行したときの対策
		extrudedflag_ = false;
		count = 0;//カウントを0にする
		position_.y = 10.0f;
		change_State(State::Walk);
	}
	
}

void Citizen::jump(float deltaTime)
{
	//横跳び
	count += deltaTime;
	if (count >= 0.5f || extrudedflag_ == false)
	{
		extrudedflag_ = false;
		change_State(State::Walk);
		count = 0;
	}
	if (extrudedflag_ == true)
	{
		position_ += velocity_;//衝突用の力
		count += deltaTime;//時間のカウント
	}
	//ジャンプ
	/*
	if (count >= 1.0f)
	{
		extrudedflag_ = false;
		count = 0;//カウントを0にする
		change_State(State::Walk);
	}
	else if (count >= 0.5f)
	{
		position_ -= velocity_;//衝突用の力
		count += deltaTime;//時間のカウント
	}
	else if (extrudedflag_ == true)
	{
		position_ += velocity_ + rotation_.Backward();//衝突用の力 後ろにも飛ばす処理
		count += deltaTime;//時間のカウント
	}
	else if (extrudedflag_ == false && count <= 0)
	{
		extrudedflag_ = false;
		count = 0;//カウントを0にする
		change_State(State::Walk);
		position_.y = 10.0f;
	}
	else if (extrudedflag_ == false)
	{
		position_ -= velocity_;//衝突用の力
		count -= deltaTime;//時間のカウント
	}*/
}

void Citizen::dash(float deltaTime)
{
	dash_count_ += deltaTime;
	//ダッシュの処理
	walk(deltaTime);
	if (dash_count_ >= 5.0f)
	{
		dash_count_ = 0;
		change_State(State::Walk);
	}
}

void Citizen::surprised(float deltaTime)
{
	//Vector3 target = (position_-enemypos_).Normalize();
	
	Vector3 dir = enemypos_ - position_;//エネミーの方向
	float angle = Vector3::Angle(Matrix::Identity.Forward(), dir);
	Vector3 checkIsLeftCrossVector = Vector3::Cross(Matrix::Identity.Forward(), dir);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(Matrix::Identity.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (checkIsLeftDot < 0.0f) {
		angle = 360.0f - angle;
	}
	rotation_ = Matrix::CreateRotationY(angle);//エネミーの方向を向く
	if(animation_.isEnd() == true)change_State(State::Dash);//走り状態に以降する
}

void Citizen::roadway()
{
	//短くした版
	for (int j = 0; j < roadway_.rows(); j++) {
		for (int i = 0; i < crosswalk_.rows(); i++)
		{
			//横断歩道の範囲に入って信号が赤か黄だったら止まる
			if (position_.x > crosswalk_.geti(i, 0) && position_.x < crosswalk_.geti(i, 1) && position_.z > crosswalk_.geti(i, 2) && position_.z < crosswalk_.geti(i, 3) && signal_ == false)
			{
				change_State(State::Down);
				breakflag = true;
				break;
			}
			//横断歩道の範囲に入って信号が青であれば進む
			else if (position_.x > crosswalk_.geti(i, 0) && position_.x < crosswalk_.geti(i, 1) && position_.z > crosswalk_.geti(i, 2) && position_.z < crosswalk_.geti(i, 3))
			{
				breakflag = true;
				break;
			}
		}
		//二重ループから抜ける処理
		if (breakflag)
			break;
		//車道に侵入しない処理 プレイヤーにも同様の処理を記述
		if (position_.x > roadway_.geti(j, 0) && position_.x < roadway_.geti(j, 1) && position_.z > roadway_.geti(j, 2) && position_.z <roadway_.geti(j, 3))
		{
			//車道定義の座標に侵入した際、positionと比較して最後に条件を満たしたのがxかzかを判定
			int x0, x1, z2, z3;
			x0 = (int)floorf(std::abs(roadway_.geti(j, 0) - position_.x));
			x1 = (int)floorf(std::abs(roadway_.geti(j, 1) - position_.x));
			z2 = (int)floorf(std::abs(roadway_.geti(j, 2) - position_.z));
			z3 = (int)floorf(std::abs(roadway_.geti(j, 3) - position_.z));
			std::list<int> minimum = { x0,x1,z2,z3 };
			minimum.sort();
			//判断したのがxならz座標は移動可能に、zならx座標を移動可能にする
			if (minimum.front() == x0 || minimum.front() == x1)
				position_.x = beforpos_.x;
			else if (minimum.front() == z2 || minimum.front() == z3)
				position_.z = beforpos_.z;
			extrudedflag_ = false;

			//角のバグ修正↓
			auto itr = minimum.begin();
			++itr;

			int corner;
			corner = *itr - minimum.front();
			
			if (corner <= 2)
			{
				position_ = beforpos_;
				//position_ += rotation_.Backward()*10;
				//break;
			}
			hit_Obj();
		}
	}
	breakflag = false;
	
}
//避ける処理
void Citizen::avoid(float deltaTime)
{
	//ターゲット座標を取得する
	auto avoidTarget = GameDataManager::getInstance().getAvoidTarget();

	Vector2 posv2, pos_forwardv2, forwardv2,leftv2;
	forwardv2.x = rotation_.Forward().x;//自身の前向きベクトル
	forwardv2.y = rotation_.Forward().z;
	forwardv2 = forwardv2.Normalize();
	posv2.x = position_.x;//自身の座標
	posv2.y = position_.z;
	pos_forwardv2.x = posv2.x + forwardv2.x;//自身の前方向座標
	pos_forwardv2.y = posv2.y + forwardv2.y;
	leftv2.x = rotation_.Left().x;//自身の横向きベクトル
	leftv2.y = rotation_.Left().z;



	//回避を行うか

	Vector2 prevpathv2,prev_currentpathv2;//経路ベクトル
	prevpathv2.x = prevPath_.x;//前回のポイント
	prevpathv2.y = prevPath_.z;
	prev_currentpathv2.x = path_.front().x - prevPath_.x;//前回のポイントから現在のポイントへ向かうベクトル
	prev_currentpathv2.y = path_.front().z - prevPath_.z;
	prev_currentpathv2.Normalize();

	float avoidDist = Vector2::Point_Distance(prev_currentpathv2, prevpathv2, posv2);//現在の回避幅

	if (avoidDist >= MAX_AVOID_SPACE) {//回避幅が許容範囲を超えたら
		toForward();//強制的に前を向く
		return;
	}
	//回避を行うか終了


	////線分で判定する
	//float slope = (pos_forwardv2.y - posv2.y) / (pos_forwardv2.x / posv2.x);//a
	//float coefficient = pos_forwardv2.y - (slope*pos_forwardv2.x);//b
	//
	//float slope_tangent = -(1 / slope);//a'


	constexpr float maxangle = 8.0f;//1回当たりの最大回転量
	constexpr float avoidlength = 16.5f;//回避幅
	constexpr float targetDistance = 16.5f*1.0f;//回避範囲
	float angle = 0.0f;//回転量
	for (auto& at : avoidTarget) {
		Vector2 targetv2;//回避対象の座標
		targetv2.x = at.lock()->getPosition().x;
		targetv2.y = at.lock()->getPosition().z;

		if (Vector2::Distance(posv2, targetv2) >= targetDistance)continue;//回避対象から一定距離以上離れていたら無視
		if (at.lock()->getNumber() == getNumber())continue;//自身と同じ識別番号なら無視

		Vector2 AP;//自身から回避対象へ向かうベクトル
		AP.x = targetv2.x - posv2.x;
		AP.y = targetv2.y - posv2.y;

		if (Vector2::Cross(leftv2, AP) < 0.0f)continue;//後ろ側だったら無視

		float D = MathHelper::Abs(Vector2::Cross(forwardv2, AP));//forwardv2とAPから作られる平行四辺形の面積を求める

		float L = Vector2::Distance(posv2, pos_forwardv2);//forwardv2の長さを求める

		float H = D / L;//上2つを使ってforwardv2,targetv2の交点からtargetv2までの距離を求める

		if (H > avoidlength)continue;//回避幅を超えていたら無視

		angle += (avoidlength-H) * MathHelper::Sign(Vector2::Cross(forwardv2, AP));//回転量を加算

		//float coefficient_tangent = targetv2.y - slope_tangent * targetv2.x;//b'
		//
		//Vector2 intersect_point;
		//intersect_point.x = (coefficient_tangent - coefficient) / (slope - slope_tangent);
		//intersect_point.y = slope_tangent * intersect_point.x + coefficient_tangent;
		//
		//float distance = Vector2::Distance(targetv2, intersect_point);

		//DrawLine3D(VGet(targetv2.x,15.0f, targetv2.y), VGet(intersect_point.x,15.0f, intersect_point.y), GetColor(255, 0, 0));
		
		//Vector2 targetv2;
		//targetv2.x = at.lock()->getPosition().x - position_.x;
		//targetv2.y = at.lock()->getPosition().z - position_.z;
		//targetv2 = targetv2.Normalize();
		//
		//auto angle = Vector2::Angle(targetv2, forwardv2);
		//if (MathHelper::Abs(angle) <= FOV) {//視界内に入っていたら
		//
		//	float checkIsLeftCrossVector = Vector2::Cross(forwardv2, targetv2);//外積で左右判定
		//	OutputDebugString((std::to_string(checkIsLeftCrossVector)+ "\n").c_str());
		//	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftCrossVector*2.0f);
		//
		//}
		//else {
		//	OutputDebugString("\n");
		//
		//}
	}
	
	angle = MathHelper::Clamp(angle, -maxangle, maxangle);//回転量を最大回転量までに丸める
	
	
	rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), angle);//回転を行う
}
//初期処理 目的地を決定
void Citizen::setPath()
{
	path_ = WalkPathReader::getInstance().getWalkList(type_);
	GameDataManager::getInstance().setCiAlive(true,type_);
	position_ = path_.front();//自分の位置を初期ポイントに設定する
	prevPath_ = position_;
	first_path_size_ = (int)path_.size();
	path_.pop_front();//次のポイントへ向かう
}
//移動をループさせる処理
void Citizen::setLoop()
{
	path_ = WalkPathReader::getInstance().getWalkList(type_);
	position_ = path_.front();//自分の位置を初期ポイントに設定する
	prevPath_ = position_;
	first_path_size_ = (int)path_.size();
	path_.pop_front();//次のポイントへ向かう
}

void Citizen::toForward()
{ 
	Vector2 prev_currentpathv2;//前のポイントから現在のポイントへ向かうベクトル
	prev_currentpathv2.x = path_.front().x - prevPath_.x;
	prev_currentpathv2.y = path_.front().z - prevPath_.z;
	prev_currentpathv2.Normalize();
	rotation_.Forward(Vector3{ prev_currentpathv2.x,0.0f,prev_currentpathv2.y });//自身の回転行列の前方向を上で作ったベクトルに置き換え
	rotation_.NormalizeRotationMatrix();//正規化する
}
