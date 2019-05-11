#pragma once

struct SBulletStatus
{
	float speed;
	float size;
	int aStatus;
	int level;
};


enum eOnUnderCheck
{
	eStraightShot,
	eOnShot,
	eUnderShot,
};

#include"Object.h"

class CBullet :public CObject
{
protected:
	//描写角度
	int drawRad;
	//生存フラグ。true＝生存
	bool flag;
	//Playerから受け取った弾のステータスをコピー
	SBulletStatus status;
	int bGraphic[30];
public:
	CBullet();
	CBullet(SBulletStatus &Status);
	int GetaStatus() { return status.aStatus; };
	//現在の生存フラグを返す
	bool GetFlag() { return flag; };
	//ステータス
	virtual void Update() = 0;
	//移動ルーチン
	virtual void Move() = 0;
	//描写
	void Render();
	//描写角度を増やし続ける
	void DrawRadPlus();
};