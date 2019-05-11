#pragma once

#include"Object.h"
//#define E_SPEED 3

class CEnemy :public CPlayerEnemyCommon
{
protected:
	VECTOR vPos;
	bool flag;
	void ComeOut();
	//hpの現在値は継承先にて宣言
	//弾の発射間隔
	int interval;
	//発射間隔カウント
	int intervalCnt;
	//発射準備
	bool shotReadyflag;
	//発射準備処理
	void ShotReady();
	//発射する球の種類
	int shotCheck;
	//そのエネミーがそのステージのボスかどうか。受け取ったbulletの値で判断する
	bool bossFlag;
	//描写される際のサイズ。チップサイズにrangeをかけた値
	float size;
	//描写される際の角度。基本的にボスが回転する
	float drawRad;

	float addSpeedX;
	float addSpeedY;
	//エネミーによって違う、移動によって変わるエネミーの向きを変更させる関数
	virtual void DrawRadMath()=0;
	//進行方向を見続ける関数
	void MoveRadMath();

	void CheckRange();

public:
	CEnemy(VECTOR &pPos, VECTOR &pvPos, float rangeSize, int bullet,int pGraphic);
	~CEnemy() { delete graphic; };
	void Update();
	virtual void Move() = 0;
	bool GetFlag() { return flag; };
	void Render();
	bool GetShotReady() { return shotReadyflag; }
	void SetShotReady() { shotReadyflag = false; }
	int GetShotCheck() { return shotCheck; };
	int GetHp() { return hp; }
	bool GetBossFlag() { return bossFlag; };
	virtual void BossShot() {};
	int hpMax;
	int gaugeGraphic;

	void RenderBossHp();
};
