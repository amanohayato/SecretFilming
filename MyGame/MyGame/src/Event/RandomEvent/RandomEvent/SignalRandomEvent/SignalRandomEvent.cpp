#include "SignalRandomEvent.h"
#include "../RandomEventState/HologramState/HologramState.h"
#include "../RandomEventState/LookAroundState/LookAroundState.h"
#include"../../../../Graphic/TextBox.h"

SignalRandomEvent::SignalRandomEvent(IWorld & world) {
	world_ = &world;
	Add(RandomEvent::Hologram_State, std::make_shared<HologramState>(world));
	Add(RandomEvent::LookAround_State, std::make_shared<LookAroundState>(world));
}

void SignalRandomEvent::Initialize()
{
	isEnd_ = false;
	enemyBase_ = std::dynamic_pointer_cast<EnemyBase>(world_->findActor("Enemy"));
	Change(RandomEvent::Hologram_State);
	currentRandomEvent_->Initialize();
	textBox_ = std::make_shared<TextBox>(0);
	textBox_->Init();
	textBox_->Display_Text();
	textBox_->add("Hologram/hologram1.txt");
	textBox_->Start_Text();
}

void SignalRandomEvent::Update()
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

void SignalRandomEvent::Draw() const
{
	currentRandomEvent_->Draw();
	world_->addDrawFunction([&] {
		if (world_->getCameraAmount() >= 0.01f)return;
		if (world_->getMapAmount() >= 0.01f)return;
		textBox_->Draw(Vector2{ 200.0f,800.0f }, FONT_ID::FONT_TEXT, Vector2(1000, 150));
	});
	DebugDraw::DebugDrawFormatString(0, 600, GetColor(255, 0, 0), "通信イベント");
}

bool SignalRandomEvent::IsEnd() const
{
	return isEnd_;
}

void SignalRandomEvent::End(){}

RandomEvent SignalRandomEvent::Next() const
{
	return RandomEvent::Null_Eve;
}

void SignalRandomEvent::Add(RandomEvent name, const IRandomEventPtr & event)
{
	randomEvents_[name] = event;
}

void SignalRandomEvent::Change(RandomEvent name)
{
	randomEvent_ = name;
	End();
	currentRandomEvent_ = randomEvents_[name];
	currentRandomEvent_->Initialize();
}
