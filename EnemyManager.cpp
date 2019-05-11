#include"EnemyManager.h"
#include"DxLib.h"
#include"Define.h"
#include"Spawn.h"
#include"Enemy.h"
#include"Wave.h"
#include"EffectManager.h"
#include"Sound.h"

CEnemyManager::CEnemyManager(int stageNum)
{
	for (int num = 0; num < ENEMY_NUM; num++)
	{
		enemy[num] = NULL;
	}
	int graphicNum = 0;
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/TurnEnemy.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/TripleEnemy.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/AddEnemy.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/FirstBoss.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/SnakeEnemy.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/SuddenEnemy.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/SecondBoss.png");
	enemyGraphic[graphicNum++] = LoadGraph("img/Space Shooter - 1/Ship/ThirdBoss.png");

	wave = new CWave(enemyGraphic, stageNum);
}

CEnemyManager::~CEnemyManager()
{
	for (int num = 0; num < ENEMY_NUM; num++)
	{
		delete enemy[num];
	}
	delete wave;
}


void CEnemyManager::Update(CEffectManager *effect, CSound *sound)
{
	Spawn();

	for (int num = 0; num < ENEMY_NUM; num++)
	{
		if (enemy[num] != NULL)
		{
			enemy[num]->Update();
			//ボスが出現したとき、現在流れているBGMを止めボス用のBGMを流す
			int bossCheck = enemy[num]->GetShotCheck();
			if (bossCheck == eFirstBoss || bossCheck == eSecondBoss || bossCheck == eThirdBoss)
			{
				if (sound->PlayCheck(eStageBGM) == true)
				{
					sound->StopSound(eStageBGM);
				}
				if (sound->PlayCheck(eStageBossBGM) == false)
				{
					effect->EffectSpawn(VGet(0, 0, 0), eBossReady, 1.0, 0, 0);
					sound->PlaySounds(eStageBossBGM, DX_PLAYTYPE_LOOP);
				}
			}
			if (enemy[num]->GetFlag() == false)
			{
				if (bossCheck == eFirstBoss || bossCheck == eSecondBoss || bossCheck == eThirdBoss)
				{
					if (sound->PlayCheck(eStageBossBGM) == true)
					{
						sound->StopSound(eStageBossBGM);
					}
				}
				//enemyのFlagが倒れたときにランダム回数爆発させる
				EnemyBomb(num, effect);
				delete enemy[num];
				enemy[num] = NULL;
			}
		}

	}
}

//撃破時の爆破最大数と最小数
#define BREAK_BOMB_MAX 3
#define BREAK_BOMB_MIN 2
//撃破時の爆破座標の最大最小値
#define BREAK_BOMB_RANGE 32
//撃破時のサイズ最大値と最小値
#define BREAK_BOMB_SIZE_MAX 10
#define BREAK_BOMB_SIZE_MIN 5
//撃破時の爆破最大待機時間
#define BREAK_BOMB_DIRAY_MAX 30

void CEnemyManager::EnemyBomb(int enemyNum, CEffectManager * effect)
{
	//爆発回数
	int bombNum = GetRand(BREAK_BOMB_MAX) + BREAK_BOMB_MIN;
	//1~bombNumの回数分ランダムな場所に爆発を発生させる
	for (int num = 0; num < bombNum; num++)
	{
		//posから-16,0,+16のどれかを引く
		VECTOR bombPos = VAdd(enemy[enemyNum]->GetPos(), VGet((float)((GetRand(2) - 1) * BREAK_BOMB_RANGE), ((float)GetRand(2) - 1 * BREAK_BOMB_RANGE), 0));
		//爆破の大きさ
		float bombSize = (float)((GetRand(BREAK_BOMB_SIZE_MAX) / 10) + BREAK_BOMB_SIZE_MIN);
		int dirayTime = GetRand(BREAK_BOMB_DIRAY_MAX);
		effect->EffectSpawn(bombPos, eBomb, bombSize, 0, dirayTime);
		effect->EffectSpawn(enemy[enemyNum]->GetPos(), eAir, 2, 0, 0);
	}
}

void CEnemyManager::Spawn()
{
	//waveを更新する
	wave->Update();
	//湧く準備ができているspawnがあるときに応じた敵を湧かせる
	if (wave->GetAnySpawn() == true)
	{
		for (int num = 0; num < ENEMY_NUM; num++)
		{
			if (enemy[num] == NULL)
			{
				enemy[num] = wave->Spawn();
				break;
			}
		}
	}
}

void CEnemyManager::Render()
{
	for (int num = 0; num < ENEMY_NUM; num++)
	{
		if (enemy[num] != NULL)
		{
			enemy[num]->Render();
		}
	}
}

bool CEnemyManager::GetShotReady(int num)
{
	return enemy[num]->GetShotReady();
}

void CEnemyManager::SetShotReady(int num)
{
	enemy[num]->SetShotReady();
}

int CEnemyManager::GetShotCheck(int num)
{
	return enemy[num]->GetShotCheck();
}

int CEnemyManager::GetHp(int num)
{
	return enemy[num]->GetHp();
}

bool CEnemyManager::GetBossFlag(int num)
{
	return enemy[num]->GetBossFlag();
}

void CEnemyManager::StageChangeInitWave(int stageNum)
{
	wave->InitWave(stageNum);
}

