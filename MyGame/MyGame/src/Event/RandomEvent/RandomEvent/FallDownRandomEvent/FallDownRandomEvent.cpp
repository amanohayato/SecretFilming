#include "FallDownRandomEvent.h"
#include "../RandomEventState/FallDownState/FallDownState.h"
#include "../RandomEventState/RisingHatState/RisingHatState.h"
#include "../RandomEventState/LookAroundState/LookAroundState.h"

FallDownRandomEvent::FallDownRandomEvent(IWorld & world) {
	world_ = &world;
	Add(RandomEvent::FallDown_State, std::make_shared<FallDownState>(world));
	Add(RandomEvent::RisingHat_State, std::make_shared<RisingHatState>(world));
	Add(RandomEvent::LookAround_State, std::make_shared<LookAroundState>(world));
}

void FallDownRandomEvent::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	Change(RandomEvent::FallDown_State);
	currentRandomEvent_->Initialize();
	textBox_ = std::make_shared<TextBox>(0);
	textBox_->Init();
	textBox_->Display_Text();
	textBox_->add("FallDown/fall1.txt");
	textBox_->Start_Text();
}

void FallDownRandomEvent::Update()
{
	currentRandomEvent_->Update();
	if (currentRandomEvent_->IsEnd()) {
		if (randomEvent_ == RandomEvent::LookAround_State)isEnd_ = true;
		else Change(currentRandomEvent_->Next());
	}
	if (!world_->hitToLine(world_->findActor("Player")->getPosition(), enemyBase_.lock()->getPosition())) textBox_->SetIsDraw(true);
	else textBox_->SetIsDraw(false);

	//テキストアップデート
	textBox_->Update();
}

void FallDownRandomEvent::Draw() const
{
	currentRandomEvent_->Draw();
	world_->addDrawFunction([&] {
		if (world_->getCameraAmount() >= 0.01f)return;
		if (world_->getMapAmount() >= 0.01f)return;
		textBox_->Draw(Vector2{ 200.0f,800.0f }, FONT_ID::FONT_TEXT, Vector2(1000, 150));
	});
	DebugDraw::DebugDrawFormatString(0, 600, GetColor(255, 0, 0), "こけるイベント中");
}

bool FallDownRandomEvent::IsEnd() const
{
	return isEnd_;
}

void FallDownRandomEvent::End(){}

RandomEvent FallDownRandomEvent::Next() const
{
	return RandomEvent::Null_Eve;
}

void FallDownRandomEvent::Add(RandomEvent name, const IRandomEventPtr & event)
{
	randomEvents_[name] = event;
}

void FallDownRandomEvent::Change(RandomEvent name)
{
	randomEvent_ = name;
	if(currentRandomEvent_!=nullptr)currentRandomEvent_->End();
	currentRandomEvent_ = randomEvents_[name];
	currentRandomEvent_->Initialize();
}
