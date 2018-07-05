#pragma once

// �v���C���[����̎��
enum class Operation_Type {

	ANY_BUTTON,					// �����ꂩ�̃{�^������(�X�e�B�b�N���͂͊܂߂Ȃ�)

	STICK_UP,					// ����͌��m�i���j���[�p�j�i���X�e�B�b�N�ł̓��́j
	STICK_DOWN,					// �����͌��m�i���j���[�p�j�i���X�e�B�b�N�ł̓��́j
	STICK_LEFT,					// �����͌��m�i���j���[�p�j�i���X�e�B�b�N�ł̓��́j
	STICK_RIGHT,				// �E���͌��m�i���j���[�p�j�i���X�e�B�b�N�ł̓��́j

	DECISION_BUTTON,			// ����{�^���i���j���[�p�j
	CANCEL_BUTTON,				// �L�����Z���{�^���i���j���[�p�j

	PLAYER_MOVE_STICK,			// �v���C���[�ړ����́i���X�e�B�b�N�ł̓��́j
	CHANGE_VIEW_POINT_STICK,	// ���_�؂�ւ����́i�E�X�e�B�b�N�ł̓��́j

	SHOW_MAP_BUTTON,			// �}�b�v�\���{�^��
	HOLD_CAMERA_BUTTON,			// �J�������\����{�^��
	TAKE_SHUTTER_BUTTON,		// �V���b�^�[��؂�{�^��
	HIDE_BUTTON,				// �B���{�^��
	DASH_BUTTON,				// ����{�^��
	RETURN_VIEW_POINT_BUTTON,	// ���_��߂��{�^��
	PAUSE_BUTTON,				// �|�[�Y�{�^��

	DEBUG_CLEAR_BUTTON,			// �f�o�b�N�p�N���A���s�{�^��
};

// �X�e�B�b�N���͂̎��
enum Stick_Input_Type {

	LEFT_STICK_ANY,			// ���X�e�B�b�N�̓���
	LEFT_STICK_UP,			// ���X�e�B�b�N�̏����
	LEFT_STICK_DOWN,		// ���X�e�B�b�N�̉�����
	LEFT_STICK_LEFT,		// ���X�e�B�b�N�̍�����
	LEFT_STICK_RIGHT,		// ���X�e�B�b�N�̉E����

	RIGHT_STICK_ANY,		// �E�X�e�B�b�N�̓���
	RIGHT_STICK_UP,			// �E�X�e�B�b�N�̏����
	RIGHT_STICK_DOWN,		// �E�X�e�B�b�N�̉�����
	RIGHT_STICK_LEFT,		// �E�X�e�B�b�N�̍�����
	RIGHT_STICK_RIGHT,		// �E�X�e�B�b�N�̉E����
};

// �g���K�[���͂̎��
enum Trigger_Input_Type {

	LEFT_TRIGGER,			// ���g���K�[�̓���
	RIGHT_TRIGGER,			// �E�g���K�[�̓���
};


//���f��ID
enum class MODEL_ID {
	MODEL_PLAYER,
	MODEL_SKYBOX,
	MODEL_STAGE,
	MODEL_SHADOW_TILE,
	MODEL_CAR,
	MODEL_ENEMY,
	MODEL_CITIZEN_USAUSA,
	MODEL_FISH,
	MODEL_TAKOYAKI_YATAI,
	MODEL_APARTMENT_1,
	MODEL_APARTMENT_2,
	MODEL_KOUBAN,
	MODEL_ZIHANKI,
	MODEL_SHINGOU_CAR,
	MODEL_SHINGOU_HUMAN,
	MODEL_HOUSE_1,
	MODEL_HOUSE_2,
	MODEL_ARM_1,
	MODEL_ARM_2,
	MODEL_ARM_3,
	MODEL_ARM_4,
	MODEL_SMOKING_AREA,
	MODEL_UFO,
	MODEL_UFO_LIGHT,
	SPRITE_QUESTION_FRAME,//�x���x�Q�[�W�g
	SPRITE_QUESTION_GAUGE,//�x���x�Q�[�W
	SPRITE_EXCLAMATION,
	SPRITE_NOTICED_LINE,	// �C�Â���
	MODEL_TJUNCTION_MAP,
	MODEL_CAT,
	MODEL_CAR_RED,
	MODEL_CAR_RED1,
	MODEL_CAR_RED2,
	MODEL_CAR_RED_LAMP,
	MODEL_CAR_BLUE,
	MODEL_CAR_BLUE1,
	MODEL_CAR_BLUE2,
	MODEL_CAR_BLUE_LAMP,
	MODEL_CAR_GRAY,
	MODEL_CAR_GRAY1,
	MODEL_CAR_GRAY2,
	MODEL_CAR_GRAY_LAMP,
	MODEL_CAR_WHITE,
	MODEL_CAR_WHITE1,
	MODEL_CAR_WHITE2,
	MODEL_CAR_WHITE_LAMP,
	MODEL_SIGNAL_ROADWAY_GREEN,
	MODEL_SIGNAL_ROADWAY_RED,
	MODEL_SIGNAL_ROADWAY_YELLOW,
	MODEL_SIGNAL_SIDEWALK_NONE,
	MODEL_SIGNAL_SIDEWALK_GREEN,
	MODEL_SIGNAL_SIDEWALK_RED,
	MODEL_MANHOLE,
	MODEL_BARRIER,			// �o���A
	MODEL_ENEMY_BEARM,		//�r�[��
	MODEL_POLICE,
	MODEL_POLICE_IDLE,
	MODEL_POLICE_RUN,
	MODEL_POLICE_POINTING,
	MODEL_POLICE_REACTION,
	MODEL_MOB,
	MODEL_ENEMY_CAP,
	MODEL_GRAY_HOLO,
	MODEL_MOB_PHONE,
	MODEL_MOB_BAG,
	SPRITE_SMOKE,
	MODEL_OUTOFFIELD,
	MODEL_MANHOLE_ANA

};
enum class SPRITE_ID {
	SPRITE_ACTION,//�A�N�V�������X�v���C�g
	SPRITE_CAMERAUI1,
	SPRITE_CAMERAUI2,
	SPRITE_FRAME,
	SPRITE_TEXTURE,

	SPRITE_MISSION_START,

	SPRITE_CONFIRM,//�m��x�Q�[�W
	SPRITE_CONFIRM_FRAME,//�m��x�Q�[�W�t���[��
	SPRITE_CONFIRM_NOMBER,//�m��x�Q�[�W�̐��l
	SPRITE_CAMERA_ICON,
	SPRITE_MAP_ICON,
	SPRITE_PIN,
	SPRITE_CHANCE,

	// �����̃V�[���p�̃X�v���C�g
	SPRITE_BLIND,				// ��ʂ��Â����邽�߂̉摜
	SPRITE_YES_UI,				// �g�͂��h�Ə����ꂽ���S
	SPRITE_NO_UI,				// �g�������h�Ə����ꂽ���S
	SPRITE_MENU_CURSOR,			// ���j���[�J�[�\��
	SPRITE_NUMBER_UI,			// �����Ɓ��F�������ꂽ�摜
	SPRITE_PRESS_ANY_BUTTON_UI, // �g�v���X�G�j�[�{�^���h�Ə����ꂽ���S

	// �G���g�����X�V�[���p�̃X�v���C�g
	SPRITE_TITLELOGO,
	SPRITE_SOZAI_TEIKYOU_TEXT,
	SPRITE_GAME_START,
	SPRITE_GO_TO_OPTION,
	SPRITE_EXIT,

	// �I�v�V�����p�X�v���C�g
	SPRITE_OPTION_CAMERA_SENSITIVITY,
	SPRITE_OPTION_BGM_VOLUME,
	SPRITE_OPTION_SE_VOLUME,
	SPRITE_OPTION_FLAME,
	SPRITE_OPTION_BAR,
	SPRITE_OPTION_CURSOR,

	// �`���[�g���A���p�X�v���C�g
	SPRITE_A_PUSH_1,
	SPRITE_A_PUSH_2,
	SPRITE_LT_PUSH,
	SPRITE_RT_PUSH,
	SPRITE_Y_PUSH,
	SPRITE_PUSH_ARROW,
	SPRITE_START_SKIP,
	SPRITE_LOOK_SPECIFIED_POINT_ICON,
	SPRITE_LOOK_ALIEN,
	SPRITE_LOOK_CAMERA_ICON,
	SPRITE_LOOK_DETERMINATION,
	SPRITE_LOOK_ALERTNESS_ICON,
	SPRITE_LOOK_MINI_ALERTNESS_ICON,
	SPRITE_LOOK_MAP_ICON,
	SPRITE_LOOK_MAP_ICON_DESCRIPTION,
	SPRITE_LOOK_MAP_ENEMY_ICON,

	// �|�[�Y�p�X�v���C�g
	SPRITE_PAUSE_BG, // �|�[�Y��ʂ̔w�i
	SPRITE_RETURN_GAME,  // �I�����ځF�Q�[���ɖ߂�
	SPRITE_RETURN_TITLE,  // �I�����ځF�^�C�g���ɖ߂�
	SPRITE_ASK_RETURN_TITLE,  // �^�C�g���ɖ߂�m�F�w�i

	// ���U���g�V�[���p�̃X�v���C�g
	SPRITE_RESULT_BG,	  // ���U���g�̔w�i
	SPRITE_DOCUMENTS,	  // �X�R�A��������鎆�̉摜
	SPRITE_GAME_CLEAR_UI, // �Q�[���N���A�̃��S
	SPRITE_GAME_OVER_UI,  // �Q�[���I�[�o�[�̃��S
	SPRITE_PLAY_TIME_UI,  // �g�o�ߎ��ԁh�Ə����ꂽ���S
	SPRITE_EVALUATION_UI, // �g�]���h�Ə����ꂽ���S
	SPRITE_EVALUATION_WORD_UI, // �g- D C B A S�h�Ə����ꂽ���S

	// 2D���\�[�X���X�g�ɏ�����Ă��Ȃ��X�v���C�g
	Awareness,			// �g�m��x�h�Ə����ꂽ���S
	Photo_Count,		// �g�B�e�񐔁h�Ə����ꂽ���S
	Escape_Count,		// �g�����񐔁h�Ə����ꂽ���S
	Game_over_retry_UI, // �g���g���C�h�Ə����ꂽ���S + �w�i���Â�����摜
	A_Lot_Of_Coin_,		// ��R�̃R�C�����`���ꂽ�摜
	Less_Coin_,			// �����̃R�C�����`���ꂽ�摜
	Stamp,				// ���q�̉摜

	SPRITE_MAP_PLAYER,
	SPRITE_MAP_ENEMY,
	SPRITE_DESC_PLAYER,
	SPRITE_TEXT_PLAYER,
	SPRITE_DESC_ENEMY,
	SPRITE_TEXT_ENEMY,
	SPRITE_TEXT_REDPIN,
	SPRITE_TEXT_BLACKPIN,

	TEXTURE_VENDING_RED,
	TEXTURE_VENDING_BLUE,

	TEXTURE_HOUSE1_BLACK,
	TEXTURE_HOUSE1_WHITE,
	TEXTURE_HOUSE1_BROWN,

	TEXTURE_NORMAL_HOUSE1_BLACK,
	TEXTURE_NORMAL_HOUSE1_WHITE,
	TEXTURE_NORMAL_HOUSE1_BROWN,

	TEXTURE_HOUSE2_WHITE,
	TEXTURE_HOUSE2_BLACK,
	TEXTURE_HOUSE2_RED,

	TEXTURE_NORMAL_HOUSE2_WHITE,
	TEXTURE_NORMAL_HOUSE2_BLACK,
	TEXTURE_NORMAL_HOUSE2_RED,

	SPRITE_MAP_GOAL,
	SPRITE_DESC_GOAL,
	SPRITE_TEXT_GOAL,

	SPRITE_CONFIRM_ALIAN0,
	SPRITE_CONFIRM_ALIAN1,
	SPRITE_CONFIRM_ALIAN2,
	SPRITE_CONFIRM_ALIAN3,
	SPRITE_CONFIRM_ALIAN4,
	SPRITE_CONFIRM_ALIAN5,
	SPRITE_CONFIRM_ALIAN6,
	SPRITE_CONFIRM_ALIAN7,
	SPRITE_CONFIRM_ALIAN8,
	SPRITE_CONFIRM_ALIAN9,
	SPRITE_CONFIRM_ALIAN10,

	SPRITE_BLACK,

	SPRITE_LOADING_DOT,

	SPRITE_ALERT_FRAME_ICON,
	SPRITE_ALERT_GAUGE_ICON,
};
enum class BGM_ID {
	SOUND_TITLE,
	SOUND_TUTORIAL,
	SOUND_GAME,
	SOUND_RESULT,
	SOUND_GETAWAY,
	SOUND_GAMECLEAR,
	SOUND_GAMEOVER,
	
};
enum class SE_ID {
	SELECT_SE,//�I��

	CURSOR_MOVE_SE,
	DECISION_SE,

	RUN_SE,//����
	WIND_SE,//�ړ�������
	JUMP_SE,//�W�����v
	LAND_SE,//���n
	HIT_SE,//�ڐG

	STAMP_SE,
	SIREN_SE,//�T�C����
	SHUTTER_SE,
	GUARD_SE,
	NOTICE_SE,
	ALIAN_VOICE_SE,
	NEKO_VOICE_SE,
	NEKO_GRAY_VOICE_SE,
	UFO_ABDUCTION_SE,

	FALL_DOWN_SE,
	FALL_PICK_SE,
	FALL_VOICE_SE,

	JUNCTION_CAR_HORN_SE,
	JUNCTION_CAR_BREAK_SE,
	JUNCTION_HORN_VC_SE,
	JUNCTION_HUTTOBI_VC_SE,

	POLICE_BEAM_SE,

	SMOKE_BEAM_CHARGE_SE,
	SMOKE_BEAM_SE,
	
	MANHOLE_ALIEN_DOWN,
	MANHOLE_ALIEN_FIT,



	VEBDINGMACHINE_HAVE_SE,
	VEBDINGMACHINE_THROW_SE,

	HOLOGRAM_ALEN_START,
	HOLOGRAM_ALEN_TALK,

	VEBDINGMACHINE_ALIEN_VC1,
	MANHOLE_ALIEN_VC1,
	MANHOLE_ALIEN_VC2,

	POLICE_STOP_VC,
	POLICE_RUN_VC,
	POLICE_SAKEBI_VC,
	POLICE_RETURN_VC

};
enum class FONT_ID {
	FONT_COUNT,//�J�E���g�p�t�H���g
	FONT_TEXT,
};
//Effekseer�𗘗p�����G�t�F�N�g�pID
enum class EFFECT_ID {

};

enum class SHADOW_ID {
	GAME_SHADOW,
};

//�Q�[�����ŗ��p����V�[����񋓂���
enum class SceneType {
	SCENE_LOADING,
	SCENE_ENTRANCE,
	SCENE_DEMOMOVIE,
	SCENE_TUTORIAL,
	SCENE_GAMEPLAY,
	SCENE_RESULT,
	SCENE_EXIT,//�_�~�[�V�[��
};

// �Q�[�����ŗ��p����T�u�V�[����񋓂���
enum class SubSceneType {

	NONE,
	TITLE,
	DISPLAY_PHOTO,
	SCORE_SHEET,
	MAIN_MENU,
	OPTION,
	PAUSE_MENU,
	DECISION_MENU,
};

enum class TransitionsAnimeType {
	None,
	FadeAnimation,
};

// �G���g�����X�V�[���̏�Ԃ̎��
enum EntranceState
{
	TITLE,
	MAINMENU,
	OPTION,
};

// �Q�[���v���C�V�[���̏�Ԃ̎��
enum PauseState
{
	PAUSE_MENU,
	PAUSE_OPTION,
};



//���b�Z�[�W�ɂ��Actor�Ԃ̑���
enum class EventMessage {
	Hit_Car,
	Hit_Bullet,
	Hide_Object,
	Hide_InCamera,
	Score_None,//�G�l�~�[�̃X�R�A��0�ɂ���
	Hit_Player,
	Hit_Enemy,
	Hit_Citizen,
	Emission,
	Hit_Object,
	Stop_Player,
	Aware_None,
	Abduct_Cat,
	Play_Smoke,
};

//Actor�̃O���[�v����
enum class ActorGroup {
	ETCETERA_ACTOR,//�Q�[���Ɋ֗^���Ȃ��A�N�^�[
	PLAYER_ACTOR,//�v���C���[
	CAR_ACTOR,//�ԃA�N�^�[
	POINT_ACTOR,//�`�F�b�N�|�C���g
	ENEMY_ACTOR,//�G
	CITIZEN_ACTOR,//�Z��
	ENEMY_HAT_ACTOR,	//�G�l�~�[�̖X�q
	UI_ACTOR,//UI,
	POLICE_ACTOR,	//�x�@
	ZIHANKI_ACTOR,	//���̋@
	EVENT_ACTOR,	//�C�x���g�n�̃A�N�^�[
	SIGNAL_ACTOR

};

// �����̃O���[�v�����i���̖��́j
enum class BuildingGroup {
	FISHSTORE=1,//��������
	POLICEBOX,//���
	TAKOYAKISHOP,//�����Ă���
	APARTMENT_1,//�}���V�����P
	APARTMENT_2,//�}���V�����Q
	FOODSTALL_1,//����P
	FOODSTALL_2,//����Q

	TRAFFICLIGHT_ROADWAY,//�ԓ��p�M���@
	TRAFFICLIGHT_SIDEWALK,//�����p�M���@
	VENDINGMACHINE_1,//�����̔��@�P
	VENDINGMACHINE_2,//�����̔��@�Q
	SHOPPINGSTREET_ARCH,//���X�X�̃A�[�`
	CLOCK,//���v
	SMOKING_AREA,//�i����
	HOUSE_1,//����1
	HOUSE_2,//����2
	BACKSTREET_RATI,//�H�n��
	BACKSTREET_KAIWA,//�H�n��
	KOUSATEN,		 //�����_
	MANHORU,			//�}���z�[��
	NEKO,
	SIGNAL_ROADWAY,
	SIGNAL_SIDEWALK1,
	SIGNAL_SIDEWALK2,
};

//�v���C���[�̉���A�N�V��������(��)
enum class EventAction_State {
	Null,//�A�N�V�����Ȃ�
	Car_Action, //�Ԃ̉���A�N�V����
	Clock_Action,//���v�̉���A�N�V����
	Vending_Action,//�����̔��@�̉���A�N�V����
	UnderVending_Action,//���̋@�̉��̉���A�N�V����
	Poster_Action,//�|�X�^�[�̉���A�N�V����
	TimeTable_Action,//�����\�̉���A�N�V����
};

// ��������C�x���g�̎��
enum class EventType {
	EVENT_NULL = 99,		// �_�~�[ �����N����Ȃ�
	EVENT_POLICE = 0,		// ��ԃC�x���g
	EVENT_TAKOYAKIYA,			// �����Ă����C�x���g
	EVENT_BACKSTREET_RATI,		// ���H�n�C�x���g�f�v
	EVENT_BACKSTREET_KAIWA,		// ���H�n�C�x���g��b
	EVENT_JUNCTION,			// �����_�C�x���g
	EVENT_VENDING,			// ���̋@�C�x���g
	EVENT_SMOKING,			// �i�����C�x���g
	EVENT_FISHSTORE,			// �����C�x���g
	EVENT_MANHORU,
	EVENT_NEKO				//�L�C�x���g
};

enum Signal_Type
{
	Signal_Red,
	Signal_Yellow,
	Signal_Green,
};
