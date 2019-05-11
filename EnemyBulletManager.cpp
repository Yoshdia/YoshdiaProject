#include"EnemyBulletManager.h"
#include"EnemyManager.h"


CEnemyBulletManager::CEnemyBulletManager()
{
	//弾全ての初期化
	for (int num = 0; num < E_BULLET_NUM; num++)
	{
		bullet[num] = NULL;
	}
	LoadDivGraph("img/Shot/8Shots.png", (int)E_GRAPHIC, 5, 6, (int)8, (int)8, bulletGraphic, TRUE);
}

CEnemyBulletManager::~CEnemyBulletManager()
{
	//弾全ての削除
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
		//NULLでない場合
		if (bullet[num] != NULL)
		{
			bullet[num]->Update();
			//弾が画面外に出た場合
			if (bullet[num]->GetFlag() == false)
			{
				//削除してからNULLを入れる
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
	//全てのbulletが更新中の場合NULLを返す
	return NULL;
}

void CEnemyBulletManager::Shot(CEnemyManager * enemyManager, VECTOR playerPos)
{
	for (int num = 0; num < ENEMY_NUM; num++)
	{
		if (enemyManager->GetEnemy(num) != NULL)
		{
			//更新中の敵の発射準備が整っているかを受け取る
			bool ready = enemyManager->GetShotReady(num);
			//受け取ったら発射準備フラグを倒させる
			enemyManager->SetShotReady(num);
			//発射準備が整っているならそのenemyが撃つ球の種類を受け取りその球を産み出す
			if (ready)
			{
				//そのenemyが撃ちたい球を取得
				int shotCheck = enemyManager->GetShotCheck(num);
				//bullet[num]のnumを決める
				int bulletNum = NullCheck(0, E_BULLET_NUM);
				//どこから発射するか、enemyの座標を返す
				VECTOR enemyPos = enemyManager->GetEnemy(num)->GetPos();
				//球を発射する
				//shotCheck = 3;
				switch (shotCheck)
				{
				case(enemyShotNo):
					//enemyShotNoの場合球を排出せずに終わる
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
					//最初のボスは何も撃たない
					break;
				case(eSecondBoss):
					//2番目のボスは追尾弾を3連射する
					bullet[bulletNum] = new CEnemyBulletTracking(bulletGraphic, enemyPos, playerPos);
					break;
				case(eThirdBoss):
					//3番目のボスは1,2番目のボスの性能をとったように
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

