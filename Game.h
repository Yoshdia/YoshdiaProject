#pragma once

class CPlayer;
class CBulletManager;
class CEffectManager;
class CEnemyManager;
class CCollision;
class CEnemyBulletManager;
class CBackGroundSpawn;
class CPause;
class CItemSpawner;
class CSound;
class BitmapText;

#include"Define.h"
#include"DxLib.h"


class CGame :public CScene
{
    CPlayer *player;
    CBulletManager *bulletManager;
    CEffectManager *effectManager;
    CEnemyManager *enemyManager;
    CCollision *collision;
	CEnemyBulletManager *enemyBulletManager;
	CBackGroundSpawn *backGroundSpawn;
	CPause *pause;
	CItemSpawner *itemSpawner;
public:
    CGame(CManager *pManager,int point);
    ~CGame();
    //更新
    void Update(CSound *sound);
    //描写
    void Render(BitmapText *text);
private:
    //体力ゲージのグラフィック。PlayerとEnemyに渡す
    int gaugeGraphic[G_GRAPHIC];
    //当たり判定を行う関数
    void CheckHit(CSound *sound);
    //敵との当たり判定まとめ
    void CheckHitEnemy(CSound *sound);
	//対プレイヤー
	void CheckHitEnemyPlayer(int enemyNum, CSound *sound);
	//対プレイヤーバレット
	void CheckHitEnemyPlayerBullet(int enemyNum, CSound *sound);
	//敵の球との当たり判定まとめ
	void CheckHitEnemyBullet(CSound *sound);
	//対プレイヤー
	void CheckHitEnemyBulletPlayer(int bulletNum, CSound *sound);
	//対VShot
	void CheckHitEnemyBulletVShot(int bulletNum, CSound *sound);
	//対アイテム
	void CheckHitItemPlayer(CSound *sound);
	//o1とo2の中心に爆発を起こす
	void BombSpawn(VECTOR o1Pos,VECTOR o2Pos);
	//半透明の黒背景
	int blackScreenImg;
	//シーン移行条件
	void ChangeScene(CSound *sound);
	//デバッグ用のシーン移行
	//int DebugScene();
	//現在のステージを記憶。最初はTitleから受け取る
	int nowStage;
	//すべてのステージをクリアした後の待機時間
	int finalCnt;
	//ゲーム終了。すべてのステージをクリアしたら建つ
	bool gameEnd;
	//敵を撃破したときにステージを変える関数
	void BreakEnemyChangeStage(CSound *sound);
	//ゲーム開始時に背景に星を描画させるための関数
	void StartSpawnBackGround();

	bool gameOver;
	int filter;
};