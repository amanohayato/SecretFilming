#include "CameraApp.h"
#include "../../Input/InputChecker.h"
#include "../Body/Ray.h"
#include "../Enemy/EnemyBase.h"
#include "../../Math/Matrix.h"
#include"../../Graphic/Sprite.h"
#include"../../Sound/Sound.h"
#include"../../Define.h"

static const Vector3 areaSize = Vector3::One*5.0f;//��`�̈�T�C�Y

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
	//// ���݂̏�Ԃ��X���[�v��ԂȂ�
	//if (curState_ == CameraAppState::Sleep)
	//{
	//	if (player_->isCamera())
	//	{
	//		// ���݂̏�Ԃ��A�N�e�B�u��Ԃ֕ύX����
	//		changeState(CameraAppState::Active);
	//	}
	//	return;
	//}

	//// �J�������\����L�[����̓��͂������Ȃ�����
	//if (!player_->isCamera())
	//{
	//	// ���݂̏�Ԃ��X���[�v��Ԃ֕ύX����
	//	changeState(CameraAppState::Sleep);
	//	return;
	//}

	// �ʐ^���B�e����L�[�����͂��ꂽ��
	if (InputChecker::GetInstance().KeyTriggerDown(Operation_Type::TAKE_SHUTTER_BUTTON))
	{
		// �X�R�A���v�Z����֐����Ă�
		int score = scoreCalculation();

		// �X�N���[���V���b�g���B�e����֐����Ă�
		world_->screenShot(score);
		Sound::GetInstance().StopSE(SE_ID::SHUTTER_SE);
		Sound::GetInstance().PlaySE(SE_ID::SHUTTER_SE);

	}
		
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	//�X�R�A0�Ȃ疳��
	if (enemy->getBaseScore() == 0) {
		RETURN_RESETRATE;
	}
	if (Vector3::Distance(player_->getPosition(), enemy->getPosition()) > shootingRange_) {
		RETURN_RESETRATE;
	}
	//�J�����͈͓��ɓG�����݂��Ă��Ȃ����0�_
	if (CheckCameraViewClip_Box(enemy->getPosition() + areaSize, enemy->getPosition() - areaSize) == TRUE) {
		RETURN_RESETRATE;
	}
	//�J�����͈͓��ɓG�̓������݂��Ă��Ȃ����0�_
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
	// ���݂̏�Ԃ��X���[�v��ԂȂ珈�����s��Ȃ�
	if (world_->getCameraAmount() < 0.99f) return;

	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	//�X�R�A0�Ȃ疳��
	//if (enemy->getBaseScore() == 0)return;

	//if (Vector3::Distance(player_->getPosition(), enemy->getPosition()) > shootingRange_) return;
	////�J�����͈͓��ɓG�����݂��Ă��Ȃ����0�_
	//if (CheckCameraViewClip_Box(enemy->getPosition() + areaSize, enemy->getPosition() - areaSize) == TRUE)return;
	////�J�����͈͓��ɓG�̓������݂��Ă��Ȃ����0�_
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

	auto verts = enemy->getHeadVertex();//���_�̋����Ŋ�̃T�C�Y�𒲂ׂ�
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
	// �J�������\���Ă��鎖������UI
	DebugDraw::DebugDrawFormatString(500, 250, GetColor(255, 255, 255), "�J�����I��");
}

void CameraApp::receiveMessage(EventMessage message, void * param)
{
}

// �X�R�A���v�Z����֐�
int CameraApp::scoreCalculation()
{
	// �G�̉F���l���擾
	std::shared_ptr<EnemyBase> enemy = std::static_pointer_cast<EnemyBase>(world_->findActor("Enemy"));

	Vector3 enemyPos = enemy->getPosition();
	Vector3 enemyHeadPos = enemy->getHeadPos();


	//// �v���C���[�̐��ʂ̃x�N�g��
	//Vector3 playerForward = player_->getRotation().Forward();
	//// �v���C���[����G�l�~�[�̃x�N�g��
	//Vector3 playerToEnemy = Vector3::Normalize(enemy->getPosition() - player_->getPosition());
	//Vector3 playerToEnemyHead = Vector3::Normalize(enemy->getHeadPos() - player_->getPosition());
	//// playerForward �� playerToEnemy �̊Ԃ̊p�x
	//float angle = MathHelper::Abs(Vector3::Angle(playerForward, playerToEnemy));
	//float headAngle = abs(Vector3::Angle(playerForward, playerToEnemyHead));
	//// �G�̉F���l�̕����������Ă��Ȃ���΁A�O�_
	//if (angle > shootingAngle_) return 0;
	//if (headAngle > shootingAngle_) return 0;

	//�J�����͈͓��ɓG�����݂��Ă��Ȃ����0�_
	if (CheckCameraViewClip_Box(enemyPos + areaSize, enemyPos - areaSize) == TRUE)return 0;
	//�J�����͈͓��ɓG�̓������݂��Ă��Ȃ����0�_
	if (CheckCameraViewClip_Box(enemyHeadPos + areaSize, enemyHeadPos - areaSize) == TRUE)return 0;
	// �G�̉F���l����������ꍇ�A�O�_
	if (Vector3::Distance(player_->getPosition(), enemy->getPosition()) > shootingRange_) return 0;
	int score = 0;

	// �v���C���[�ƉF���l�̊ԂɌ������������
	if (
		!(world_->hitToLine(player_->getPosition(), enemy->getPosition())) &&
		!(world_->hitToLine(player_->getPosition(), enemy->getHeadPos()))
		)
	{
		// �C�x���g���̃X�R�A���擾�i���͂Ƃ肠�����Q�Opt���x�[�X�Ɂj
		score = std::static_pointer_cast<EnemyBase>(enemy)->getBaseScore();
	}
	// �F���l���C�x���g�V�[���ɓ����Ă��Ȃ���΂O�_�i���͂܂��������j
	if (score==0) return 0;


	// �����␳
	auto dist = (Vector3::Distance(player_->getPosition(), enemy->getPosition()) / shootingRange_);
	score = (int)(score * (1.f - dist));

	// �p�x�␳
	//score *= 1 - (angle / shootingAngle_);

	score = max(0, score);
	// �f�o�b�O���O��\��
	//OutputDebugString(("�l���X�R�A�F" + std::to_string(score) + "\n").c_str());
	enemy->receiveMessage(EventMessage::Score_None);
	return score;
}

// �J�����A�v���̏�Ԃ̕ύX
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