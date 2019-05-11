#pragma once

#include"Enemy.h"

//�ӂ��ƋȂ���Ȃ���O�i���Ă���
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

//���i����
class CEnemyStraight :public CEnemy
{
public:
	CEnemyStraight(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	void DrawRadMath();
};

//�������Ȃ��璼�i����
class CEnemyAddSpeed :public CEnemy
{
public:
	CEnemyAddSpeed(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	float addSpeed;
	void DrawRadMath();
};

//�ŏ��̃{�X
class CEnemyFirstBoss :public CEnemy
{
public:
	CEnemyFirstBoss(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	int moveCase;
	void DrawRadMath();
};

//�ւ̂悤�ɓ���
class CEnemySnake :public CEnemy
{
public:
	CEnemySnake(int tex, VECTOR &pPos, VECTOR &pvPos, int bullet);
private:
	void Move();
	float rad;
	void DrawRadMath();
};

//�}�P���Ă���ւ̂悤�ɓ����G
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

//2�Ԗڂ̃{�X
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

//3�Ԗڂ̃{�X
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

