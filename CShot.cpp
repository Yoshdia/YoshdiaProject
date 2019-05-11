#include"DxLib.h"
#include"Bullet.h"
#include"Define.h"
#include"CShot.h"
#include"math.h"

#define C_CHIP_SIZE 4

CCBullet::CCBullet(int *tex, VECTOR & pPos, SBulletStatus & cStatu, int uoCheck) :CBullet(cStatu)
{
	pos = pPos;
	memcpy(bGraphic, tex, C_GRAPHIC * sizeof(tex[0]));
	range = (C_CHIP_SIZE / 2) + (status.size / 4);
	underOnCheck=uoCheck;
	//rad = -190;
}

void CCBullet::Update()
{
	DrawRadPlus();
	Move();
	if (ComeOutScreen(pos, 200) == out)
	{
		flag = false;
	}
}

void CCBullet::Move()
{
	VECTOR vPos = VGet(-1, 0, 0);

	if (underOnCheck == eOnShot)
	{
		vPos.y -= 0.5f;
	}
	if (underOnCheck == eUnderShot)
	{
		vPos.y += 0.5f;
	}
	//rad += 0.05f;
	//vPos = VGet((float)cos(rad) * 6, (float)sin(rad) * 6, 0);
	normPos(&pos, vPos, status.speed, status.speed);
}