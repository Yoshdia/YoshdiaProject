#include"EnemyBulletManager.h"
#include"EnemyManager.h"


CEnemyBulletManager::CEnemyBulletManager()
{
	//�e�S�Ă̏�����
	for (int num = 0; num < E_BULLET_NUM; num++)
	{
		bullet[num] = NULL;
	}
	LoadDivGraph("img/Shot/8Shots.png", (int)E_GRAPHIC, 5, 6, (int)8, (int)8, bulletGraphic, TRUE);
}

CEnemyBulletManager::~CEnemyBulletManager()
{
	//�e�S�Ă̍폜
	for (int num = 0; num < E_BULLET_NUM; num++)
	{
		delete bullet[num];
	}
}

void CEnemyBulletManager::Update(CEnemyManager *enemyManager, VECTOR playerPos)
{
	Shot(enemyManager, playerPos);
	for (int num = 0; num < E_BULLET_NUM; num++)
	{
		//NULL�łȂ��ꍇ
		if (bullet[num] != NULL)
		{
			bullet[num]->Update();
			//�e����ʊO�ɏo���ꍇ
			if (bullet[num]->GetFlag() == false)
			{
				//�폜���Ă���NULL������
				delete bullet[num];
				bullet[num] = NULL;
			}
		}
	}
}

int CEnemyBulletManager::NullCheck(int mixNum, int maxNum)
{
	for (int num = mixNum; num < maxNum; num++)
	{
		if (bullet[num] == NULL)
		{
			return num;
		}
	}
	//�S�Ă�bullet���X�V���̏ꍇNULL��Ԃ�
	return NULL;
}

void CEnemyBulletManager::Shot(CEnemyManager * enemyManager, VECTOR playerPos)
{
	for (int num = 0; num < ENEMY_NUM; num++)
	{
		if (enemyManager->GetEnemy(num) != NULL)
		{
			//�X�V���̓G�̔��ˏ����������Ă��邩���󂯎��
			bool ready = enemyManager->GetShotReady(num);
			//�󂯎�����甭�ˏ����t���O��|������
			enemyManager->SetShotReady(num);
			//���ˏ����������Ă���Ȃ炻��enemy�������̎�ނ��󂯎�肻�̋����Y�ݏo��
			if (ready)
			{
				//����enemy���������������擾
				int shotCheck = enemyManager->GetShotCheck(num);
				//bullet[num]��num�����߂�
				int bulletNum = NullCheck(0, E_BULLET_NUM);
				//�ǂ����甭�˂��邩�Aenemy�̍��W��Ԃ�
				VECTOR enemyPos = enemyManager->GetEnemy(num)->GetPos();
				//���𔭎˂���
				//shotCheck = 3;
				switch (shotCheck)
				{
				case(enemyShotNo):
					//enemyShotNo�̏ꍇ����r�o�����ɏI���
					break;
				case(enemyShotTracking):
					bullet[bulletNum] = new CEnemyBulletTracking(bulletGraphic, enemyPos, playerPos);
					break;
				case(enemyShotStraight):
					bullet[bulletNum] = new CEnemyBulletStraight(bulletGraphic, enemyPos);
					break;
				case(enemyShotRandam):
					bullet[bulletNum] = new CEnemyBulletRandam(bulletGraphic, enemyPos);
					break;
				case(eFirstBoss):
					//�ŏ��̃{�X�͉��������Ȃ�
					break;
				case(eSecondBoss):
					//2�Ԗڂ̃{�X�͒ǔ��e��3�A�˂���
					bullet[bulletNum] = new CEnemyBulletTracking(bulletGraphic, enemyPos, playerPos);
					break;
				case(eThirdBoss):
					//3�Ԗڂ̃{�X��1,2�Ԗڂ̃{�X�̐��\���Ƃ����悤��
					bullet[bulletNum] = new CEnemyBulletTracking(bulletGraphic, enemyPos, playerPos);
					break;
				}
			}
		}
	}
}

void CEnemyBulletManager::Render()
{
	for (int num = 0; num < E_BULLET_NUM; num++)
	{
		if (bullet[num] != NULL)
		{
			bullet[num]->Render();
		}
	}
}

