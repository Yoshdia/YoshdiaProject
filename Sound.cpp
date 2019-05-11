#include "Sound.h"
#include"DxLib.h"

CSound::CSound()
{
	//CasolSound = LoadSoundMem("img/Space Shooter - 1/Sound/alert.wav");
	//EnterSound = LoadSoundMem("img/Space Shooter - 1/Sound/Gold3.wav");
	//PlayerHitSound = LoadSoundMem("img/Space Shooter - 1/Sound/shoot-destroy-2.wav");
	//EnemyHitSound = LoadSoundMem("img/Space Shooter - 1/Sound/shoot-destroy-1.wav");
	//ItemGetSound = LoadSoundMem("img/Space Shooter - 1/Sound/powerUp.wav");
	//LevelUpSound = LoadSoundMem("img/Space Shooter - 1/Sound/Gold1.wav");
	//StatusLevelUpSound = LoadSoundMem("img/Space Shooter - 1/Sound/Gold4.wav");

	//StageBGM = LoadSoundMem("img/Space Shooter - 1/Music/Shooting.OGG");
	//StageBossBGM = LoadSoundMem("img/Space Shooter - 1/Music/Boss.OGG");
	//StageClearBGM = LoadSoundMem("img/Space Shooter - 1/Music/Clear.OGG");
	//StageOverBGM = LoadSoundMem("img/Space Shooter - 1/Music/Over.OGG");
}

CSound::~CSound()
{
	DeleteSoundMem(CasolSound);
	DeleteSoundMem(EnterSound);
	DeleteSoundMem(PlayerHitSound);
	DeleteSoundMem(EnemyHitSound);
	DeleteSoundMem(ItemGetSound);
	DeleteSoundMem(LevelUpSound);
	DeleteSoundMem(StatusLevelUpSound);
	DeleteSoundMem(StageBGM);
	DeleteSoundMem(StageBossBGM);
	DeleteSoundMem(StageClearBGM);
	DeleteSoundMem(StageOverBGM);
}

void CSound::PlaySounds(int soundNum, int playType)
{
	int sound = 0;

	SetSound(&sound, soundNum);

	PlaySoundMem(sound, playType, TRUE);
}

bool CSound::PlayCheck(int soundNum)
{
	int sound = 0;

	SetSound(&sound, soundNum);

	return CheckSoundMem(sound);
}

void CSound::StopSound(int soundNum)
{
	int sound = 0;

	SetSound(&sound, soundNum);

	StopSoundMem(sound);
}

void CSound::SetSound(int * sound, int soundNum)
{
	switch (soundNum)
	{
	case(eCasolSound):
		*sound = CasolSound;
		break;
	case(eEnterSound):
		*sound = EnterSound;
		break;
	case(ePlayerHitSound):
		*sound = PlayerHitSound;
		break;
	case(eEnemyHitSound):
		*sound = EnemyHitSound;
		break;
	case(eItemGetSound):
		*sound = ItemGetSound;
		break;
	case(eLevelUpSound):
		*sound = LevelUpSound;
		break;
	case(eStatusLevelUpSound):
		*sound = StatusLevelUpSound;
		break;
	case(eStageBGM):
		*sound = StageBGM;
		break;
	case(eStageBossBGM):
		*sound = StageBossBGM;
		break;
	case(eStageClearBGM):
		*sound = StageClearBGM;
		break;
	case(eStageOverBGM):
		*sound = StageOverBGM;
		break;
	}
}
