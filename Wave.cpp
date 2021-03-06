#include"Enemy.h"
#include"Spawn.h"
#include"Wave.h"

enum EWave
{
	//EnemyTurnが3体出現する
	spawn1,
	//EnemyStraightが3体出現する
	spawn2,
	//EnemyAddSpeedが1体出現する
	spawn3,
	//FirstBoss
	spawn4,
	//EnemySnakeが7体
	spawn5,
	//EnemySudden
	spawn6,
	//enemySecond
	spawn7,
	//enemyThird
	spawn8,
};

enum eUpDownCheck
{
	eUp = -1,
	eLeft = -1,
	eStraight = 0,
	eDown = 1,
	eRight = 1
};

CWave::CWave(int *pEnemyGraphic, int stage)
{
	for (int num = 0; num < SPAWN_NUM; num++)
	{
		spawn[num] = NULL;
	}
	anySpawnFlag = false;
	anySpawnNum = 0;
	stageNumber = stage;
	LoadWave();
	InitWave(stageNumber);
	memcpy(enemyGraphic, pEnemyGraphic, 8 * sizeof(pEnemyGraphic[0]));
	waveNum = 0;
	gameCnt = 0;
}

#define HEIGHT_HALF0 0
#define HEIGHT_HALF1 SCREEN_HEIGHT_HALF / 2
#define HEIGHT_HALF2 SCREEN_HEIGHT_HALF
#define HEIGHT_HALF3 SCREEN_HEIGHT_HALF + (SCREEN_HEIGHT_HALF / 2)
#define HEIGHT_HALF4 SCREEN_HEIGHT



void CWave::InitWave(int stageNum)
{
	stageNumber = stageNum;
	SetWave(stageNumber);
	waveNum = 0;
	gameCnt = 0;
	anySpawnFlag = false;
	anySpawnNum = 0;
}

void CWave::SetWave(int stageNum)
{
	for (int num = 0; num < WAVE_NUM; num++)
	{
		wave[num] = waveLoad[stageNum][num];
	}
}

CWave::~CWave()
{
	for (int num = 0; num < SPAWN_NUM; num++)
	{
		delete spawn[num];
	}
}

void CWave::Update()
{
	gameCnt++;

	//ゲームカウントとwave番号が同じ場合whichWaveに応じたSpawnを新規作成する
	if (gameCnt == wave[waveNum].time)
	{
		for (int num = 0; num < SPAWN_NUM; num++)
		{
			if (spawn[num] == NULL)
			{
				float enemyX = 0;
				if (wave[waveNum].rightLeftCheck == eRight)
				{
					enemyX = SCREEN_WIDTH;
				}
				//どこから排出するかを受け取ったWave情報から受け取り渡す 
				VECTOR pos = VGet(enemyX, wave[waveNum].yPos, 0);
				//移動する向きも受け取るので渡す Downのときはそのまま、Upのときは-1をかけることで反転させる
				VECTOR vPos = { 0,0,0 };
				//その敵が何を発射するか　stageが0のときは球を撃たないenemyShotNoを渡す
				int enemyShot;
				switch (wave[waveNum].whitchWave)
				{
				case(spawn1):
					vPos = VGet(wave[waveNum].rightLeftCheck, wave[waveNum].upDownCheck, 0);
					enemyShot = enemyShotTracking;
					if (stageNumber == 0)
					{
						enemyShot = enemyShotNo;
					}
					spawn[num] = new CSpawn1(enemyGraphic[0], pos, vPos, enemyShot);
					break;
				case(spawn2):
					vPos = VGet(wave[waveNum].rightLeftCheck, wave[waveNum].upDownCheck, 0);
					enemyShot = enemyShotStraight;
					if (stageNumber == 0)
					{
						enemyShot = enemyShotNo;
					}
					spawn[num] = new CSpawn2(enemyGraphic[1], pos, vPos, enemyShot);
					break;
				case(spawn3):
					vPos = VGet(wave[waveNum].rightLeftCheck, 0, 0);
					enemyShot = enemyShotRandam;
					if (stageNumber == 0)
					{
						enemyShot = enemyShotNo;
					}
					spawn[num] = new CSpawn3(enemyGraphic[2], pos, vPos, enemyShot);
					break;
				case(spawn4):
					//ステージの終盤に現れる、撃破するとStageが変わる敵は、複数弾を発射することもあるため「撃破するとStageが変わる」ということを伝える
					enemyShot = eFirstBoss;
					spawn[num] = new CSpawn4(enemyGraphic[3], pos, vPos, enemyShot);
					break;
				case(spawn5):
					vPos = VGet(wave[waveNum].rightLeftCheck, wave[waveNum].upDownCheck, 0);
					enemyShot = enemyShotNo;
					spawn[num] = new CSpawn5(enemyGraphic[4], pos, vPos, enemyShot);
					break;
				case(spawn6):
					vPos = VGet(wave[waveNum].rightLeftCheck, wave[waveNum].upDownCheck, 0);
					enemyShot = enemyShotNo;
					spawn[num] = new CSpawn6(enemyGraphic[5], pos, vPos, enemyShot);
					break;
				case(spawn7):
					enemyShot = eSecondBoss;
					spawn[num] = new CSpawn7(enemyGraphic[6], pos, vPos, enemyShot);
					break;
				case(spawn8):
					enemyShot = eThirdBoss;
					spawn[num] = new CSpawn8(enemyGraphic[7], pos, vPos, enemyShot);
					break;
				}
				break;
			}
		}
		//次のWaveへ
		waveNum++;
	}

	//Spawnを更新する
	for (int num = 0; num < SPAWN_NUM; num++)
	{
		if (spawn[num] != NULL)
		{
			spawn[num]->Update();
			//湧く直前に建つspawnFlagが建っているとき
			if (spawn[num]->GetFlag() == true)
			{
				anySpawnFlag = true;
				//指数を記憶する
				anySpawnNum = num;
			}
			//spawnの中ですべての敵を輩出し終わったものがあった場合に開放してNULLを入れる
			if (spawn[num]->GetEndFlag() == true && spawn[num]->GetFlag() == false)
			{
				delete spawn[num];
				spawn[num] = NULL;
			}
		}
	}
}

CEnemy * CWave::Spawn()
{
	anySpawnFlag = false;
	//準備ができたspawnにどのEnemyを湧かせるか返させる
	return spawn[anySpawnNum]->Spawn();
}

void CWave::LoadWave()
{
	//waveLoad[0][waveNum++] = { ,spawn,HEIGHT_HALF, };

	int waveNum = 0;
	//Wave1情報
	{

		waveLoad[0][waveNum++] = { 100,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[0][waveNum++] = { 300,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[0][waveNum++] = { 600,spawn2,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 1000,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[0][waveNum++] = { 1400,spawn1,HEIGHT_HALF4,eUp,eRight };
		waveLoad[0][waveNum++] = { 1700,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 2000,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[0][waveNum++] = { 2300,spawn5,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 2900,spawn2,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 3100,spawn2,HEIGHT_HALF3,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 3700,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[0][waveNum++] = { 4100,spawn1,HEIGHT_HALF4,eUp,eRight };
		waveLoad[0][waveNum++] = { 4400,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 4800,spawn3,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 5100,spawn3,HEIGHT_HALF3,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 5500,spawn3,HEIGHT_HALF1, eStraight,eRight };
		waveLoad[0][waveNum++] = { 5600,spawn3,HEIGHT_HALF2, eStraight,eRight };
		waveLoad[0][waveNum++] = { 5700,spawn3,HEIGHT_HALF3, eStraight,eRight };
		
		waveLoad[0][waveNum++] = { 6400,spawn4,HEIGHT_HALF2,eStraight,eRight };
		
		waveLoad[0][waveNum++] = { 7100,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[0][waveNum++] = { 7500,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[0][waveNum++] = { 7900,spawn2,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 8800,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[0][waveNum++] = { 9400,spawn1,HEIGHT_HALF4,eUp,eRight };
		waveLoad[0][waveNum++] = { 10000,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 10600,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[0][waveNum++] = { 11200,spawn5,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 12400,spawn2,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 13000,spawn2,HEIGHT_HALF3,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 14200,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[0][waveNum++] = { 15000,spawn1,HEIGHT_HALF4,eUp,eRight };
		waveLoad[0][waveNum++] = { 15600,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[0][waveNum++] = { 16400,spawn3,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 17000,spawn3,HEIGHT_HALF3,eStraight,eLeft };
		waveLoad[0][waveNum++] = { 17800,spawn3,HEIGHT_HALF1, eStraight,eRight };
		waveLoad[0][waveNum++] = { 18000,spawn3,HEIGHT_HALF2, eStraight,eRight };
		waveLoad[0][waveNum++] = { 18200,spawn3,HEIGHT_HALF3, eStraight,eRight };
	}

	waveNum = 0;
	{
		waveLoad[1][waveNum++] = { 100,spawn5,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[1][waveNum++] = { 450,spawn5,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[1][waveNum++] = { 800,spawn5,HEIGHT_HALF3,eStraight,eRight };

		waveLoad[1][waveNum++] = { 1300,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[1][waveNum++] = { 1400,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[1][waveNum++] = { 1500,spawn3,HEIGHT_HALF3,eStraight,eRight };

		waveLoad[1][waveNum++] = { 1700,spawn2,HEIGHT_HALF2,eStraight,eRight };

		waveLoad[1][waveNum++] = { 2100,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[1][waveNum++] = { 2400,spawn1,HEIGHT_HALF4,eUp,eRight };

		waveLoad[1][waveNum++] = { 2700,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[1][waveNum++] = { 2800,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[1][waveNum++] = { 2900,spawn3,HEIGHT_HALF3,eStraight,eRight };

		waveLoad[1][waveNum++] = { 3100,spawn3,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[1][waveNum++] = { 3200,spawn3,HEIGHT_HALF2,eStraight,eLeft };
		waveLoad[1][waveNum++] = { 3300,spawn3,HEIGHT_HALF3,eStraight,eLeft };
					   
		waveLoad[1][waveNum++] = { 3500,spawn5,HEIGHT_HALF2,eStraight,eRight };
				   
		waveLoad[1][waveNum++] = { 3800,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[1][waveNum++] = { 4000,spawn1,HEIGHT_HALF4,eUp,eRight };

		waveLoad[1][waveNum++] = { 4300,spawn6,HEIGHT_HALF2,eUp,eRight };
		waveLoad[1][waveNum++] = { 4400,spawn6,HEIGHT_HALF1,eDown,eRight };
		waveLoad[1][waveNum++] = { 4500,spawn6,HEIGHT_HALF3,eUp,eRight };

		waveLoad[1][waveNum++] = { 4800,spawn6,HEIGHT_HALF2,eUp,eRight };
		waveLoad[1][waveNum++] = { 4900,spawn6,HEIGHT_HALF1,eDown,eRight };
		waveLoad[1][waveNum++] = { 5000,spawn6,HEIGHT_HALF3,eUp,eRight };

		waveLoad[1][waveNum++] = { 5400,spawn7,HEIGHT_HALF2,eStraight,eRight };

		waveLoad[1][waveNum++] = { 6100,spawn5,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[1][waveNum++] = { 6800,spawn5,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[1][waveNum++] = { 7500,spawn5,HEIGHT_HALF3,eStraight,eRight };

		waveLoad[1][waveNum++] = { 8500,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[1][waveNum++] = { 8700,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[1][waveNum++] = { 8900,spawn3,HEIGHT_HALF3,eStraight,eRight };

		waveLoad[1][waveNum++] = { 9300,spawn2,HEIGHT_HALF2,eStraight,eRight };

		waveLoad[1][waveNum++] = { 10100,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[1][waveNum++] = { 10700,spawn1,HEIGHT_HALF4,eUp,eRight };

		waveLoad[1][waveNum++] = { 11300,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[1][waveNum++] = { 11500,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[1][waveNum++] = { 11700,spawn3,HEIGHT_HALF3,eStraight,eRight };
								   
		waveLoad[1][waveNum++] = { 11900,spawn3,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[1][waveNum++] = { 12100,spawn3,HEIGHT_HALF2,eStraight,eLeft };
		waveLoad[1][waveNum++] = { 12300,spawn3,HEIGHT_HALF3,eStraight,eLeft };
								   
		waveLoad[1][waveNum++] = { 12700,spawn5,HEIGHT_HALF2,eStraight,eRight };
								   
		waveLoad[1][waveNum++] = { 13300,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[1][waveNum++] = { 13700,spawn1,HEIGHT_HALF4,eUp,eRight };
								   
		waveLoad[1][waveNum++] = { 14300,spawn6,HEIGHT_HALF2,eUp,eRight };
		waveLoad[1][waveNum++] = { 14500,spawn6,HEIGHT_HALF1,eDown,eRight };
		waveLoad[1][waveNum++] = { 14700,spawn6,HEIGHT_HALF3,eUp,eRight };
								   
		waveLoad[1][waveNum++] = { 15300,spawn6,HEIGHT_HALF2,eUp,eRight };
		waveLoad[1][waveNum++] = { 15500,spawn6,HEIGHT_HALF1,eDown,eRight };
		waveLoad[1][waveNum++] = { 15700,spawn6,HEIGHT_HALF3,eUp,eRight };
	}

	waveNum = 0;
	{
		waveLoad[2][waveNum++] = { 100,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 250,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 600,spawn3,HEIGHT_HALF3,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 800,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[2][waveNum++] = { 1000,spawn1,HEIGHT_HALF4,eUp,eRight };
				 
		waveLoad[2][waveNum++] = { 1400,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 1550,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 1700,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 1850,spawn3,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 2200,spawn2,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 2500,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 2750,spawn3,HEIGHT_HALF1,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 3100,spawn5,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 3450,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 3500,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 3700,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 3900,spawn3,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 4100,spawn2,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 4400,spawn3,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[2][waveNum++] = { 4500,spawn3,HEIGHT_HALF3,eStraight,eLeft };
		waveLoad[2][waveNum++] = { 4700,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 4800,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 4900,spawn3,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 5300,spawn5,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 5900,spawn8,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 7100,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 7400,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 7700,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 8000,spawn3,HEIGHT_HALF3,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 8500,spawn1,HEIGHT_HALF0,eDown,eRight };
		waveLoad[2][waveNum++] = { 8900,spawn1,HEIGHT_HALF4,eUp,eRight };
				 
		waveLoad[2][waveNum++] = { 9700,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 10000,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 10300,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 10600,spawn3,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 11300,spawn2,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 11600,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 12100,spawn3,HEIGHT_HALF1,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 12800,spawn5,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 13500,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 13600,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 14000,spawn3,HEIGHT_HALF2,eStraight,eRight };
		waveLoad[2][waveNum++] = { 14400,spawn3,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 14800,spawn2,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 15100,spawn3,HEIGHT_HALF1,eStraight,eLeft };
		waveLoad[2][waveNum++] = { 15200,spawn3,HEIGHT_HALF3,eStraight,eLeft };
		waveLoad[2][waveNum++] = { 15600,spawn3,HEIGHT_HALF1,eStraight,eRight };
		waveLoad[2][waveNum++] = { 15800,spawn3,HEIGHT_HALF3,eStraight,eRight };
		waveLoad[2][waveNum++] = { 16000,spawn3,HEIGHT_HALF2,eStraight,eRight };
				 
		waveLoad[2][waveNum++] = { 16800,spawn5,HEIGHT_HALF2,eStraight,eRight };


	}


}