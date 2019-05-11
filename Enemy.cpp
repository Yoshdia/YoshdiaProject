#include "Enemy.h"
#include"Define.h"
#include"math.h"

CEnemy::CEnemy(VECTOR &pPos, VECTOR &pvPos, float rangeSize, int bullet, int pGraphic)
{
	damegedInvincibleFlag = false;
	range = rangeSize;
	flag = true;
	pos = pPos;
	vPos = pvPos;
	shotReadyflag = false;
	intervalCnt = 0;
	shotCheck = bullet;
	drawRad = 0;

	graphic = new int;
	*graphic = pGraphic;



	if (bullet == eFirstBoss || bullet == eSecondBoss || bullet == eThirdBoss)
	{
		bossFlag = true;
	}
	else
	{
		bossFlag = false;
	}
}

void CEnemy::Update()
{
	ShotReady();
	DamegeProcess(600);
	ComeOut();
	Move();
	DrawRadMath();
}


void CEnemy::ShotReady()
{
	intervalCnt++;
	if (bossFlag)
	{
		BossShot();
	}
	if (intervalCnt >= interval)
	{
		shotReadyflag = true;
		intervalCnt = 0;
	}
}

void CEnemy::ComeOut()
{
	//画面外に出るかHpがなくなるとフラグが倒れる
	if (ComeOutScreen(pos, 200) == true ||
		hp <= 0)
	{
		flag = false;
	}

}

void CEnemy::Render()
{
	DrawRotaGraph((int)pos.x, (int)pos.y, size, drawRad + 1.57, *graphic, TRUE);
	if (bossFlag == true)
	{
		RenderBossHp();
	}
}

void CEnemy::RenderBossHp()
{
	float p = (float)((hp * 100) / hpMax);

	//p /= 100;

	for (int num = 0; num < (int)p; num++)
	{
		DrawRotaGraph((int)pos.x + (num)-50, (int)pos.y - 96, 1.0, 0, gaugeGraphic, TRUE);
	}
}

void CEnemy::MoveRadMath()
{
	if (vPos.x != 0 && vPos.y != 0)
	{
		drawRad = atanf((vPos.y*addSpeedY) / (vPos.x*addSpeedX));
		if (vPos.x < 0)
		{
			drawRad -= 3.14f;
		}
	}
	else if (vPos.x == 0)
	{
		drawRad = asinf(vPos.y);
	}
	else if (vPos.y == 0)
	{
		drawRad = acosf(vPos.x);
	}
}

void CEnemy::CheckRange()
{
	float chipSizeX;
	float chipSizeY;
	GetGraphSizeF(*graphic, &chipSizeX, &chipSizeY);
	range = ((chipSizeX)*size) + 1;
}
