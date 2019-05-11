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
	//�������ׂă������ɓǂݍ���
	CSound();
	//����ǂݍ��񂾃��������J������
	~CSound();
	//�󂯎�������ʎq�̉����󂯎�����Đ��`���ōĐ�����
	void PlaySounds(int soundNum, int playType);
	//�󂯎�������ʎq�̉����Đ��������ׂ�
	bool PlayCheck(int soundNum);
	//�󂯎�������ʎq�̉��̍Đ����~������
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