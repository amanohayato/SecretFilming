#include "CameraApp.h"
#include "../../Input/InputChecker.h"
#include "../Body/Ray.h"
#include "../Enemy/EnemyBase.h"
#include "../../Math/Matrix.h"
#include"../../Graphic/Sprite.h"
#include"../../Sound/Sound.h"
#include"../../Define.h"

static const Vector3 areaSize = Vector3::One*5.0f;//矩形領域サイズ

static const Vector2 defaultBox{ 800,450 };


#define RETURN_RESETRATE do{frameSetRate=0.0f;return;} while(0)

CameraApp::CameraApp(IWorld * world, ActorPtr player) :
	Actor(world, "CameraApp", Vector3::Zero, std::make_shared<DummyBody>())
{
	player_ = player;
}

void CameraApp::initialize()
{
	frameSetRate = 0.0f;
}

void CameraApp::update(float deltaTime)
{
	if (world_->getCameraAmount() < 0.99f) {
		RETURN_RESETRATE;
	}
	//// 現在の状態がスリープ状態なら
	//if (curState_ == CameraAppState::Sleep)
	//{
	//	if (player_->isCamera())
	//	{
	//		// 現在の状態をアクティブ状態へ変更する
	//		changeState(CameraAppState::Active);
	//	}
	//	return;
	//}

	//// カメラを構えるキーからの入力が無くなったら
	//if (!player_->isCamera())
	//{
	//	// 現在の状態をスリープ状態へ変更する
	//	changeState(CameraAppState::Sleep);
	//	return;
	//}

	// 写真を撮影するキーが入力されたら
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::TAKE_SHUTTER_BUTTON))
	{
		// スコアを計算する関数を呼ぶ
		int score = scoreCalculation();

		// スクリーンショットを撮影する関数を呼ぶ
		world_->screenShot(score);
		Sound::GetInstance().StopSE(SE_ID::SHUTTER_SE);
		Sound::GetInstance().PlaySE(SE_ID::SHUTTER_SE);

	}
		
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	//スコア0なら無視
	if (enemy->getBaseScore() == 0) {
		RETURN_RESETRATE;
	}
	if (Vector3::Distance(player_->getPosition(), enemy->getPosition()) > shootingRange_) {
		RETURN_RESETRATE;
	}
	//カメラ範囲内に敵が存在していなければ0点
	if (CheckCameraViewClip_Box(enemy->getPosition() + areaSize, enemy->getPosition() - areaSize) == TRUE) {
		RETURN_RESETRATE;
	}
	//カメラ範囲内に敵の頭が存在していなければ0点
	if (CheckCameraViewClip_Box(enemy->getHeadPos() + areaSize, enemy->getHeadPos() - areaSize) == TRUE) {
		RETURN_RESETRATE;
	}
	if (
		(world_->hitToLine(player_->getPosition(), enemy->getPosition())) ||
		(world_->hitToLine(player_->getPosition(), enemy->getHeadPos()))
		) {
		RETURN_RESETRATE;
	}
	frameSetRate += deltaTime*5.0f;
	frameSetRate = MathHelper::Clamp(frameSetRate, 0.0f, 2.0f);
}

void CameraApp::draw() const
{
	// 現在の状態がスリープ状態なら処理を行わない
	if (world_->getCameraAmount() < 0.99f) return;

	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	//スコア0なら無視
	//if (enemy->getBaseScore() == 0)return;

	//if (Vector3::Distance(player_->getPosition(), enemy->getPosition()) > shootingRange_) return;
	////カメラ範囲内に敵が存在していなければ0点
	//if (CheckCameraViewClip_Box(enemy->getPosition() + areaSize, enemy->getPosition() - areaSize) == TRUE)return;
	////カメラ範囲内に敵の頭が存在していなければ0点
	//if (CheckCameraViewClip_Box(enemy->getHeadPos() + areaSize, enemy->getHeadPos() - areaSize) == TRUE)return;
	//if (
	//	(world_->hitToLine(player_->getPosition(), enemy->getPosition())) ||
	//	(world_->hitToLine(player_->getPosition(), enemy->getHeadPos()))
	//	)return;

	auto ps = ConvWorldPosToScreenPos(enemy->getHeadPos());

	auto enemyPos = ConvWorldPosToScreenPos(enemy->getPosition());

	float chancelength = Vector3::Distance(ps, enemyPos);

	constexpr float upcorrect = 2.0f;
	chancelength *= upcorrect;
	Vector2 chancePos;
	chancePos.x = enemyPos.x;
	chancePos.y = enemyPos.y;
	chancePos += Vector2::Down*chancelength;

	auto verts = enemy->getHeadVertex();//頂点の距離で顔のサイズを調べる
	auto headps2 = ConvWorldPosToScreenPos(verts.at(1));
	auto boxlength=Vector3::Distance(ps, headps2);
	Vector2 boxsize{ boxlength,boxlength };
	boxsize *= 40.0f;
	
	float rate = MathHelper::Clamp(frameSetRate-1.0f,0.0f,1.0f);
	Vector2 drawBoxSize = Vector2::Lerp(defaultBox, boxsize, rate);
	Vector2 drawPosition = Vector2::Lerp(Vector2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT) * 0.5f, Vector2{ ps.x,ps.y }, rate);
	world_->addDrawFunction([=] {
		DrawBoxAA(drawPosition.x - drawBoxSize.x, drawPosition.y - drawBoxSize.y, drawPosition.x + drawBoxSize.x, drawPosition.y + drawBoxSize.y, GetColor(251, 236, 53), FALSE,3.0f);

		Vector2 origin = Sprite::GetInstance().GetSize(SPRITE_ID::SPRITE_CHANCE);
		origin *= 0.5f;
		origin.x = 0.0f;

		if(rate >=1.0f)Sprite::GetInstance().Draw(SPRITE_ID::SPRITE_CHANCE, chancePos, origin, Vector2::One);
		
	});
	// カメラを構えている事を示すUI
	DebugDraw::DebugDrawFormatString(500, 250, GetColor(255, 255, 255), "カメラオン");
}

void CameraApp::receiveMessage(EventMessage message, void * param)
{
}

// スコアを計算する関数
int CameraApp::scoreCalculation()
{
	// 敵の宇宙人を取得
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	Vector3 enemyPos = enemy->getPosition();
	Vector3 enemyHeadPos = enemy->getHeadPos();


	//// プレイヤーの正面のベクトル
	//Vector3 playerForward = player_->getRotation().Forward();
	//// プレイヤーからエネミーのベクトル
	//Vector3 playerToEnemy = Vector3::Normalize(enemy->getPosition() - player_->getPosition());
	//Vector3 playerToEnemyHead = Vector3::Normalize(enemy->getHeadPos() - player_->getPosition());
	//// playerForward と playerToEnemy の間の角度
	//float angle = MathHelper::Abs(Vector3::Angle(playerForward, playerToEnemy));
	//float headAngle = abs(Vector3::Angle(playerForward, playerToEnemyHead));
	//// 敵の宇宙人の方向を向いていなければ、０点
	//if (angle > shootingAngle_) return 0;
	//if (headAngle > shootingAngle_) return 0;

	//カメラ範囲内に敵が存在していなければ0点
	if (CheckCameraViewClip_Box(enemyPos + areaSize, enemyPos - areaSize) == TRUE)return 0;
	//カメラ範囲内に敵の頭が存在していなければ0点
	if (CheckCameraViewClip_Box(enemyHeadPos + areaSize, enemyHeadPos - areaSize) == TRUE)return 0;
	// 敵の宇宙人が遠すぎる場合、０点
	if (Vector3::Distance(player_->getPosition(), enemy->getPosition()) > shootingRange_) return 0;
	int score = 0;

	// プレイヤーと宇宙人の間に建物が無ければ
	if (
		!(world_->hitToLine(player_->getPosition(), enemy->getPosition())) &&
		!(world_->hitToLine(player_->getPosition(), enemy->getHeadPos()))
		)
	{
		// イベント毎のスコアを取得（今はとりあえず２０ptをベースに）
		score = std::static_pointer_cast<EnemyBase>(enemy)->getBaseScore();
	}
	// 宇宙人がイベントシーンに入っていなければ０点（今はまだ未実装）
	if (score==0) return 0;


	// 距離補正
	auto dist = (Vector3::Distance(player_->getPosition(), enemy->getPosition()) / shootingRange_);
	score = (int)(score * (1.f - dist));

	// 角度補正
	//score *= 1 - (angle / shootingAngle_);

	score = max(0, score);
	// デバッグログを表示
	//OutputDebugString(("獲得スコア：" + std::to_string(score) + "\n").c_str());
	enemy->receiveMessage(EventMessage::Score_None);
	return score;
}

// カメラアプリの状態の変更
void CameraApp::changeState(CameraAppState state)
{
	curState_ = state;
}

void CameraApp::active()
{
	changeState(CameraAppState::Active);
}

void CameraApp::sleep()
{
	changeState(CameraAppState::Sleep);
}

const float CameraApp::shootingRange_{ 500.0f };

const float CameraApp::shootingAngle_{ 50.0f };