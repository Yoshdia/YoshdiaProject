//#include"DxLib.h"
#include"Define.h"
#include"Enemys.h"
#include"math.h"
#include"DxLib.h"

CEnemyTurn::CEnemyTurn(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{

	hp = 1;
	hpMax = hp;
	interval = 150;
	size = 1.7f;
	CheckRange();


	addSpeedX = -2;
	addSpeed = -0.01f;

	addSpeedY = 3;
}

void CEnemyTurn::Move()
{
	addSpeedX += addSpeed;
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemyTurn::DrawRadMath()
{
	MoveRadMath();
}

/************************************************************************/
CEnemyStraight::CEnemyStraight(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 1;
	hpMax = hp;
	interval = 150;
	size = 1.7f;
	CheckRange();
	addSpeedX = -3;
	addSpeedY = -3;
}

void CEnemyStraight::Move()
{
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemyStraight::DrawRadMath()
{
	drawRad = -1.57f;
}

/************************************************************************/
CEnemyAddSpeed::CEnemyAddSpeed(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 1;
	hpMax = hp;
	interval = 150;
	size = 1.7f;
	CheckRange();

	addSpeed = -0.03f;
}

void CEnemyAddSpeed::Move()
{
	addSpeedX += addSpeed;

	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemyAddSpeed::DrawRadMath()
{
	MoveRadMath();
}

/************************************************************************/

CEnemyFirstBoss::CEnemyFirstBoss(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 30;
	hpMax = hp;
	interval = 100;
	moveCase = 0;
	size = 1.7f;
	CheckRange();
	gaugeGraphic = LoadGraph("img/UI/EnemyHp.png",TRUE);
}

void CEnemyFirstBoss::Move()
{
	switch (moveCase)
	{
		//moveCaseが0、最初は左からゆっくりと出現する
	case(0):
		intervalCnt = 0;
		vPos.x = -1;
		vPos.y = 0;
		addSpeedX = 0.5;
		addSpeedY = 0;
		if (pos.x < SCREEN_WIDTH - 96)
		{
			moveCase = 1;
			addSpeedX = 6;
			addSpeedY = 6;
		}
		break;

		//下へ
	case(1):
		vPos.x = 0;
		vPos.y = 1;
		if (pos.y > SCREEN_HEIGHT - 96)
		{
			moveCase = 2;
		}
		break;
		//左上へ
	case(2):
		vPos.x = -1;
		vPos.y = -1;
		if (pos.y < 96)
		{
			moveCase = 3;
		}
		break;
		//左下へ
	case(3):
		vPos.x = -1;
		vPos.y = 1;
		if (pos.x < 96)
		{
			moveCase = 4;
		}
		break;
		//上へ
	case(4):
		vPos.x = 0;
		vPos.y = -1;
		if (pos.y < 96)
		{
			moveCase = 5;
		}
		break;
		//右下へ
	case(5):
		vPos.y = 1;
		vPos.x = 1;
		if (pos.y > SCREEN_HEIGHT - 96)
		{
			moveCase = 6;
		}
		break;
		//右上へ
	case(6):
		vPos.x = 1;
		vPos.y = -1;
		if (pos.y < 96)
		{
			moveCase = 1;
		}
		break;
	}
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemyFirstBoss::DrawRadMath()
{
	MoveRadMath();
}

/************************************************************************/

CEnemySnake::CEnemySnake(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 1;
	hpMax = hp;
	interval = 150;
	size = 1.7f;
	CheckRange();

	rad = 90;
	vPos.x = -2 * vPos.x;
	addSpeedX = 4;
	addSpeedY = -4;
}

void CEnemySnake::Move()
{
	rad += 0.03f;
	vPos.y = (float)sin(rad);
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemySnake::DrawRadMath()
{
	MoveRadMath();
}

/************************************************************************/
CEnemySudden::CEnemySudden(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 1;
	hpMax = hp;
	interval = 150;
	size = 1.7f;
	CheckRange();

	rad = 90;
	//vPos.x = -6 * vPos.x;
	//addSpeedY = pvPos.y*-10;
	addSpeedX = -6;
	addSpeedY = 10;
}

void CEnemySudden::Move()
{
	rad += 0.03f;
	vPos.y = (float)sin(rad);
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemySudden::DrawRadMath()
{
	MoveRadMath();
}

/************************************************************************/
#define E_2_MULTI_INTERVAL 15
#define E_2_MULTI_NUM 5
#define E_2_INTERVAL 160

CEnemySecondBoss::CEnemySecondBoss(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 40;
	hpMax = hp;
	interval = E_2_MULTI_INTERVAL;
	moveCase = 0;
	size = 1.7f;
	CheckRange();

	shotCnt = 0;
	gaugeGraphic = LoadGraph("img/UI/EnemyHp.png", TRUE);
}

void CEnemySecondBoss::Move()
{
	switch (moveCase)
	{
	case(0):
		//最初は弾を発射しないためintervalを0にし続ける
		intervalCnt = 0;
		//最初は定まった位置までゆっくり移動して出現する
		vPos.x = -1;
		vPos.y = 0;
		addSpeedX = 0.5;
		addSpeedY = 0;
		if (pos.x < SCREEN_WIDTH - 96)
		{
			moveCase = 1;
			vPos.x = 0;
			vPos.y = 0;
			addSpeedX = 6;
			addSpeedY = 6;
		}
		break;
		//下へ
	case(1):
		vPos.y = 1;
		if (pos.y > SCREEN_HEIGHT - 96)
		{
			moveCase = 2;
			vPos.x = 0;
			vPos.y = 0;
		}
		break;
	case(2):
		vPos.y = -1;
		vPos.x = -1;
		if (pos.y < 96)
		{
			vPos.x = 0;
			vPos.y = 0;
			moveCase = 3;
		}
		break;
	case(3):
		vPos.y = 1;
		if (pos.y > SCREEN_HEIGHT - 96)
		{
			vPos.x = 0;
			vPos.y = 0;
			moveCase = 4;
		}
		break;
	case(4):
		vPos.x = 1;
		vPos.y = -1;
		if (pos.y < 96)
		{
			vPos.x = 0;
			vPos.y = 0;
			moveCase = 1;
		}
		break;
	}
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemySecondBoss::BossShot()
{
	if (intervalCnt >= interval)
	{
		shotCnt++;
		interval = E_2_MULTI_INTERVAL;
	}
	if (shotCnt > E_2_MULTI_NUM)
	{
		shotCnt = 0;
		interval = E_2_INTERVAL;
	}
}

void CEnemySecondBoss::DrawRadMath()
{
	drawRad = 0;
}

/************************************************************************/
CEnemyThirdBoss::CEnemyThirdBoss(int tex, VECTOR & pPos, VECTOR & pvPos, int bullet) :CEnemy(pPos, pvPos, E_CHIPSIZE, bullet, tex)
{
	*graphic = tex;
	hp = 70;
	hpMax = hp;
	interval = 100;
	moveCase = 0;
	size = 1.7f;
	CheckRange();
	mmm = 0;
	mmmChange = (hp / 3) ;
	gaugeGraphic = LoadGraph("img/UI/EnemyHp.png", TRUE);
}

void CEnemyThirdBoss::Move()
{
	switch    (mmm)
	{
	case(0):
		switch (moveCase)
		{
		case(0):
			intervalCnt = 0;
			vPos.x = -1;
			vPos.y = 0;
			addSpeedX = 0.5;
			addSpeedY = 0;
			if (pos.x < SCREEN_WIDTH - 96)
			{
				moveCase = 1;
				addSpeedX = 6;
				addSpeedY = 6;
			}
			break;
		case(1):
			vPos.x = 0;
			vPos.y = -1;
			if (pos.y < 96)
			{
				moveCase = 2;
			}
			break;
		case(2):
			vPos.y = 1;
			if (pos.y > SCREEN_HEIGHT-96)
			{
				moveCase = 1;
			}
			break;
		}

		if (hp < mmmChange*2)
		{
			intervalCnt = 0;
			vPos.x = 1;
			vPos.y = 0;
			addSpeedX = 2;
			addSpeedY = 1;
				DrawRadMath();
			if (pos.x > SCREEN_WIDTH + 32)
			{
				mmm = 1;
				moveCase = 0;
				pos.x = -32;
				pos.y = SCREEN_HEIGHT_HALF;
			}
		}
		break;
	case(1):
		switch (moveCase)
		{
		case(0):
			intervalCnt = 0;
			vPos.x = 1;
			vPos.y = 0;
			addSpeedX = 1;
			addSpeedY = 0;
			if (pos.x > 96)
			{
				moveCase = 1;
				addSpeedX = 6;
				addSpeedY = 6;
			}
			break;
		case(1):
			vPos.x = 0;
			vPos.y = 1;
			if (pos.y > SCREEN_HEIGHT-96)
			{
				moveCase = 2;
			}
			break;
		case(2):
			vPos.x = 0;
			vPos.y = -1;
			if (pos.y < 96)
			{
				moveCase = 1;
			}
			break;
		}

		if (hp < mmmChange)
		{
			intervalCnt = 0;
			vPos.x = -3;
			vPos.y = 0;
			addSpeedX = 1;
			addSpeedY = 1;
			DrawRadMath();
			if (pos.x < -32)
			{
				mmm = 2;
				moveCase = 0;
				pos.x = SCREEN_WIDTH + 32;
				pos.y = SCREEN_HEIGHT_HALF;
			}
		}
		break;
	case(2):
		switch (moveCase)
		{
			//moveCaseが0、最初は左からゆっくりと出現する
		case(0):
			intervalCnt = 0;
			vPos.x = -1;
			vPos.y = 0;
			addSpeedX = 1;
			addSpeedY = 0;
			if (pos.x < SCREEN_WIDTH - 96)
			{
				moveCase = 1;
				addSpeedX = 6;
				addSpeedY = 6;
			}
			break;

			//下へ
		case(1):
			vPos.x = 0;
			vPos.y = 1;
			if (pos.y > SCREEN_HEIGHT - 96)
			{
				moveCase = 2;
			}
			break;
			//左上へ
		case(2):
			vPos.x = -1;
			vPos.y = -1;
			if (pos.y < 96)
			{
				moveCase = 3;
			}
			break;
			//左下へ
		case(3):
			vPos.x = -1;
			vPos.y = 1;
			if (pos.x < 96)
			{
				moveCase = 4;
			}
			break;
			//上へ
		case(4):
			vPos.x = 0;
			vPos.y = -1;
			if (pos.y < 96)
			{
				moveCase = 5;
			}
			break;
			//右下へ
		case(5):
			vPos.y = 1;
			vPos.x = 1;
			if (pos.y > SCREEN_HEIGHT - 96)
			{
				moveCase = 6;
			}
			break;
			//右上へ
		case(6):
			vPos.x = 1;
			vPos.y = -1;
			if (pos.y < 96)
			{
				moveCase = 1;
			}
			break;
		}
		break;
	}
	normPos(&pos, vPos, addSpeedX, addSpeedY);
}

void CEnemyThirdBoss::BossShot()
{
	if (intervalCnt >= interval)
	{
		shotCnt++;
		interval = E_2_MULTI_INTERVAL;
	}
	if (shotCnt > E_2_MULTI_NUM)
	{
		shotCnt = 0;
		interval = E_2_INTERVAL;
	}
}

void CEnemyThirdBoss::DrawRadMath()
{
	if (moveCase > 0)
	{
		drawRad += 0.1f;
	}
}
