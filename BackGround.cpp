#include"BackGround.h"
#include"Define.h"


/***********************************************************/

//描画サイズと描画角度の増加数はランダムでとる
CMoveBackGround::CMoveBackGround(VECTOR pPos, int &pGraphic, bool spinFlag)
{
	pos = pPos;
	flag = true;
	drawSize = (GetRand(15)*0.1f) + 1;
	drawRad = 0;
	drawRadAdd = (GetRand(70) - 35)*0.0001f;
	//受け取った画像が星の場合に建つフラグが立っている場合回転速度を0にする
	if (spinFlag == true)
	{
		drawRadAdd = 0;
	}
	graphic = pGraphic;
}

void CMoveBackGround::Update()
{
	pos.x -= 0.5f;
	if (pos.x <= 0 - 50)
	{
		flag = false;
	}
}

void CMoveBackGround::Render()
{
	DrawRotaGraph((int)pos.x, (int)pos.y, drawSize, drawRad += drawRadAdd, graphic, TRUE);
}

/***********************************************************/
//場所を指定して動かない背景を描写する
CNoMoveBackGround::CNoMoveBackGround(int pGraphic, VECTOR pPos)
{
	pos = pPos;
	graphic=pGraphic;
	flag = true;
}

void CNoMoveBackGround::Update()
{
}


//受け取った座標からwidth,heightへ四角形を作る
void CNoMoveBackGround::Render()
{
	float drawSize = 6.0f;
	DrawRotaGraph((int)pos.x, (int)pos.y, drawSize, 0, graphic, TRUE);

}