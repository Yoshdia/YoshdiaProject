#include"DxLib.h"
#include"Bullet.h"
#include"Define.h"
#include"VShot.h"

#define C_CHIPSIZE 4

CVBullet::CVBullet(int *tex, VECTOR & pPos, SBulletStatus & vStatu) :CBullet(vStatu)
{
	//pos = VGet(0,SCREEN_HEIGHT_HALF,0);
	pos = pPos;
	memcpy(bGraphic, tex, C_GRAPHIC * sizeof(tex[0]));

	status = { 0,0,0,vStatu.level };
}

void CVBullet::Update()
{
drawRad++;
	status.size+=6;
	float chipSizeX;
	float chipSizeY;
	GetGraphSizeF(*bGraphic, &chipSizeX, &chipSizeY);
	range = ((chipSizeX)*status.size);
	if (status.size >= 700)
	{
		flag = false;
	}
}
