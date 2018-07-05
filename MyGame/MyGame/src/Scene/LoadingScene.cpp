#include "LoadingScene.h"
#include"../Resource/LoadingList.h"
#include"../Graphic/EffekseerManager.h"
#include"../Actor/Citizen/WalkPathReader.h"
#include"../Graphic/Shader/CBuff/Floor_CB.h"
#include"../Graphic/ShadowMap.h"
#include"../Math/MathHelper.h"
#include"../Define.h"
#include"../Math/Point.h"

LoadingScene::LoadingScene() {
	next_ = SceneType::SCENE_ENTRANCE;
}

void LoadingScene::start() {
	_animCount = 0;
	_loadAnimList.clear();
	LoadSpriteAnim();
	//各種リソースのロードを行う
	SetUseASyncLoadFlag(TRUE);
	LoadSprite();
	LoadModel();
	SetUseASyncLoadFlag(FALSE);
	LoadEffect();
	LoadFont();
	SetUseASyncLoadFlag(TRUE);
	LoadBGM();
	SetUseASyncLoadFlag(FALSE);
	LoadSE();
	LoadShader();
	LoadEtcetera();


}

void LoadingScene::update(float deltaTime) {
	_animCount++;
	_animCount %= _loadAnimList.size();

	if (GetASyncLoadNum() <= 0) {
		isEnd_ = true;
	}
}

void LoadingScene::draw() const {
	if (isEnd_)return;
	Point pos;
	int x,y;
	GetGraphSize(_loadAnimList.at(_animCount), &x, &y);
	pos.x = WINDOW_WIDTH - x;
	pos.y = WINDOW_HEIGHT - y;
	DrawGraph(pos.x, pos.y, _loadAnimList.at(_animCount), TRUE);
}

void LoadingScene::end() {
	for (int i = 0; i < _loadAnimList.size(); ++i) {
		DeleteGraph(_loadAnimList.at(i));
	}
	_loadAnimList.clear();
}

void LoadingScene::LoadSprite()
{
	std::string defaultPath = "res/Sprite/";	// 全リソース共通パス

	Sprite::GetInstance().Load(defaultPath + "free/action01.png",					SPRITE_ID::SPRITE_ACTION);			// 回避アクションでの暗くなる演出用画像
	Model::GetInstance().Load2D(defaultPath + "free/qustionframe.png",				MODEL_ID::SPRITE_QUESTION_FRAME);	// 宇宙人の警戒度ゲージの外枠画像
	Model::GetInstance().Load2D(defaultPath + "free/qustiongauge.png",				MODEL_ID::SPRITE_QUESTION_GAUGE);	// 宇宙人の警戒度ゲージの内側画像
	Sprite::GetInstance().Load(defaultPath + "free/camera_ui1.png",					SPRITE_ID::SPRITE_CAMERAUI1);		// シャッターボタンを押す前のカメラフレーム画像
	Sprite::GetInstance().Load(defaultPath + "free/camera_ui2.png",					SPRITE_ID::SPRITE_CAMERAUI2);		// シャッターボタンを押した後のカメラフレーム画像
	Model::GetInstance().Load2D(defaultPath + "free/exclamation.png",				MODEL_ID::SPRITE_EXCLAMATION);		// 宇宙人に気づかれた時に表示する！マーク

	Sprite::GetInstance().Load(defaultPath + "free/Confirm/gauge_max_NOgauge.png",	SPRITE_ID::SPRITE_CONFIRM);			// 確定度ゲージの内側画像
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/gauge.png",				SPRITE_ID::SPRITE_CONFIRM_FRAME);	// 確定度ゲージの外枠画像
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/number.png",				SPRITE_ID::SPRITE_CONFIRM_NOMBER,	// 確定度の値を表す数字リソース
		11, Point(11, 1), Point(27, 39));

	Sprite::GetInstance().Load(defaultPath + "free/Confirm/0p.png",		SPRITE_ID::SPRITE_CONFIRM_ALIAN0);	// 宇宙人の画像での確定度の表示UI_0
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/10p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN1);	// 宇宙人の画像での確定度の表示UI_1
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/20p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN2);	// 宇宙人の画像での確定度の表示UI_2
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/30p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN3);	// 宇宙人の画像での確定度の表示UI_3
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/40p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN4);	// 宇宙人の画像での確定度の表示UI_4
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/50p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN5);	// 宇宙人の画像での確定度の表示UI_5
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/60p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN6);	// 宇宙人の画像での確定度の表示UI_6
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/70p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN7);	// 宇宙人の画像での確定度の表示UI_7
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/80p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN8);	// 宇宙人の画像での確定度の表示UI_8
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/90p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN9);	// 宇宙人の画像での確定度の表示UI_9
	Sprite::GetInstance().Load(defaultPath + "free/Confirm/100p.png",	SPRITE_ID::SPRITE_CONFIRM_ALIAN10);	// 宇宙人の画像での確定度の表示UI_10

	Model::GetInstance().Load2D(defaultPath + "free/noticed_line.png",	MODEL_ID::SPRITE_NOTICED_LINE);	// 気付き線の画像
	Sprite::GetInstance().Load(defaultPath + "free/frame.png",			SPRITE_ID::SPRITE_FRAME);		// カメラのシャッター時のフラッシュ演出の画像
	Sprite::GetInstance().Load(defaultPath + "free/cameraicon.png",		SPRITE_ID::SPRITE_CAMERA_ICON);	// カメラアイコンの画像
	Sprite::GetInstance().Load(defaultPath + "free/mapicon.png",		SPRITE_ID::SPRITE_MAP_ICON);	// マップアイコンの画像
	Sprite::GetInstance().Load(defaultPath + "free/pin.png",			SPRITE_ID::SPRITE_PIN);			// マップアプリのイベントが発生する場所を示すピンの
	Sprite::GetInstance().Load(defaultPath + "free/chanceUI.png",		SPRITE_ID::SPRITE_CHANCE);		// シャッターチャンスを表すカメラのUIの画像
	Sprite::GetInstance().Load(defaultPath + "free/black2.png",			SPRITE_ID::SPRITE_BLACK);		// 真っ暗な画像（画面のフェード等に使う）

	// シーン共通のリソース
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Blind.png",				SPRITE_ID::SPRITE_BLIND);				// 画面の背景を暗くするための画像（SPRITE_ID::SPRITE_BLACK）で事足りる
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Yes_UI.png",				SPRITE_ID::SPRITE_YES_UI);				// シーンでの YES の画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/No_UI.png",				SPRITE_ID::SPRITE_NO_UI);				// シーンでの NO の画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Menu_cursor.png",		SPRITE_ID::SPRITE_MENU_CURSOR);			// シーンでのカーソル画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/press_any_button.png",	SPRITE_ID::SPRITE_PRESS_ANY_BUTTON_UI);	// シーンでの PressAnyButton の画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Number_UI.png",			SPRITE_ID::SPRITE_NUMBER_UI,			// シーンでの数字リソース
		11, Point(11, 1), Point(50, 65));

	// エントランスシーン用のスプライト
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Titlelogo.png",			SPRITE_ID::SPRITE_TITLELOGO);			// タイトルロゴの画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/sozai_teikyou_text.png", SPRITE_ID::SPRITE_SOZAI_TEIKYOU_TEXT);	// サウンドの提供を表す画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Game_start.png",			SPRITE_ID::SPRITE_GAME_START);			// タイトルメニューのゲームスタート項目画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Go_to_option.png",		SPRITE_ID::SPRITE_GO_TO_OPTION);		// タイトルメニューのオプションへ項目画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Exit.png",				SPRITE_ID::SPRITE_EXIT);				// タイトルメニューのゲーム終了項目画像

	// オプションシーン用のスプライト
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Option_camera_sensitivity.png",	SPRITE_ID::SPRITE_OPTION_CAMERA_SENSITIVITY);	// オプションでのカメラ感度項目画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Option_BGM_volume.png",			SPRITE_ID::SPRITE_OPTION_BGM_VOLUME);			// オプションでのBGM音量項目画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Option_SE_volume.png",			SPRITE_ID::SPRITE_OPTION_SE_VOLUME);			// オプションでのSE音量項目画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Option_Flame.png",				SPRITE_ID::SPRITE_OPTION_FLAME);				// オプションでの選択項目のゲージの外枠画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Option_cursor.png",				SPRITE_ID::SPRITE_OPTION_CURSOR);				// オプションでのカーソル画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/option_bar_color.png",			SPRITE_ID::SPRITE_OPTION_BAR,					// オプションでの選択項目のゲージの内枠画像
		10, Point(10, 1), Point(100, 50));

	// チュートリアル用のスプライト
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/A_Push_1.png",	SPRITE_ID::SPRITE_A_PUSH_1);	// Aボタンの入力促し画像_1
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/A_Push_2.png",	SPRITE_ID::SPRITE_A_PUSH_2);	// Aボタンの入力促し画像_2
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/LT_Push.png",	SPRITE_ID::SPRITE_LT_PUSH);		// LTボタンの入力促し画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/RT_Push.png",	SPRITE_ID::SPRITE_RT_PUSH);		// RTボタンの入力促し画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Y_Push.png",		SPRITE_ID::SPRITE_Y_PUSH);		// Yボタンの入力促し画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Push_Arrow.png", SPRITE_ID::SPRITE_PUSH_ARROW);	// 入力促し矢印画像
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/skip01.png",		SPRITE_ID::SPRITE_START_SKIP);	// 

	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookSpecifiedPointIcon.png",	SPRITE_ID::SPRITE_LOOK_SPECIFIED_POINT_ICON);	// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookAlien.png",					SPRITE_ID::SPRITE_LOOK_ALIEN);					// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookCameraIcon.png",			SPRITE_ID::SPRITE_LOOK_CAMERA_ICON);			// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookDetermination.png",			SPRITE_ID::SPRITE_LOOK_DETERMINATION);			// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookAlertnessIcon.png",			SPRITE_ID::SPRITE_LOOK_ALERTNESS_ICON);			// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookMiniAlertnessIcon.png",		SPRITE_ID::SPRITE_LOOK_MINI_ALERTNESS_ICON);	// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookMapIcon.png",				SPRITE_ID::SPRITE_LOOK_MAP_ICON);				// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookMapIconDescription.png",	SPRITE_ID::SPRITE_LOOK_MAP_ICON_DESCRIPTION);	// 
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/TutorialEmphasis/LookMapEnemyIcon.png",			SPRITE_ID::SPRITE_LOOK_MAP_ENEMY_ICON);			// 

	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/MissonStart.png",		SPRITE_ID::SPRITE_MISSION_START);	// 確定度ゲージの外枠画像

	// ポーズ用のスプライト
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Pause_Bg.png", SPRITE_ID::SPRITE_PAUSE_BG);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Return_Game.png", SPRITE_ID::SPRITE_RETURN_GAME);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Return_Title.png", SPRITE_ID::SPRITE_RETURN_TITLE);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Ask_return_title.png", SPRITE_ID::SPRITE_ASK_RETURN_TITLE);

	// リザルトシーンを作成するのに必要なスプライト
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Result_Bg.png", SPRITE_ID::SPRITE_RESULT_BG);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Documents.png", SPRITE_ID::SPRITE_DOCUMENTS);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Game_clear_UI.png", SPRITE_ID::SPRITE_GAME_CLEAR_UI);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Game_over_UI.png", SPRITE_ID::SPRITE_GAME_OVER_UI);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Evaluation_UI.png", SPRITE_ID::SPRITE_EVALUATION_UI);
	Sprite::GetInstance().Load
	(
		defaultPath + "free/SceneSprite/Evaluation_word_UI.png",
		SPRITE_ID::SPRITE_EVALUATION_WORD_UI,
		5,
		Point(5, 1),
		Point(300, 300)
	);

	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Awareness.png", SPRITE_ID::Awareness);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Photo_Count.png", SPRITE_ID::Photo_Count);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Escape_Count.png", SPRITE_ID::Escape_Count);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Game_over_retry_UI.png", SPRITE_ID::Game_over_retry_UI);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/A_Lot_Of_Coin_UI.png", SPRITE_ID::A_Lot_Of_Coin_);
	Sprite::GetInstance().Load(defaultPath + "free/SceneSprite/Less_Coin_.png", SPRITE_ID::Less_Coin_);


	Sprite::GetInstance().Load(defaultPath + "free/MapUI/player_mark32.png", SPRITE_ID::SPRITE_MAP_PLAYER);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/enemy_mark32.png", SPRITE_ID::SPRITE_MAP_ENEMY);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/player_mark64.png", SPRITE_ID::SPRITE_DESC_PLAYER);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/player_mark_text.png", SPRITE_ID::SPRITE_TEXT_PLAYER);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/enemy_mark64.png", SPRITE_ID::SPRITE_DESC_ENEMY);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/enemy_mark_text.png", SPRITE_ID::SPRITE_TEXT_ENEMY);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/nextevent_mark_text.png", SPRITE_ID::SPRITE_TEXT_REDPIN);
	Sprite::GetInstance().Load(defaultPath + "free/MapUI/event_mark_text.png", SPRITE_ID::SPRITE_TEXT_BLACKPIN);


	std::string texturepath = "res/Model/cgmodels/";
	Sprite::GetInstance().Load(texturepath + "buildings/Vending_machine_2.tif", SPRITE_ID::TEXTURE_VENDING_RED);
	Sprite::GetInstance().Load(texturepath + "buildings/Vending_machine_1.tif", SPRITE_ID::TEXTURE_VENDING_BLUE);

	Sprite::GetInstance().Load(texturepath + "buildings/House1_1.tif", SPRITE_ID::TEXTURE_HOUSE1_BLACK);
	Sprite::GetInstance().Load(texturepath + "buildings/House1_2.tif", SPRITE_ID::TEXTURE_HOUSE1_WHITE);
	Sprite::GetInstance().Load(texturepath + "buildings/House1_3_2Color.png", SPRITE_ID::TEXTURE_HOUSE1_BROWN);

	Sprite::GetInstance().Load(texturepath + "buildings/House1_1n.tif", SPRITE_ID::TEXTURE_NORMAL_HOUSE1_BLACK);
	Sprite::GetInstance().Load(texturepath + "buildings/House1_2n.tif", SPRITE_ID::TEXTURE_NORMAL_HOUSE1_WHITE);
	Sprite::GetInstance().Load(texturepath + "buildings/House1_3_5p.png", SPRITE_ID::TEXTURE_NORMAL_HOUSE1_BROWN);

	Sprite::GetInstance().Load(texturepath + "buildings/House2_1.tif", SPRITE_ID::TEXTURE_HOUSE2_WHITE);
	Sprite::GetInstance().Load(texturepath + "buildings/House2_2.tif", SPRITE_ID::TEXTURE_HOUSE2_BLACK);
	Sprite::GetInstance().Load(texturepath + "buildings/House2_3.tif", SPRITE_ID::TEXTURE_HOUSE2_RED);

	Sprite::GetInstance().Load(texturepath + "buildings/House2_1n.tif", SPRITE_ID::TEXTURE_NORMAL_HOUSE2_WHITE);
	Sprite::GetInstance().Load(texturepath + "buildings/House2_2n.tif", SPRITE_ID::TEXTURE_NORMAL_HOUSE2_BLACK);
	Sprite::GetInstance().Load(texturepath + "buildings/House2_3n.tif", SPRITE_ID::TEXTURE_NORMAL_HOUSE2_RED);

	Sprite::GetInstance().Load(defaultPath +"free/goal_mark32.png", SPRITE_ID::SPRITE_MAP_GOAL);
	Sprite::GetInstance().Load(defaultPath +"free/goal_mark64.png", SPRITE_ID::SPRITE_DESC_GOAL);
	Sprite::GetInstance().Load(defaultPath +"free/goal_mark_text.png", SPRITE_ID::SPRITE_TEXT_GOAL);

	Sprite::GetInstance().Load(defaultPath + "free/icon__gray1.png", SPRITE_ID::SPRITE_ALERT_FRAME_ICON);
	Sprite::GetInstance().Load(defaultPath + "free/icon__gray.png", SPRITE_ID::SPRITE_ALERT_GAUGE_ICON);

}

void LoadingScene::LoadModel()
{
	std::string defaultPath = "res/Model/";//全リソース共通パス
	std::string buildingPath = "cgmodels/buildings/";

	std::string characterPath = defaultPath + "cgmodels/characters/";

	Model::GetInstance().Load(characterPath + "Gray_model.mv1", MODEL_ID::MODEL_ENEMY);
	std::list<std::string> anims{
		characterPath + "Gray_kyara_taiki.mv1",					//0
		characterPath + "Gray_walk.mv1",					//1
		characterPath + "Gray_run.mv1",						//2
		characterPath + "Gray_modaeru.mv1",					//3
		characterPath + "Gray_erase_memory.mv1",			//4
		characterPath + "Gray_Kyara_jidanda.mv1",			//5
		characterPath + "Gray_fall_down2.mv1",				//6
		characterPath + "Gray_manhole_rescue2.mv1",			//7
		characterPath + "Gray_botanosu.mv1",				//8
		characterPath + "Gray_bunnageru_2.mv1",				//9
		characterPath + "Gray_modaeru.mv1",					//10
		characterPath + "Gray_check_left_and_right.mv1",	//11
		characterPath + "Tako_hat.mv1",						//12
		characterPath + "Gray_lookup.mv1",					//13
		characterPath + "Gray_udekumi_2.mv1",				//14
		characterPath + "Gray_manhole_armpartners2.mv1",	//15
		characterPath + "Gray_manhole_fall.mv1",			//16
		characterPath + "Gray_fall_down3.mv1",				//17
		characterPath + "Gray_rising_hat.mv1",              //18
		characterPath + "Gray_nozoki_1.mv1",                //19
		characterPath + "Gray_nozoki_2.mv1",                //20
		characterPath + "Gray_nozoki_3.mv1",                //21
		characterPath + "Gray_memory_delete.mv1",			//22
		characterPath + "Gray_kaiwa.mv1",                   //23
		characterPath + "gray_furimuki.mv1",                //24
		characterPath + "Gray_lookleft.mv1",                //25
		characterPath + "Gray_lookright.mv1",               //26
	};											
	AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_ENEMY, anims);

	Model::GetInstance().Load(characterPath + "mob/mob.mv1", MODEL_ID::MODEL_MOB);
	std::list<std::string> anims2{
		characterPath + "mob/Idle.mv1",					//0
		characterPath + "mob/Walking.mv1",					//1
	};
	AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_MOB, anims2);

	Model::GetInstance().Load(characterPath + "policemen.mv1", MODEL_ID::MODEL_POLICE);
	std::list<std::string> anims3{
		characterPath + "policemen_Idle.mv1",	//0
		characterPath + "policemen_run.mv1",	//1
		characterPath + "policemen_pointing.mv1",//2
		characterPath + "policemen_reaction.mv1"//3
	};
	AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_POLICE, anims3);

	Model::GetInstance().Load(characterPath + "mob/mob_phone.mv1", MODEL_ID::MODEL_MOB_PHONE);
	std::list<std::string> anims4{
		characterPath + "mob/mob_phone_Idle.mv1",					//0
		characterPath + "mob/mob_phone_walk.mv1",					//1
		characterPath + "mob/mob_surprised.mv1",					//2
		characterPath + "mob/mob_surprised_run.mv1",					//3
	};
	AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_MOB_PHONE, anims4);

	Model::GetInstance().Load(characterPath + "mob/mob_bag.mv1", MODEL_ID::MODEL_MOB_BAG);
	std::list<std::string> anims5{
		characterPath + "mob/mob_bag_Idle.mv1",					//0
		characterPath + "mob/mob_bag_walk.mv1",					//1
		characterPath + "mob/mob_surprised.mv1",					//2
		characterPath + "mob/mob_surprised_run.mv1",					//3
	};
	AnimLoader::getInstance().loadAnims(MODEL_ID::MODEL_MOB_BAG, anims5);

	Model::GetInstance().Load(defaultPath + "cgmodels/other/ManholeAna.mv1", MODEL_ID::MODEL_MANHOLE_ANA);

	Model::GetInstance().Load(characterPath + "policemen_Idle.mv1", MODEL_ID::MODEL_POLICE_IDLE);
	Model::GetInstance().Load(characterPath + "policemen_run.mv1", MODEL_ID::MODEL_POLICE_RUN);
	Model::GetInstance().Load(characterPath + "policemen_pointing.mv1", MODEL_ID::MODEL_POLICE_POINTING);
	Model::GetInstance().Load(characterPath + "policemen_reaction.mv1", MODEL_ID::MODEL_POLICE_REACTION);


	Model::GetInstance().Load(characterPath + "Barrier_1.mv1", MODEL_ID::MODEL_BARRIER);
	Model::GetInstance().Load(defaultPath + "cgmodels/other/Manhole.mv1", MODEL_ID::MODEL_MANHOLE);
	Model::GetInstance().Load(characterPath + "EnemyBeam.mv1", MODEL_ID::MODEL_ENEMY_BEARM);


	Model::GetInstance().Load(defaultPath + "models/car/car1/model.mv1", MODEL_ID::MODEL_CAR);
	Model::GetInstance().Load(characterPath + "Player/Player_hand.mv1", MODEL_ID::MODEL_ARM_1);
	Model::GetInstance().Load(characterPath + "Player/Player_hand_with_phone.mv1", MODEL_ID::MODEL_ARM_2);
	Model::GetInstance().Load(characterPath + "Player/Player_hand_with_phone_2.mv1", MODEL_ID::MODEL_ARM_3);
	Model::GetInstance().Load(characterPath + "Player/Player_hand_Newspapers.mv1", MODEL_ID::MODEL_ARM_4);
	Model::GetInstance().Load(defaultPath + "cgmodels/buildings/fish.mv1", MODEL_ID::MODEL_FISH);
	//Model::GetInstance().Load(defaultPath + "bird/bird.pmx", MODEL_ID::MODEL_ENEMY);
	Model::GetInstance().Load(defaultPath + "models/usausa/usausa.pmd", MODEL_ID::MODEL_CITIZEN_USAUSA);
	Model::GetInstance().Load(defaultPath + buildingPath + "Fish.mv1", MODEL_ID::MODEL_FISH);
	Model::GetInstance().Load(defaultPath + buildingPath + "Takoyakiya.mv1", MODEL_ID::MODEL_TAKOYAKI_YATAI);
	Model::GetInstance().Load(defaultPath + buildingPath + "Apartment_1.mv1", MODEL_ID::MODEL_APARTMENT_1);
	Model::GetInstance().Load(defaultPath + buildingPath + "Apartment_2.mv1", MODEL_ID::MODEL_APARTMENT_2);
	Model::GetInstance().Load(defaultPath + buildingPath + "Policebox.mv1", MODEL_ID::MODEL_KOUBAN);
	Model::GetInstance().Load(defaultPath + buildingPath + "Vending_machine.mv1", MODEL_ID::MODEL_ZIHANKI);
	Model::GetInstance().Load(defaultPath + buildingPath + "Kuruma_shingouki.mv1", MODEL_ID::MODEL_SHINGOU_CAR);
	Model::GetInstance().Load(defaultPath + buildingPath + "Hito_shingouki.mv1", MODEL_ID::MODEL_SHINGOU_HUMAN);
	Model::GetInstance().Load(defaultPath + buildingPath + "House_1.mv1", MODEL_ID::MODEL_HOUSE_1);
	Model::GetInstance().Load(defaultPath + buildingPath + "House_2.mv1", MODEL_ID::MODEL_HOUSE_2);
	Model::GetInstance().Load(defaultPath + buildingPath + "Smoking_area.mv1", MODEL_ID::MODEL_SMOKING_AREA);
	Model::GetInstance().Load(defaultPath + buildingPath + "TJunctionMap.mv1", MODEL_ID::MODEL_TJUNCTION_MAP);

	Model::GetInstance().Load(defaultPath + "cgmodels/characters/UFO.mv1", MODEL_ID::MODEL_UFO);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/cat.mv1", MODEL_ID::MODEL_CAT);

	Model::GetInstance().Load(defaultPath + "cgmodels/other/LightUfo.mv1", MODEL_ID::MODEL_UFO_LIGHT);

	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car_red.mv1", MODEL_ID::MODEL_CAR_RED);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_red_move1.mv1", MODEL_ID::MODEL_CAR_RED1);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_red_move2.mv1", MODEL_ID::MODEL_CAR_RED2);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_red_stop.mv1", MODEL_ID::MODEL_CAR_RED_LAMP);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car_blue.mv1", MODEL_ID::MODEL_CAR_BLUE);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_blue_move1.mv1", MODEL_ID::MODEL_CAR_BLUE1);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_blue_move2.mv1", MODEL_ID::MODEL_CAR_BLUE2);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_blue_stop.mv1", MODEL_ID::MODEL_CAR_BLUE_LAMP);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car_gray.mv1", MODEL_ID::MODEL_CAR_GRAY);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_gray_move1.mv1", MODEL_ID::MODEL_CAR_GRAY1);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_gray_move2.mv1", MODEL_ID::MODEL_CAR_GRAY2);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_gray_stop.mv1", MODEL_ID::MODEL_CAR_GRAY_LAMP);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car_white.mv1", MODEL_ID::MODEL_CAR_WHITE);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_white_move1.mv1", MODEL_ID::MODEL_CAR_WHITE1);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_white_move2.mv1", MODEL_ID::MODEL_CAR_WHITE2);
	Model::GetInstance().Load(defaultPath + "cgmodels/characters/Car/car_white_stop.mv1", MODEL_ID::MODEL_CAR_WHITE_LAMP);
	Model::GetInstance().Load(defaultPath + buildingPath + "Signal_for_roadway_blue.mv1", MODEL_ID::MODEL_SIGNAL_ROADWAY_GREEN);
	Model::GetInstance().Load(defaultPath + buildingPath + "Signal_for_roadway_red.mv1", MODEL_ID::MODEL_SIGNAL_ROADWAY_RED);
	Model::GetInstance().Load(defaultPath + buildingPath + "Signal_for_roadway_yellow.mv1", MODEL_ID::MODEL_SIGNAL_ROADWAY_YELLOW);
	Model::GetInstance().Load(defaultPath + buildingPath + "Signal_for_sidewalk_none.mv1", MODEL_ID::MODEL_SIGNAL_SIDEWALK_NONE);
	Model::GetInstance().Load(defaultPath + buildingPath + "Signal_for_sidewalk_blue.mv1", MODEL_ID::MODEL_SIGNAL_SIDEWALK_GREEN);
	Model::GetInstance().Load(defaultPath + buildingPath + "Signal_for_sidewalk_red.mv1", MODEL_ID::MODEL_SIGNAL_SIDEWALK_RED);

	Model::GetInstance().Load(characterPath + "EnemyBeam.mv1", MODEL_ID::MODEL_ENEMY_BEARM);

	Model::GetInstance().Load(characterPath + "gray_cap.mv1", MODEL_ID::MODEL_ENEMY_CAP);

	Model::GetInstance().Load2D("res/Sprite/free/smoke.png", MODEL_ID::SPRITE_SMOKE);
	
	Model::GetInstance().Load(characterPath + "gray_hologram_model.mv1", MODEL_ID::MODEL_GRAY_HOLO);
}


void LoadingScene::LoadEffect()
{
	//Modelクラスを利用したエフェクト
	std::string defaultPath = "res/Effekseer";//全リソース共通パス

}

void LoadingScene::LoadFont()
{
	std::string defaultPath = "res/Font/";//全リソース共通パス
	FontManager::GetInstance().AddFont(FONT_ID::FONT_COUNT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 50);
	FontManager::GetInstance().AddFont(FONT_ID::FONT_TEXT, defaultPath + "GN-Koharuiro_Sunray.ttf", "GN-こはるいろサンレイ", 50);
}

void LoadingScene::LoadBGM()
{
	std::string defaultPath = "res/Sound/bgm/";//全リソース共通パス
	Sound::GetInstance().LoadBGM(defaultPath + "free/Title_bgm.mp3", BGM_ID::SOUND_TITLE);
	Sound::GetInstance().LoadBGM(defaultPath + "free/Tutorial_bgm.mp3", BGM_ID::SOUND_TUTORIAL);
	Sound::GetInstance().LoadBGM(defaultPath + "free/Game_play_bgm.mp3", BGM_ID::SOUND_GAME);
	Sound::GetInstance().LoadBGM(defaultPath + "free/Getaway_bgm.mp3", BGM_ID::SOUND_GETAWAY);
	Sound::GetInstance().LoadBGM(defaultPath + "free/Game_result_bgm.mp3", BGM_ID::SOUND_RESULT);
	Sound::GetInstance().LoadBGM(defaultPath + "free/Game_clear_bgm.mp3", BGM_ID::SOUND_GAMECLEAR);
	Sound::GetInstance().LoadBGM(defaultPath + "free/Game_over_bgm.mp3", BGM_ID::SOUND_GAMEOVER);

}

void LoadingScene::LoadSE()
{
	std::string defaultPath = "res/Sound/se/";//全リソース共通パス
	Sound::GetInstance().LoadSE(defaultPath + "select.mp3", SE_ID::SELECT_SE);

	Sound::GetInstance().LoadSE(defaultPath + "free/Cursor_move_se.mp3", SE_ID::CURSOR_MOVE_SE);
	Sound::GetInstance().LoadSE(defaultPath + "free/Decision_se.mp3", SE_ID::DECISION_SE);

	Sound::GetInstance().LoadSE(defaultPath + "run.mp3", SE_ID::RUN_SE);
	Sound::GetInstance().LoadSE(defaultPath + "wind.mp3", SE_ID::WIND_SE);
	Sound::GetInstance().LoadSE(defaultPath + "jump.mp3", SE_ID::JUMP_SE);
	Sound::GetInstance().LoadSE(defaultPath + "land.mp3", SE_ID::LAND_SE);
	Sound::GetInstance().LoadSE(defaultPath + "hit.mp3", SE_ID::HIT_SE);
	Sound::GetInstance().LoadSE(defaultPath + "free/Siren_se.mp3", SE_ID::SIREN_SE);
	Sound::GetInstance().LoadSE(defaultPath + "free/Stamp_se.mp3", SE_ID::STAMP_SE);
	Sound::GetInstance().LoadSE(defaultPath + "free/Shutter_se.mp3", SE_ID::SHUTTER_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/alien_notice.mp3", SE_ID::NOTICE_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/alien_vc1.mp3", SE_ID::ALIAN_VOICE_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/manhole_ufo_abduction.mp3", SE_ID::UFO_ABDUCTION_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/neko/cat_vois.mp3", SE_ID::NEKO_VOICE_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/neko/alien_vc5.mp3", SE_ID::NEKO_GRAY_VOICE_SE);
	
	Sound::GetInstance().Load3DSE(defaultPath + "free/fall/fall_alien_down.mp3", SE_ID::FALL_DOWN_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/fall/fall_alien_extend.mp3", SE_ID::FALL_PICK_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/fall/alien_vc6.mp3", SE_ID::FALL_VOICE_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/Junction/intersection_car_brake.mp3", SE_ID::JUNCTION_CAR_BREAK_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/Junction/intersection_car_horn.mp3", SE_ID::JUNCTION_CAR_HORN_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/Junction/intersection_alien_guard.mp3", SE_ID::GUARD_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/Junction/car_horn_vc.mp3", SE_ID::JUNCTION_HORN_VC_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/Junction/car_huttobi_vc.mp3", SE_ID::JUNCTION_HUTTOBI_VC_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/manhole/manhole_alien_down.mp3", SE_ID::MANHOLE_ALIEN_DOWN);
	Sound::GetInstance().Load3DSE(defaultPath + "free/manhole/manhole_alien_fit.mp3", SE_ID::MANHOLE_ALIEN_FIT);

	Sound::GetInstance().Load3DSE(defaultPath + "free/police/police_alien_beam.mp3", SE_ID::POLICE_BEAM_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/smoke/smoking_alien_beam.mp3", SE_ID::SMOKE_BEAM_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/smoke/smoking_alien_charge.mp3", SE_ID::SMOKE_BEAM_CHARGE_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/VendingMachine/machine_alien_have.mp3", SE_ID::VEBDINGMACHINE_HAVE_SE);
	Sound::GetInstance().Load3DSE(defaultPath + "free/VendingMachine/machine_alien_throw.mp3", SE_ID::VEBDINGMACHINE_THROW_SE);

	Sound::GetInstance().Load3DSE(defaultPath + "free/hologram/hologram_alien_start.mp3", SE_ID::HOLOGRAM_ALEN_START);
	Sound::GetInstance().Load3DSE(defaultPath + "free/hologram/hologram_alien_start.mp3", SE_ID::HOLOGRAM_ALEN_TALK);
	Sound::GetInstance().Load3DSE(defaultPath + "free/VendingMachine/alien_vc2.mp3", SE_ID::VEBDINGMACHINE_ALIEN_VC1);

	Sound::GetInstance().Load3DSE(defaultPath + "free/police/police_return_vc.mp3", SE_ID::POLICE_RETURN_VC);
	Sound::GetInstance().Load3DSE(defaultPath + "free/police/police_run_vc.mp3", SE_ID::POLICE_RUN_VC);
	Sound::GetInstance().Load3DSE(defaultPath + "free/police/police_sakebi_vc.mp3", SE_ID::POLICE_SAKEBI_VC);
	Sound::GetInstance().Load3DSE(defaultPath + "free/police/police_stop_vc.mp3", SE_ID::POLICE_STOP_VC);

	Sound::GetInstance().Load3DSE(defaultPath + "free/manhole/alien_vc3.mp3", SE_ID::MANHOLE_ALIEN_VC1);
	Sound::GetInstance().Load3DSE(defaultPath + "free/manhole/alien_vc4.mp3", SE_ID::MANHOLE_ALIEN_VC2);



}

void LoadingScene::LoadShader()
{
	std::string defaultPath = "res/Shader/";//全リソース共通パス
	ShaderManager::getInstance().LoadShader(ShaderID::SKYBOX_SHADER, defaultPath + "SkyBoxVertexShader.cso", defaultPath + "SkyBoxPixelShader.cso");
	ShaderManager::getInstance().LoadShader(ShaderID::GAUGE_SHADER, defaultPath + "GaugePixelShader.cso");
	ShaderManager::getInstance().LoadShader(ShaderID::TILING_SHADER, defaultPath + "FloorTilingVertexShader.cso", defaultPath + "FloorTilingPixelShader.cso");
	ShaderManager::getInstance().CreateCBuff(ShaderID::TILING_SHADER, sizeof(Floor_CB));

	Sprite::GetInstance().Load("res/Model/cgmodels/buildings/tex.png", SPRITE_ID::SPRITE_TEXTURE);
}

void LoadingScene::LoadEtcetera()
{
	std::string defaultPath = "res/";//全リソース共通パス
	SetUseASyncLoadFlag(TRUE);
	Model::GetInstance().Load(defaultPath + "Field/Skybox/skydome.mv1", MODEL_ID::MODEL_SKYBOX);
	Model::GetInstance().Load(defaultPath + "Model/cgmodels/buildings/map.mv1", MODEL_ID::MODEL_STAGE);
	Model::GetInstance().Load(defaultPath + "Model/cgmodels/buildings/shadow.mv1", MODEL_ID::MODEL_SHADOW_TILE);
	Model::GetInstance().Load(defaultPath + "Model/cgmodels/buildings/OutOfFieldMap.mv1", MODEL_ID::MODEL_OUTOFFIELD);
	SetUseASyncLoadFlag(FALSE);

	WalkPathReader::getInstance().initialize();
	WalkPathReader::getInstance().load_citizenmap(defaultPath + "Data/citizenmap1.csv", defaultPath + "Data/citizenmap2.csv", defaultPath + "Data/citizenmap3.csv", defaultPath + "Data/citizenmap4.csv", defaultPath + "Data/citizenmap5.csv", defaultPath + "Data/citizenmap6.csv");
	WalkPathReader::getInstance().load_carmap(defaultPath + "Data/carmap1.csv", defaultPath + "Data/carmap2.csv", defaultPath + "Data/carmap3.csv", defaultPath + "Data/carmap4.csv", defaultPath + "Data/eventcar1.csv", defaultPath + "Data/eventcar2.csv", defaultPath + "Data/eventcar3.csv");
	WalkPathReader::getInstance().load_policemap(defaultPath + "Data/policemap.csv");

	constexpr int shadowrate = 4096;
	ShadowMap::GetInstance().Set(SHADOW_ID::GAME_SHADOW, Point{ shadowrate,shadowrate }, -Vector3::One);
	ShadowMap::GetInstance().SetRange(SHADOW_ID::GAME_SHADOW, Vector3{ 0.0f,-30.0f,0.0f }, Vector3{ 1500.0f,300.0f,1300.0f });

}

void LoadingScene::LoadSpriteAnim()
{
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j <= 9; ++j) {
			auto filepath = "res/Sprite/free/now_loading/now loading_0" + std::to_string(i) + std::to_string(j) + ".tif";
			int id = LoadGraph(filepath.c_str());
			_loadAnimList.push_back(id);
		}
	}

}
