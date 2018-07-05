#include "Sound.h"
#include "../Define.h"
#include "../math/MathHelper.h"
#include <sstream>

static constexpr float SOUND_RANGE = 256.0f;

Sound::Sound():
	m_bgm_volume(BGMVOLUME), m_se_volume(SEVOLUME)
{
	
}

Sound::~Sound()
{
	InitSoundMem();
}

// ����������
void Sound::Initialize()
{

	InitSoundMem();
	m_BGMs.clear();
	m_SEs.clear();
	_play3DSoundList.clear();
	Set3DSoundOneMetre(10.0f);

	//dupSE.clear();
	for (auto& se : dupSE)
	{
		se = 0;
	}
}

// BGM��ǂݍ���
void Sound::LoadBGM(const std::string& filename, const BGM_ID& id, float volume)
{
	m_BGMs[id] = LoadSoundMem(filename.c_str());
	m_BGM_Volumes[id] = volume;
	SettingBGM(id);
}

// SE��ǂݍ���
void Sound::LoadSE(const std::string& filename, const SE_ID& id, float volume)
{
	m_SEs[id] = LoadSoundMem(filename.c_str());
	m_SE_Volumes[id] = volume;
	SettingSE(id);
}

// 3D(���̉���)�ōĐ�������SE��ǂݍ���
void Sound::Load3DSE(const std::string& filename, const SE_ID& id, float volume)
{
	SetCreate3DSoundFlag(TRUE);
	m_SEs[id] = LoadSoundMem(filename.c_str());
	m_SE_Volumes[id] = volume;
	SetCreate3DSoundFlag(FALSE);

	Set3DRadiusSoundMem(SOUND_RANGE, m_SEs[id]);

	SettingSE(id);
}

void Sound::DeleteAll()
{
	std::unordered_map<BGM_ID, int>::iterator bgmitr = m_BGMs.begin();
	while (bgmitr != m_BGMs.end()) {
		DeleteSoundMem(bgmitr->second);
		++bgmitr;
	}
	m_BGMs.clear();
	
	std::unordered_map<SE_ID, int>::iterator seitr = m_SEs.begin();
	while (seitr != m_SEs.end()) {
		DeleteSoundMem(seitr->second);
		++seitr;
	}
	m_SEs.clear();

	m_BGM_Volumes.clear();
	m_SE_Volumes.clear();
}

// �t�@�C������'.'��������菜��
std::string Sound::Split(const std::string& filename)
{
	std::string assetname;
	std::getline(
		std::stringstream(filename),
		assetname,
		'.'
	);
	return assetname;
}

// BGM��炷
void Sound::PlayBGM(const BGM_ID& id, int playtype)
{
	PlaySoundMem(m_BGMs[id], playtype);
}

// SE��炷
void Sound::PlaySE(const SE_ID& id, int playtype)
{
	if (IsPlaySE(id) && playtype == DX_PLAYTYPE_LOOP)
		return;

	ChangeVolumeSoundMem((int)((m_se_volume * m_SE_Volumes[id]) * 255), m_SEs[id]);
	PlaySoundMem(m_SEs[id], playtype);
}

void Sound::Play3DSE(const SE_ID & id, VECTOR* position, int playtype)
{
	Set3DPositionSoundMem(*position, m_SEs[id]);

	PlaySE(id, playtype);

	_play3DSoundList.push_back(std::make_pair(id, position));
}

void Sound::SetRate(const SE_ID & id, int rate)
{
	SetFrequencySoundMem(rate, m_SEs[id]);
}

void Sound::ReSetRate(const SE_ID & id)
{
	ResetFrequencySoundMem(m_SEs[id]);
}

int Sound::GetRate(const SE_ID & id)
{
	return GetFrequencySoundMem(m_SEs[id]);
}

void Sound::PlaySE_IsNotPlay(const SE_ID & id)
{
	if (IsPlaySE(id))return;

	PlaySE(id);
}

void Sound::PlaySEDuplicate(const SE_ID& id, int playtype)
{
	if (IsPlaySE(id) && playtype == DX_PLAYTYPE_LOOP)
		return;

	ChangeVolumeSoundMem((int)((m_se_volume * m_SE_Volumes[id]) * 255), m_SEs[id]);
	int dupHandle = DuplicateSoundMem(m_SEs[id]);
	PlaySoundMem(dupHandle, playtype);

	for (auto& se : dupSE)
	{
		if (se == 0)
		{
			se = dupHandle;
			return;
		}
	}
}

// BGM���~�߂�
void Sound::StopBGM()
{
	for (auto i : m_BGMs)
	{
		StopSoundMem(i.second);
	}
}

// SE���~�߂�
void Sound::StopSE(const SE_ID& id)
{
	StopSoundMem(m_SEs[id]);
}

void Sound::StopSE()
{
	for (auto i : m_SEs)
	{
		StopSoundMem(i.second);
	}
}

// BGM�����Ă��邩�ǂ������ׂ�
bool Sound::IsPlayBGM()
{
	for (auto i : m_BGMs)
	{
		if (CheckSoundMem(i.second))
		{
			return true;
		}
	}
	return false;
}

// SE�����Ă��邩�ǂ������ׂ�
bool Sound::IsPlaySE(const SE_ID& id)
{
	return CheckSoundMem(m_SEs[id]) == 1;
}

// �eBGM�̃{�����[����ݒ肷��
void Sound::SetBGMVolume(const BGM_ID& id, float volume)
{
	m_BGM_Volumes[id] = volume;
	SettingBGM(id);
}

// �eSE�̃{�����[����ݒ肷��
void Sound::SetSEVolume(const SE_ID& id, float volume)
{
	m_SE_Volumes[id] = volume;
	SettingSE(id);
}

// �eBGM�̃{�����[�����󂯎��
float Sound::IsBGMVolume(const BGM_ID& id)
{
	return m_BGM_Volumes[id];
}

// �eSE�̃{�����[�����󂯎��
float Sound::IsSEVolume(const SE_ID& id)
{
	return m_SE_Volumes[id];
}

// �S�Ă�BGM�̃{�����[����ݒ肷��
void Sound::SetAllBGMVolume(float volume)
{
	m_bgm_volume = volume;
	for (auto& i : m_BGMs)
		SettingBGM(i.first);
	m_bgm_volume = MathHelper::Clamp(m_bgm_volume, 0.0f, 1.0f);
}

// �S�Ă�SE�̃{�����[����ݒ肷��
void Sound::SetAllSEVolume(float volume)
{
	m_se_volume = volume;
	for (auto& i : m_SEs)
		SettingSE(i.first);
	m_se_volume = MathHelper::Clamp(m_se_volume, 0.0f, 1.0f);
}

// �S�Ă�BGM�̃{�����[�����󂯎��
float Sound::IsAllBGMVolume()
{
	return m_bgm_volume;
}

// �S�Ă�SE�̃{�����[�����󂯎��
float Sound::IsAllSEVolume()
{
	return m_se_volume;
}

void Sound::SetEventListenerPos(const VECTOR& position, const VECTOR& forward)
{

	Set3DSoundListenerPosAndFrontPos_UpVecY(position, forward);
}

void Sound::Update()
{
	for (auto& se : dupSE)
	{
		if (CheckSoundMem(se) == 0 && se != 0)
		{
			DeleteSoundMem(se);
			se = 0;
		}
	}
	_play3DSoundList.remove_if([&](auto& sound) {return (!IsPlaySE(sound.first)) || (sound.second == nullptr); });
	for (auto& s : _play3DSoundList) {
		auto c = *s.second;
		Set3DPositionSoundMem(*s.second, m_SEs[s.first]);
	}
}

void Sound::SettingBGM(const BGM_ID& id)
{
	ChangeVolumeSoundMem((int)((m_bgm_volume * m_BGM_Volumes[id]) * 255), m_BGMs[id]);
}

void Sound::SettingSE(const SE_ID& id)
{
	ChangeVolumeSoundMem((int)((m_se_volume * m_SE_Volumes[id]) * 255), m_SEs[id]);
}