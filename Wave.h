#pragma once

#define STAGE_NUM 3
#define WAVE_NUM 100
#define SPAWN_NUM 10
class CEnemy;
class CSpawn;
#include"Define.h"

struct SWave
{
	//湧くゲームカウント
	int time;
	//どのSpawnを湧かせるか
	int whitchWave;
	//どこから湧くか
	float yPos;
	//上下どちらから出現するか
	float upDownCheck;
	//左右どちらから出現するか
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
	//Wave情報を作成する
	void SetWave(int stageNum);
	void InitWave(int stageNum);
private:
	//敵の画像 Spawnそれぞれに渡す
	int enemyGraphic[8];
	//現在更新中のSpawnの中のどれかに湧く直前のものがあった場合に建つ
	bool anySpawnFlag;
	//湧く直前のSpawnが入った*spawnの指数を記憶する
	int anySpawnNum;
	//ゲームカウント
	int gameCnt;
	//wave番号
	int waveNum;
	////Stage番号
	int stageNumber;
	//Waveの読み込み
	void LoadWave();

	SWave waveLoad[3][WAVE_NUM];

};