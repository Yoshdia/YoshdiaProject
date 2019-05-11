#include"EnemyBullet.h"
#include"Define.h"
#include"math.h"

#define BULLET_A_SPEED 5

CEnemyBulletTracking::CEnemyBulletTracking(int *tex, VECTOR & pPos, VECTOR playerPos) :CBullet()
{
	pos = pPos;
	memcpy(bGraphic, tex, E_GRAPHIC * sizeof(tex[0]));
	range = (4 / 2) + (status.size / 4);
	status.size = 3;
	double vx = 0, vy = 0;
	//マウスの座標に向けて一定速度で進む
	double distance = sqrt((playerPos.x - pos.x)*(playerPos.x - pos.x) + (playerPos.y - pos.y)*(playerPos.y - pos.y));
	if (distance)
	{
		vx = (playerPos.x - pos.x) / distance;
		vy = (playerPos.y - pos.y) / distance;
	}
	vPos = VGet((float)vx, (float)vy, 0);
}

void CEnemyBulletTracking::Update()
{
	DrawRadPlus();
	Move();
	if (ComeOutScreen(pos, 100) == true)
	{
		flag = false;
	}
}

void CEnemyBulletTracking::Move()
{
	normPos(&pos, vPos, BULLET_A_SPEED, BULLET_A_SPEED);
}

/************************************************************************/

CEnemyBulletStraight::CEnemyBulletStraight(int *tex, VECTOR & pPos) :CBullet()
{
	pos = pPos;
	memcpy(bGraphic, tex, E_GRAPHIC * sizeof(tex[0]));
	range = (4 / 2) + (status.size / 4);
	status.size = 3;
}

void CEnemyBulletStraight::Update()
{
	DrawRadPlus();
	Move();
	if (ComeOutScreen(pos, 100) == true)
	{
		flag = false;
	}
}

void CEnemyBulletStraight::Move()
{
	VECTOR vPos = VGet(-5, 0, 0);

	pos = VAdd(pos, vPos);
}

/************************************************************************/
CEnemyBulletRandam::CEnemyBulletRandam(int *tex, VECTOR & pPos) :CBullet()
{
	pos = pPos;
	memcpy(bGraphic, tex, E_GRAPHIC * sizeof(tex[0]));
	range = (4 / 2) + (status.size / 4);
	status.size = 3;

	vPos = VGet(0, 0, 0);

	float rand = (float)GetRand(2) - 1;
	vPos.x = rand;
	rand = (float)(GetRand(2) - 1);
	vPos.y = rand;
}

void CEnemyBulletRandam::Update()
{
	DrawRadPlus();
	Move();
	if (ComeOutScreen(pos, 100) == true)
	{
		flag = false;
	}
}

void CEnemyBulletRandam::Move()
{
	if (vPos.x == 0 && vPos.y == 0)
	{
		vPos.x += -1;
	}
	normPos(&pos, vPos, 5,5);
}
