#include "SoundManager.h"
#include "DxLib.h"

SoundManager::SoundManager()
{
	bgmHandle = LoadSoundMem("Data/Sound/BGM.mp3");

	PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);
}

SoundManager::~SoundManager()
{
	StopSoundMem(bgmHandle);
	DeleteSoundMem(bgmHandle);
}