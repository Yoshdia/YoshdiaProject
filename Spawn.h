#pragma once
#include"DxLib.h"

class CEnemy;

//スポーン情報基底クラス
class CSpawn
{
protected:
	CSpawn(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//スポーンする敵の数
	int spawnNum;
	//spawnNumが複数の場合、それらが湧く間隔
	int spawnInterval;
	//敵がスポーンする直前に建つフラグ
	bool spawnflg;
	//すべての敵を排出し終わったら建つフラグ
	bool spawnEnd;
	//CWaveから受け取る、排出座標と移動する向き
	VECTOR pos;
	VECTOR vPos;
	//排出される敵が発射する球の識別
	int bullet;
public:
	//cntがspawnIntervalを超えたときにspawnFlagを建たせる関数
	void Update();
	//spawnFlgが建っている状態で呼ばれる。生成したい敵を返す
	virtual CEnemy* Spawn() = 0;
	//spawnFlgを返す
	bool GetFlag() { return spawnflg; }
	//すべての敵を排出し終わったらdeleteされる
	bool GetEndFlag() { return spawnEnd; }
	//敵の画像
	int enemyGraphic;
};

//EnemyTurnが3体出現する
class CSpawn1 :public CSpawn
{
public:
	CSpawn1(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos,int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};

//EnemyStraightが3体出現する
class CSpawn2 :public CSpawn
{
public:
	CSpawn2(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
private:
	VECTOR bulletPos;
};

//EnemyAddSpeedが1体出現する
class CSpawn3 :public CSpawn
{
public:
	CSpawn3(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};

//Stage1のボス。撃破でステージチェンジ
class CSpawn4 :public CSpawn
{
public:
	CSpawn4(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};

//EnemySnakeが5体出現する
class CSpawn5 :public CSpawn
{
public:
	CSpawn5(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};

//急に加速してくる
class CSpawn6 :public CSpawn
{
public:
	CSpawn6(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};

//Stage2のボス。撃破でステージチェンジ
class CSpawn7 :public CSpawn
{
public:
	CSpawn7(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};

//Stage3のボス。撃破でステージチェンジ
class CSpawn8 :public CSpawn
{
public:
	CSpawn8(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//基底クラス参照
	CEnemy* Spawn();
};