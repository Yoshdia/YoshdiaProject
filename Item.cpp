#include "Item.h"

CItem::CItem(int tex, VECTOR pPos, int pItemNum)
{
	pos = pPos;
	flag = true;
	liveCnt = 0;
	itemNum = pItemNum;
	draw = false;
	changeCnt = 60;
	itemGraphic = new int;
	*itemGraphic = tex;
	float chipSizeX;
	float chipSizeY;
	GetGraphSizeF(tex, &chipSizeX, &chipSizeY);
	range = ((chipSizeX)*2.0f);
	drawRad = 0;
	drawRadAdd = (GetRand(70) - 35)*0.0001f;
}

CItem::~CItem()
{
	delete itemGraphic;
}

void CItem::Update()
{
	pos.x-=0.2f;
	liveCnt++;
	//1000カウントより点滅開始
	if (liveCnt > 700)
	{
		draw = true;
	}
	if (liveCnt > 700 + changeCnt)
	{
		draw = false;
	}
	if (liveCnt > 700 + changeCnt + changeCnt)
	{
		liveCnt = 700;
		changeCnt /= 1.5f;
	}
	if (changeCnt < 1)
	{
		flag = false;
	}
}

void CItem::Render()
{
	if (draw == false)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, 2.0, drawRad+= drawRadAdd, *itemGraphic, TRUE);
	}
}
