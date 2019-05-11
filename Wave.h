#pragma once

#define STAGE_NUM 3
#define WAVE_NUM 100
#define SPAWN_NUM 10
class CEnemy;
class CSpawn;
#include"Define.h"

struct SWave
{
	//�N���Q�[���J�E���g
	int time;
	//�ǂ�Spawn��N�����邩
	int whitchWave;
	//�ǂ�����N����
	float yPos;
	//�㉺�ǂ��炩��o�����邩
	float upDownCheck;
	//���E�ǂ��炩��o�����邩
	float rightLeftCheck;
};

class CWave
{
	CSpawn *spawn[SPAWN_NUM];
	SWave wave[WAVE_NUM];
public:
	CWave(int *pEnemyGraphic, int stage);
	~CWave();
	void Update();
	CEnemy* Spawn();
	bool GetAnySpawn() { return anySpawnFlag; };
	//Wave�����쐬����
	void SetWave(int stageNum);
	void InitWave(int stageNum);
private:
	//�G�̉摜 Spawn���ꂼ��ɓn��
	int enemyGraphic[8];
	//���ݍX�V����Spawn�̒��̂ǂꂩ�ɗN�����O�̂��̂��������ꍇ�Ɍ���
	bool anySpawnFlag;
	//�N�����O��Spawn��������*spawn�̎w�����L������
	int anySpawnNum;
	//�Q�[���J�E���g
	int gameCnt;
	//wave�ԍ�
	int waveNum;
	////Stage�ԍ�
	int stageNumber;
	//Wave�̓ǂݍ���
	void LoadWave();

	SWave waveLoad[3][WAVE_NUM];

};