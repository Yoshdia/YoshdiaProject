#include"DxLib.h"
#include"Bullet.h"
#include"Define.h"
#include"ZShot.h"

#define Z_WIDE 96
#define Z_CHIP_SIZE 4

CZBullet::CZBullet(int *tex, VECTOR &pPos, SBulletStatus &zStatu, int uoCheck):CBullet(zStatu)
{
	firstPos = pPos;
	pos = pPos;
	memcpy(bGraphic, tex, Z_GRAPHIC * sizeof(tex[0]));
	range = (Z_CHIP_SIZE / 2) + (status.size / 4);
	underOnCheck=uoCheck;
}

void CZBullet::Update()
{
    DrawRadPlus();
	Move();
	if (ComeOutScreen(pos, 100)==true)
	{
		flag = false;
	}
}

void CZBullet::Move()
{
	VECTOR vPos = VGet(0, 0, 0);

	if (underOnCheck == eOnShot && pos.y > firstPos.y - Z_WIDE)
	{
		vPos.y -= 1.0f;
	}
	if (underOnCheck == eUnderShot && pos.y < firstPos.y + Z_WIDE)
	{
		vPos.y += 1.0f;
	}
	vPos.x += 1.0f;

	normPos(&pos, vPos, status.speed, status.speed);
}
