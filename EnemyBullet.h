#pragma once


#include"Bullet.h"

class CEnemyBulletTracking :public CBullet
{
public:
	CEnemyBulletTracking(int *tex, VECTOR &pPos, VECTOR playerPos);
	void HitAction() {flag = false;	}
	void Update();
private:
	void Move();
	VECTOR vPos;
};

class CEnemyBulletStraight :public CBullet
{
public:
	CEnemyBulletStraight(int *tex, VECTOR &pPos);
	void HitAction() { flag = false; }
	void Update();
private:
	void Move();
};

class CEnemyBulletRandam :public CBullet
{
public:
	CEnemyBulletRandam(int *tex, VECTOR &pPos);
	void HitAction() { flag = false; }
	void Update();
private:
	void Move();
	VECTOR vPos;
};