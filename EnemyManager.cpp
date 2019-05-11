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
			//�{�X���o�������Ƃ��A���ݗ���Ă���BGM���~�߃{�X�p��BGM�𗬂�
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
				//enemy��Flag���|�ꂽ�Ƃ��Ƀ����_���񐔔���������
				EnemyBomb(num, effect);
				delete enemy[num];
				enemy[num] = NULL;
			}
		}

	}
}

//���j���̔��j�ő吔�ƍŏ���
#define BREAK_BOMB_MAX 3
#define BREAK_BOMB_MIN 2
//���j���̔��j���W�̍ő�ŏ��l
#define BREAK_BOMB_RANGE 32
//���j���̃T�C�Y�ő�l�ƍŏ��l
#define BREAK_BOMB_SIZE_MAX 10
#define BREAK_BOMB_SIZE_MIN 5
//���j���̔��j�ő�ҋ@����
#define BREAK_BOMB_DIRAY_MAX 30

void CEnemyManager::EnemyBomb(int enemyNum, CEffectManager * effect)
{
	//������
	int bombNum = GetRand(BREAK_BOMB_MAX) + BREAK_BOMB_MIN;
	//1~bombNum�̉񐔕������_���ȏꏊ�ɔ����𔭐�������
	for (int num = 0; num < bombNum; num++)
	{
		//pos����-16,0,+16�̂ǂꂩ������
		VECTOR bombPos = VAdd(enemy[enemyNum]->GetPos(), VGet((float)((GetRand(2) - 1) * BREAK_BOMB_RANGE), ((float)GetRand(2) - 1 * BREAK_BOMB_RANGE), 0));
		//���j�̑傫��
		float bombSize = (float)((GetRand(BREAK_BOMB_SIZE_MAX) / 10) + BREAK_BOMB_SIZE_MIN);
		int dirayTime = GetRand(BREAK_BOMB_DIRAY_MAX);
		effect->EffectSpawn(bombPos, eBomb, bombSize, 0, dirayTime);
		effect->EffectSpawn(enemy[enemyNum]->GetPos(), eAir, 2, 0, 0);
	}
}

void CEnemyManager::Spawn()
{
	//wave���X�V����
	wave->Update();
	//�N���������ł��Ă���spawn������Ƃ��ɉ������G��N������
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

