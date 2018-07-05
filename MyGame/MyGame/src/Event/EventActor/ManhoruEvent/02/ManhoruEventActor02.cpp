#include "ManhoruEventActor02.h"

#include "../../../../Actor/UIActor/NoticedLine.h"

#include "../../../../Field/Building/Town/Manhoru/ManhoruBulding.h"
#include "../../../../Actor/EventActor/EventEnemy/EventCar/EventCar.h"

#include "../../../../Actor/EventActor/EventUtility/MoveActor.h"

#include "../../../../Sound/Sound.h"
ManhoruEventActor02::ManhoruEventActor02(IWorld & world) :
	EventActor(world)
{
}

ManhoruEventActor02::~ManhoruEventActor02()
{
}

void ManhoruEventActor02::Start()
{
	mEnemyBase = static_cast<EnemyBase*>(mWorld->findActor("Enemy").get());
	Sound::GetInstance().Play3DSE(SE_ID::MANHOLE_ALIEN_VC1, (VECTOR*)&mEnemyBase->getPosition());



}

void ManhoruEventActor02::Update()
{
	auto manhoruBil = static_cast<ManhoruBulding*>(mEnemyBase->GetEventPoints().front().building_.lock().get());
	auto car = manhoruBil->GetCarActor();
	Matrix endMat;
	endMat = Matrix::Identity;
	endMat.Forward(static_cast<EventCar*>(car.get())->GetPosition() - mEnemyBase->getPosition());
	endMat.Right(Vector3::Cross(endMat.Forward(), Vector3::Up));
	endMat.Up(Vector3::Up);
	endMat.Translation(mEnemyBase->getPosition());

	Matrix mat = mEnemyBase->getPose();
	mIsEnd = MoveActor::Move(mat, endMat);
	mEnemyBase->get_rotation() = mat.RotationMatrix();
	mEnemyBase->getPosition() = mat.Translation();
}

void ManhoruEventActor02::Draw() const
{
}

void ManhoruEventActor02::End()
{
}
