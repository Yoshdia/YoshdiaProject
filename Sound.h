#pragma once

enum eSound
{
	eCasolSound,
	eEnterSound,
	ePlayerHitSound,
	eEnemyHitSound,
	eItemGetSound,
	eLevelUpSound,
	eStatusLevelUpSound,
	eStageBGM,
	eStageBossBGM,
	eStageClearBGM,
	eStageOverBGM,
};

class CSound
{
public:
	//音をすべてメモリに読み込む
	CSound();
	//音を読み込んだメモリを開放する
	~CSound();
	//受け取った識別子の音を受け取った再生形式で再生する
	void PlaySounds(int soundNum, int playType);
	//受け取った識別子の音が再生中か調べる
	bool PlayCheck(int soundNum);
	//受け取った識別子の音の再生を停止させる
	void StopSound(int soundNum);
private:
	void SetSound(int *sound,int soundNum);

	int CasolSound;
	int EnterSound;
	int PlayerHitSound;
	int EnemyHitSound;
	int ItemGetSound;
	int LevelUpSound;
	int StatusLevelUpSound;
	int StageBGM;
	int StageBossBGM;
	int StageClearBGM;
	int StageOverBGM;
};