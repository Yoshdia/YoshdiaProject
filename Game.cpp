#include"Manager.h"
#include"Player.h"
#include"Game.h"
#include"BulletManager.h"
#include"EffectManager.h"
#include"EnemyManager.h"
#include"EnemyBulletManager.h"
#include"Collision.h"
#include"BackGroundSpawn.h"
#include"LevelUp.h"
#include"Over.h"
#include"Clear.h"
#include"ItemSpawner.h"
#include"Sound.h" 
#include"BitMapFont.h"

CGame::CGame(CManager *pManager, int point) : CScene(pManager)
{
	nowStage = point;
	gameEnd = false;
	//pauseに渡す黒背景の画像
	blackScreenImg = LoadGraph("img/UI/BlackScreen.png");

	player = new CPlayer(pManager, point);
	bulletManager = new CBulletManager;
	effectManager = new CEffectManager;
	enemyManager = new CEnemyManager(nowStage);
	collision = new CCollision;
	enemyBulletManager = new CEnemyBulletManager;
	backGroundSpawn = new CBackGroundSpawn;
	itemSpawner = new CItemSpawner;
	backGroundSpawn->changeStageGraphic(nowStage);
	StartSpawnBackGround();
	pause = new CTutorial;
	finalCnt = 0;
	gameOver = false;
	filter = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
}

CGame::~CGame()
{
	delete player;
	delete bulletManager;
	delete effectManager;
	delete enemyManager;
	delete collision;
	delete enemyBulletManager;
	delete backGroundSpawn;
	delete itemSpawner;
}

void CGame::Update(CSound *sound)
{
	//レベルアップ中など、ゲームが停止する場合pauseにそれが入る
	if (pause == NULL)
	{
		//BGMが流れていない場合BGMを再生する
		if (sound->PlayCheck(eStageBGM) == false)
		{
			sound->PlaySounds(eStageBGM, DX_PLAYTYPE_LOOP);
		}
		CheckHit(sound);
		backGroundSpawn->Update();
		//playerへbulletManagerのアドレスを渡し発射できるようにする
		player->Update(bulletManager, effectManager, sound);
		bulletManager->Update();
		effectManager->Update();
		itemSpawner->Update();
		//enemyManagerへeffectManagerのアドレスを渡しエフェクトを作成できるようにする
		enemyManager->Update(effectManager, sound);
		enemyBulletManager->Update(enemyManager, player->GetPos());
		pause = player->CreateLevelUp();

		int playerHp = player->GetHp();

		if (player->GetHp() < 0)
		{
			player->SubAllHp();
			pause = new CChangeStagePause();
		}

		if (player->GetPlayerAllHp() < 0)
		{
			pause = new CWait;
			gameOver = true;
		}
		if (nowStage == 3)
		{
			pause = new CWait();
			gameEnd = true;
		}

	}
	else
	{
		effectManager->Update();
		if (pause->Update(effectManager, player, manager, sound) == true)
		{
			pause = NULL;
			ChangeScene(sound);
		}
	}
}

void CGame::Render(BitmapText *text)
{
	backGroundSpawn->Render(blackScreenImg);
	SetFontSize(16);
	player->Render(effectManager, text);
	enemyManager->Render();
	itemSpawner->Render();

	//エフェクトのa値を下げる
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	effectManager->Render(text);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	bulletManager->Render();
	enemyBulletManager->Render();

	////別画面filterにぼかしをかけたい描画をする
	SetDrawScreen(filter);
	ClearDrawScreen();

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	bulletManager->Render();
	effectManager->Render(text);
	enemyBulletManager->Render();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


	GraphFilter(filter, DX_GRAPH_FILTER_GAUSS, 16, 2000);

	SetDrawScreen(DX_SCREEN_BACK);

	SetDrawBlendMode(DX_BLENDMODE_ADD, 200);
	DrawGraph(0, 0, filter, FALSE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);



	if (pause != NULL)
	{
		pause->Render(player, blackScreenImg, text);
	}
}

void CGame::CheckHit(CSound *sound)
{
	//enemyとの当たり判定まとめ
	CheckHitEnemy(sound);
	CheckHitEnemyBullet(sound);
	CheckHitItemPlayer(sound);
}

//playerとenemyが衝突したときのダメージ
#define COLLISION_DAMAGE 1
//playerのzShotのレベルが一定以上のときに回復するAPの量
#define HEAL_AP_RATE 10

//enemyとの当たり判定まとめ
void CGame::CheckHitEnemy(CSound *sound)
{
	for (int enemyNum = 0; enemyNum < ENEMY_NUM; enemyNum++)
	{
		if (enemyManager->GetEnemy(enemyNum) != NULL)
		{
			//対Player
			CheckHitEnemyPlayer(enemyNum, sound);
			//対PlayerBullet
			CheckHitEnemyPlayerBullet(enemyNum, sound);
		}
	}
}

void CGame::CheckHitEnemyPlayer(int enemyNum, CSound *sound)
{
	if (collision->CheckCollision(player, enemyManager->GetEnemy(enemyNum), false) == true)
	{
		//playerとenemuにCOLLISION_DAMAGEを与える
		player->HitDamage(COLLISION_DAMAGE);
		enemyManager->GetEnemy(enemyNum)->HitDamage(COLLISION_DAMAGE);
		//Player座標とEnemy画像の中心bombPosに爆発を起こす
		BombSpawn(player->GetPos(), enemyManager->GetEnemy(enemyNum)->GetPos());
		if (enemyManager->GetHp(enemyNum) <= 0)
		{
			//撃破した敵がボスだった場合ステージを変化させる
			if (enemyManager->GetBossFlag(enemyNum) == true)
			{
				for (int num = 0; num < 20; num++)
				{
					VECTOR bossPos = enemyManager->GetEnemy(enemyNum)->GetPos();
					bossPos.x += (GetRand(3) - 1) * 16;
					bossPos.y += (GetRand(3) - 1) * 16;
					int size = GetRand(3) + 5;
					int dirayTime = (GetRand(10) * 10) + 60;
					effectManager->EffectSpawn(bossPos, eBomb, size, 0, dirayTime);
				}
				effectManager->FontSpawn(enemyManager->GetEnemy(enemyNum)->GetPos(), ePlusScore, 10000);
				player->PlusScore(10000);
				BreakEnemyChangeStage(sound);
				backGroundSpawn->changeStageGraphic(nowStage);
				StartSpawnBackGround();

			}
			sound->PlaySounds(eEnemyHitSound, DX_PLAYTYPE_BACK);
		}
	}
}

#define BREAK_ENEMY_PLUS_SCORE 1000
#define BREAK_ENEMY_CSHOT_BONUS 1000

#define ENEMY_BULLET_BOMB_SIZE_MAX 10
#define ENEMY_BULLET_BOMB_SIZE_MIN 5

void CGame::CheckHitEnemyPlayerBullet(int enemyNum, CSound *sound)
{
	for (int bulletNum = 0; bulletNum < BULLET_NUM; bulletNum++)
	{
		if (bulletManager->GetBullet(bulletNum) != NULL)
		{
			if (collision->CheckCollision(bulletManager->GetBullet(bulletNum), enemyManager->GetEnemy(enemyNum), false) == true)
			{
				//被弾した敵に1ダメージを与える
				enemyManager->GetEnemy(enemyNum)->HitDamage(1);
				//ダメージを与えた敵の体力が０以下だったらスコアを足す
				if (enemyManager->GetHp(enemyNum) <= 0)
				{
					int plusScore = 1000;
					//aStatusが2以上なら獲得スコアが増える
					int bulletAStatus = bulletManager->GetBullet(bulletNum)->GetaStatus();
					if (bulletAStatus > 2)
					{
						plusScore = 2000;
					}
					if (bulletAStatus > 3)
					{
						plusScore = 3000;
					}
					player->PlusScore(plusScore);
					effectManager->FontSpawn(enemyManager->GetEnemy(enemyNum)->GetPos(), ePlusScore, plusScore);
					//撃破した敵がボスだった場合ステージを変化させる
					if (enemyManager->GetBossFlag(enemyNum) == true)
					{
						for (int num = 0; num < 20; num++)
						{
							VECTOR bossPos = enemyManager->GetEnemy(enemyNum)->GetPos();
							bossPos.x += (GetRand(3) - 1) * 16;
							bossPos.y += (GetRand(3) - 1) * 16;
							int size = GetRand(3) + 5;
							int dirayTime = (GetRand(10) * 10) + 60;
							effectManager->EffectSpawn(bossPos, eBomb, size, 0, dirayTime);
						}
						effectManager->FontSpawn(enemyManager->GetEnemy(enemyNum)->GetPos(), ePlusScore, 10000);
						player->PlusScore(10000);
						BreakEnemyChangeStage(sound);
						backGroundSpawn->changeStageGraphic(nowStage);
						StartSpawnBackGround();

					}
					//一定の確率でアイテムを落とす
					int itemRand = GetRand(20);
					if (itemRand == 1)
					{
						itemSpawner->Spawn(enemyManager->GetEnemy(enemyNum)->GetPos());
					}
					sound->PlaySounds(eEnemyHitSound, DX_PLAYTYPE_BACK);
				}
				//VShot以外は消滅時に爆発を起こす
				if (bulletNum != vShot - 1)
				{
					effectManager->EffectSpawn(bulletManager->GetBulletPos(bulletNum), eBomb, 4, 1, 0);
				}
			}
		}
	}
}

#define E_BULLET_DAMAGE 1

//enemyBulletとの当たり判定まとめ
void CGame::CheckHitEnemyBullet(CSound *sound)
{
	for (int bulletNum = 0; bulletNum < E_BULLET_NUM; bulletNum++)
	{
		if (enemyBulletManager->GetBullet(bulletNum) != NULL)
		{
			CheckHitEnemyBulletPlayer(bulletNum, sound);
			//対VShot
			CheckHitEnemyBulletVShot(bulletNum, sound);
		}
	}
}

void CGame::CheckHitEnemyBulletPlayer(int bulletNum, CSound *sound)
{
	//対Player
	if (collision->CheckCollision(player,
		enemyBulletManager->GetBullet(bulletNum), false) == true)
	{
		//playerとenemuにCOLLISION_DAMAGEを与える
		player->HitDamage(E_BULLET_DAMAGE);
		enemyBulletManager->GetBullet(bulletNum)->HitAction();
		//Player座標とEnemy画像の中心bombPosに爆発を起こす
		BombSpawn(player->GetPos(), enemyBulletManager->GetBullet(bulletNum)->GetPos());
		sound->PlaySounds(ePlayerHitSound, DX_PLAYTYPE_BACK);
	}
}


void CGame::CheckHitEnemyBulletVShot(int bulletNum, CSound *sound)
{
	//vShotと衝突した球はその場に爆発を起こして消える
	if (bulletManager->GetBullet(vShot - 1) != NULL)
	{
		if (collision->CheckCollision(enemyBulletManager->GetBullet(bulletNum),
			bulletManager->GetBullet(vShot - 1), false) == true)
		{
			enemyBulletManager->GetBullet(bulletNum)->HitAction();
			//爆破のサイズをMIN-MAX+MINの中からランダムで所得し爆発させる
			float bombSize = (GetRand(ENEMY_BULLET_BOMB_SIZE_MAX) / 10) + (float)ENEMY_BULLET_BOMB_SIZE_MIN;
			effectManager->EffectSpawn(enemyBulletManager->GetBullet(bulletNum)->GetPos(), eBomb, bombSize, 1, 0);
		}
	}
}

void CGame::CheckHitItemPlayer(CSound *sound)
{
	for (int itemNum = 0; itemNum < ITEM_NUM; itemNum++)
	{
		if (itemSpawner->GetItem(itemNum) != NULL)
		{
			if (collision->CheckCollision(player, itemSpawner->GetItem(itemNum), true))
			{
				int item = itemSpawner->GetItem(itemNum)->GetItemNum();
				if (item == eScore)
				{
					player->PlusScore(5000);
					effectManager->FontSpawn(player->GetPos(), ePlusScore, 5000);
				}
				if (item == eShieldItem)
				{
					player->PlusHp();;
					player->PlusScore(1000);
					effectManager->FontSpawn(player->GetPos(), ePlusScore, 1000);
				}
				sound->PlaySounds(eItemGetSound, DX_PLAYTYPE_BACK);
			}
		}
	}
}

void CGame::BombSpawn(VECTOR o1Pos, VECTOR o2Pos)
{
	VECTOR bombPos = VSub(o1Pos, o2Pos);
	bombPos = VSub(o1Pos, bombPos);
	effectManager->EffectSpawn(bombPos, eBomb, 5, 1, 0);
}

void CGame::ChangeScene(CSound *sound)
{
	if (gameEnd == true)
	{
		//BGM系が流れていた場合それをすべて止める
		if (sound->PlayCheck(eStageBossBGM) == true)
		{
			sound->StopSound(eStageBossBGM);
		}
		if (sound->PlayCheck(eStageBGM) == true)
		{
			sound->StopSound(eStageBGM);
		}
		manager->scene = new CClear(manager);
		delete this;
	}
	else if (gameOver == true)
	{
		//BGM系が流れていた場合それをすべて止める
		if (sound->PlayCheck(eStageBossBGM) == true)
		{
			sound->StopSound(eStageBossBGM);
		}
		if (sound->PlayCheck(eStageBGM) == true)
		{
			sound->StopSound(eStageBGM);
		}
		manager->scene = new COver(manager);
		delete this;
	}
}

void CGame::BreakEnemyChangeStage(CSound *sound)
{
	//それまで流れていたボスＢＧＭはenemyManager内で止めるため、ここで通常のＢＧＭを流す

	nowStage += 1;
	if (nowStage == 3)
	{
		gameEnd = true;
	}
	else
	{
		sound->PlaySounds(eStageBGM, DX_PLAYTYPE_LOOP);
	}
	enemyManager->StageChangeInitWave(nowStage);
}

void CGame::StartSpawnBackGround()
{
	//開始時に産み出す隕石の数をランダムで指定しランダムな場所に設置
	int bgNum = GetRand(10) + 5;

	for (int num = 0; num < bgNum; num++)
	{
		float bgStarX = (float)GetRand(SCREEN_WIDTH);
		int bgGraphicNum = GetRand(4);
		backGroundSpawn->MoveBackGround(bgStarX, bgGraphicNum);
	}

	//星、惑星、ブラックホールの中からどれかを三つ設置する
	for (int num = 0; num < 3; num++)
	{
		float bgStarX = (float)GetRand(SCREEN_WIDTH);
		int bgGraphicNum = GetRand(7) + 4;
		backGroundSpawn->MoveBackGround(bgStarX, bgGraphicNum);
	}
}

