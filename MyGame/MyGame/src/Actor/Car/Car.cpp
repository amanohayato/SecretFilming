#include "Car.h"
#include"../../Graphic/Model.h"
#include"../../Input/InputChecker.h"
#include"../Other/CameraActor.h"
#include"../Citizen/WalkPathReader.h"
#include"../../Scene/Manager/GameDataManager.h"
#include"../../Sound/Sound.h"

Car::Car(IWorld * world,std::string name, MODEL_ID id1, MODEL_ID id2, MODEL_ID id3, int type, bool is_front, const IBodyPtr & body):
	Actor(world,name,Vector3::Zero,body), modelid_(id1), modelid_move1_(id1), modelid_move2_(id2), modelid_lamp_(id3),is_front_(is_front){
	crosswalk_.load("res/Data/carcrosswalk.csv");
	path_ = WalkPathReader::getInstance().getDriveList(type);//carmapの読み込み(Vectorにcarmap1 2 3 4とeventcar1 2 3 が入っている)
	position_ = path_.front();
	type_ = type;//どのルートの車か判断する
	carstate_ = CarState::Move;
	GameDataManager::getInstance().setCarAlive(true, type);//自身が生成されたら生存フラグをtrueにして送る

}


void Car::update(float deltaTime)
{
	delta_time_ = deltaTime;
	
	//車信号の状態を取得する
	signal_ = GameDataManager::getInstance().getCarSignal();
	//一定以上のy座標を超えるか目的地がなくなると自身を消す
	if (path_.empty()|| position_.y >deadpos_y_) {
		GameDataManager::getInstance().setCarAlive(false, type_);//生存フラグをfalseにして送る
		GameDataManager::getInstance().removeCarList(this->shared_from_this());//生きている車のポインタを格納してるリストから自身を削除
		dead();
		return;
	}
	Signal();
}

void Car::draw() const
{
	//スポーン時の車の向き
	if (is_front_ == false)
	{
		Model::GetInstance().Draw(modelid_, Matrix(rotation_ * Matrix::CreateFromAxisAngle(rotation_.Up(), 180.0f) * Matrix::CreateScale((Vector3(1.2f, 1.2f, 1.2f)))).Translation(position_ + Vector3::Down*body_->radius()));//180度回転させてスケールを1.2倍する
		
	}
	//スポーン時の車の向き(逆)
	else
	{
		Model::GetInstance().Draw(modelid_, Matrix(rotation_).Translation(position_ + Vector3::Down*body_->radius()));
	}
	//当たり判定デバック表示
	body_->transform(getPose())->draw();
}
void Car::shadowDraw() const
{
	draw();
}
//衝突したらメッセージを送る
void Car::onCollide(Actor & other)
{
	Vector3 hitdir = (other.getPosition() - position_);
	other.receiveMessage(EventMessage::Hit_Car, (void*)&hitdir);
}
//メッセージを受け取る
void Car::receiveMessage(EventMessage message, void * param)
{
	if (message == EventMessage::Hit_Enemy)
	{
		hit_Enemy(*(Vector3*)param);
	}
}
void Car::change_State(CarState state)
{
	carstate_ = state;
	switch (carstate_)
	{
	case Car::CarState::Idle:
		Idle();
		break;
	case Car::CarState::Move:
		move();
		break;
	}
}
//エネミーと当たったときの判定
void Car::hit_Enemy(const Vector3& dir)
{
	Vector3 dir_ = Vector3::Normalize(dir);
	velocity_ = rotation_.Up() * 10 + dir_ * 3;
	velocity_ = Vector3::Normalize(velocity_);
	//上に跳ぶフラグをtrueにする
	enemyhitflag_ = true;

	Sound::GetInstance().Play3DSE(SE_ID::JUNCTION_HUTTOBI_VC_SE,(VECTOR*)&position_);
}

void Car::move()
{
	//エラー対策
	if (path_.size() == 0)
		return;
	count_ += delta_time_;
	Vector3 toNextPoint = (path_.front() - position_).Normalize();//自身から次の地点へのベクトル
	Vector3 checkIsLeftCrossVector = Vector3::Cross(rotation_.Forward(), toNextPoint);//外積で左右判定
	float checkIsLeftDot = Vector3::Dot(rotation_.Up(), checkIsLeftCrossVector);//上+内積で自身の回転を考慮した左右判定(正なら左、負なら右)
	if (enemyhitflag_)
	{
		position_ += velocity_ * 2;
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Right(),1);
	}
	//初期の向きによって正面側か後ろ側かどちらに進むかを決定
	else if (is_front_ == false)
	{
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Up(), checkIsLeftDot*6.0f);
		position_ += rotation_.Forward()*3.0f;
	}
	else
	{
		rotation_ *= Matrix::CreateFromAxisAngle(rotation_.Backward(), checkIsLeftDot*6.0f);
		position_ += rotation_.Backward()*3.0f;
	}
	//目的地についたら次の目的地へ
	if (Vector2::Distance(Vector2(position_.x, position_.z), Vector2(path_.front().x, path_.front().z)) <= 10.0f) {
		path_.pop_front();
	}
	if (count_ <= 0.05f)
		modelid_ = modelid_move1_;
	else if (count_ <= 0.1f)
		modelid_ = modelid_move2_;
	else
		count_ = 0;
}

void Car::Idle()
{
	//車が止まります
	modelid_ = modelid_lamp_;
}
//信号のときの処理
void Car::Signal()
{
	for (int i = 0; i < crosswalk_.rows(); i++)
	{
		
		//イベントカーであれば信号を無視する
		if (type_ == 4 || type_ == 5 || type_ == 6)
		{
			change_State(CarState::Move);
			break;
		}
		//信号が赤で車が止まる範囲に入ったら車を停止状態にする
		if (signal_ == false && position_.x > crosswalk_.geti(i, 0) && position_.x < crosswalk_.geti(i, 1) && position_.z > crosswalk_.geti(i, 2) && position_.z < crosswalk_.geti(i, 3))
		{
			change_State(CarState::Idle);
			break;
		}
		//それ以外の条件なら走る
		else
		{
			change_State(CarState::Move);
		}
	}
}

void Car::setsignal(bool signal)
{
	signal_ = signal;
}
