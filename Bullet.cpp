#include"DxLib.h"
#include"Bullet.h"

CBullet::CBullet()
{
	flag = true;
}

CBullet::CBullet(SBulletStatus &Status)
{
	//graphic = new int[graphicNum];
	flag = true;
	status = Status;

}

void CBullet::Render()
{
	//3ƒŒƒxƒ‹‚±‚Æ‚É•`Ê‚·‚é‰æ‘œ‚ª•Ï‚í‚é
	int drawLevel = status.level / 3;
	DrawRotaGraph((int)pos.x, (int)pos.y,1.0 + (status.size / 2), drawRad, bGraphic[0+(drawLevel *5)],TRUE);
}

void CBullet::DrawRadPlus()
{
	drawRad++;
	if (drawRad >= 360)
	{
		drawRad = 0;
	}
}
