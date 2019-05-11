#include"DxLib.h"
#include"Bullet.h"
#include"Define.h"
#include"XShot.h"

#define X_CHIPSIZE 4

CXBullet::CXBullet(int *tex, VECTOR & pPos, SBulletStatus & xStatu) :CBullet( xStatu)
{
	pos = pPos;
	memcpy(bGraphic, tex, X_GRAPHIC * sizeof(tex[0]));
	speed = 0;

	status.speed += 1;
	status.size += 4;
	range = (X_CHIPSIZE / 2) + (status.size / 4);
}

void CXBullet::Update()
{
    DrawRadPlus();
	Move();
	if (ComeOutScreen(pos, 100) == true)
	{
		flag = false;
	}
}

void CXBullet::Move()
{
	VECTOR vPos = VGet(1, 0, 0);
	speed += status.speed;
	normPos(&pos, &vPos, speed);
}
