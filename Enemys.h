#pragma once

#include"Enemy.h"

//ふわりと曲がりながら前進してくる
class CEnemyTurn :public CEnemy
{
public:
	CEnemyTurn(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	//float speed;
	void Move();
	float addSpeed;
	void DrawRadMath();
};

//直進する
class CEnemyStraight :public CEnemy
{
public:
	CEnemyStraight(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	void DrawRadMath();
};

//加速しながら直進する
class CEnemyAddSpeed :public CEnemy
{
public:
	CEnemyAddSpeed(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	float addSpeed;
	void DrawRadMath();
};

//最初のボス
class CEnemyFirstBoss :public CEnemy
{
public:
	CEnemyFirstBoss(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	int moveCase;
	void DrawRadMath();
};

//蛇のように動く
class CEnemySnake :public CEnemy
{
public:
	CEnemySnake(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	float rad;
	void DrawRadMath();
};

//急襲してくる蛇のように動く敵
class CEnemySudden :public CEnemy
{
public:
	CEnemySudden(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	float rad;
	float speed;
	void DrawRadMath();
};

//2番目のボス
class CEnemySecondBoss :public CEnemy
{
public:
	CEnemySecondBoss(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	int moveCase;
	void BossShot();
	int shotCnt;
	void DrawRadMath();
};

//3番目のボス
class CEnemyThirdBoss :public CEnemy
{
public:
	CEnemyThirdBoss(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	int moveCase;
	void BossShot();
	int shotCnt;
	void DrawRadMath();
	int mmm;
	double mmmChange;
};

