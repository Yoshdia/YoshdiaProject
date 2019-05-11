#pragma once

class CEnemy;
class CEffectManager;
class CWave;
class CPlayerEnemyCommon;
class CSound;

#define ENEMY_NUM 30

class CEnemyManager
{
	CEnemy *enemy[ENEMY_NUM];
	CEffectManager *effectManager;
	CWave *wave;
public:
	CEnemyManager(int stageNum);
	~CEnemyManager();

	void Spawn();
	//エネミーをCPlayerEnemyCommon型にキャストして返す
	CPlayerEnemyCommon *GetEnemy(int num) { return (CPlayerEnemyCommon*)enemy[num]; }

	//更新
	void Update(CEffectManager *effect,CSound *sound);
    //enemyのFlagが倒れたときにランダム回数爆発させる
    void EnemyBomb(int enemyNum, CEffectManager *effect);
	//描写
	void Render();
	//enemyのshotReadyFlagを返す
	bool GetShotReady(int num);
	void SetShotReady(int num);
	int GetShotCheck(int num);
	int GetHp(int num);
	bool GetBossFlag(int num);
	//delete WaveをGame側で行えるように
	void StageChangeInitWave(int stageNum);
private:
	//敵の画像
	int enemyGraphic[8];

};