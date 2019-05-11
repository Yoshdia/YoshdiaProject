#include "DxLib.h"
#include "Effect.h"
#include "Define.h"
#include<string.h>
#include"BitMapFont.h"

CEffect::CEffect(int liveCnt, VECTOR pPos)
{
	graphicNumber = liveCnt;
	flag = true;
	animCnt = -1;
	animSize = 0;
	animRad = 0;
	pos = pPos;
	dirayCnt = 0;
	dirayTime = 0;
	dirayOk = true;
}

CEffect::CEffect(int graphicNum, double size, double rad, VECTOR pPos, int diray)
{
	//グラフィック枚数をコピー
	graphicNumber = graphicNum;
	flag = true;
	//Renderよりも先にUpdateが呼ばれるため0で初期化すると1枚目からスタートしてしまうので-1で初期化
	animCnt = -1;
	animSize = size;
	animRad = rad;
	pos = pPos;
	dirayCnt = 0;
	dirayTime = diray;
	dirayOk = false;
	//graphic = new int[graphicNumber];
}

void CEffect::Update()
{
	dirayCnt++;

	if (dirayCnt >= dirayTime)
	{
		dirayOk = true;
	}
	if (dirayOk == true)
	{
		//アニメーションカウント
		animCnt++;

		//アニメーションが再生し終わったら生存フラグを倒す
		if (animCnt == graphicNumber)
		{
			flag = false;
		}
	}
}


/******敵が撃破されたときに爆破エフェクトを出す******/

CBomb::CBomb(VECTOR &pPos, int *tex, double &size, double &rad, int diray) :CEffect(EF_BOMB_GRAPHIC, size, rad, pPos, diray)
{
	memcpy(graphic, tex, EF_BOMB_GRAPHIC * sizeof(tex[0]));
	graphicNumber *= 3;
}

void CBomb::Render(BitmapText *text)
{
	if (dirayOk == true)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, animSize, animRad, graphic[animCnt / 3], TRUE);
	}
}

/******敵が撃破されたときに空気の爆発エフェクトを出す******/

CAirBomb::CAirBomb(VECTOR &pPos, int *tex, double &size, double &rad, int diray) :CEffect(EF_BOMB_GRAPHIC, size, rad, pPos, diray)
{
	memcpy(graphic, tex, EF_AIR_GRAPHIC * sizeof(tex[0]));
	graphicNumber *= 5;
}

void CAirBomb::Render(BitmapText *text)
{
	if (dirayOk == true)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, animSize, animRad, graphic[animCnt / 5], TRUE);
	}
}

/******ステータスのレベルアップが行われたときにエフェクトを出す******/

CStatusLevelUp::CStatusLevelUp(VECTOR &pPos, int *tex, double &size, double &rad, int diray) :CEffect(EF_STATUS_LEVEL_GRAPHIC, size, rad, pPos, diray)
{
	memcpy(graphic, tex, EF_STATUS_LEVEL_GRAPHIC * sizeof(tex[0]));
	graphicNumber *= 3;
}

void CStatusLevelUp::Render(BitmapText *text)
{
	if (dirayOk == true)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, animSize, animRad, graphic[EF_STATUS_LEVEL_GRAPHIC - (animCnt / 3)], TRUE);
	}
}

#define FONT_EF_LIVE 40
/******敵を撃破したときに+1000等の文字を出す******/
CPlusScoreFont::CPlusScoreFont(VECTOR &pPos, int plusScore) : CEffect(FONT_EF_LIVE, pPos)
{
	score = plusScore;
}

void CPlusScoreFont::Render(BitmapText *text)
{
	if (score == 1000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+1000");
	}
	if (score == 2000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+2000");
	}
	if (score == 3000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+3000");
	}
	if (score == 5000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+5000");
	}
}

/******レベルアップしたときにLevelUpの文字を出す******/
CLevelUpFont::CLevelUpFont(VECTOR &pPos) : CEffect(64, pPos)
{
	pos = VGet(pPos.x - 80, pPos.y - 64, 0);
}

void CLevelUpFont::Render(BitmapText *text)
{
	text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "level up!");

}

/*******レベルアップしたときにPlayerを中心に拡大する円を作る*******/
#define CIRCLR_EF_LIVE 64

CLevelUpCircle::CLevelUpCircle(VECTOR & pPos) :CEffect(CIRCLR_EF_LIVE, pPos)
{
}

void CLevelUpCircle::Render(BitmapText *text)
{
	DrawCircle((int)pos.x, (int)pos.y, animCnt * 3, GetColor(255, 255, 255), FALSE);
}

/*********レベルアップしたときにスキルポイント画像を描写*********/
#define IMG_EF_LIVE 64

CImg::CImg(VECTOR & pPos, int * pGraphic) :CEffect(IMG_EF_LIVE, pPos)
{
	graphic = pGraphic;
	pos.y += 16;
}

void CImg::Render(BitmapText *text)
{
	text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "+");
	DrawRotaGraph((int)pos.x + 64, (int)pos.y--, 1.5, 0, *graphic, TRUE);
}

CBossReady::CBossReady(VECTOR & pPos, int * pDangerGraphic, int* pYellowGraphic) : CEffect(150, pPos)
{
	dangerGraphic = pDangerGraphic;
	yellowGraphic = pYellowGraphic;
	a = 0;
	plusFlag = true;
}

void CBossReady::Render(BitmapText * text)
{
	if (plusFlag == false)
	{
		a -= 5;
	}
	else
	{
		a += 5;
	}
	if (a > 180)
	{
		plusFlag = false;
	}
	if (a < 0)
	{
		plusFlag = true;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawGraph(0, 0, *yellowGraphic, TRUE);
	DrawRotaGraph((int)SCREEN_WIDTH_HALF, (int)SCREEN_HEIGHT_HALF, 1.0, 0, *dangerGraphic, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
