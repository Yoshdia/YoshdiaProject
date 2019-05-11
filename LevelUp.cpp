#include"DxLib.h"
#include"Manager.h"
#include"LevelUp.h"
#include"Player.h"
#include"Define.h"
#include"Sound.h"
#include"BitMapFont.h"
#include"EffectManager.h"

CLevelUp::CLevelUp(int pLevel)
{
	casol = 0;
	attackLevel = pLevel;
	casolAdd = 8;
}
#define LEVEL_BOTTON_X SCREEN_WIDTH_HALF/2
#define LEVEL_BOTTON_Y SCREEN_HEIGHT_HALF
#define LEVEL_BOTTON_GRAP 128

bool CLevelUp::Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound)
{
	CasolMove(pManager, sound);

	//Enterキーを押すとplayer内のLevelUpを呼び出しステータスの変化を起こす
	if (pManager->GetKey()[KEY_INPUT_RETURN] == 1 ||
		//Bボタン
		(pManager->GetControl()[CONTROL_B] ==1)||
		//Aボタン
		(pManager->GetControl()[CONTROL_A]==1))
	{
		if (pPlayer->LevelUp(casol, sound) == true)
		{
			sound->PlaySounds(eStatusLevelUpSound, DX_PLAYTYPE_BACK);
		}
	}
	if (pPlayer->LevelUpEnd() == true)
	{
		effectManager->EffectSpawn(pPlayer->GetPos(), eStatusLevelUp, 1.0, 0, 0);
		delete this;
		return true;
	}
	return false;
}


void CLevelUp::Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text)
{
	DrawGraph(0, 0, pBlackScreenImg, TRUE);
	//player内のHPZXCを描画する関数を呼び出す
	int bottonX = 0;
	bottonX = LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * 0);
	pPlayer->RenderBottonDraw(12, bottonX, LEVEL_BOTTON_Y);
	bottonX = LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * 1);
	pPlayer->RenderBottonDraw(13, bottonX, LEVEL_BOTTON_Y);
	bottonX = LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * 2);
	pPlayer->RenderFrontBotton(bottonX, LEVEL_BOTTON_Y);
	if (attackLevel >= P_CAN_SHOT_PLUS_LEVEL + 1)
	{
		bottonX = LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * 3);
		pPlayer->RenderBackBotton(bottonX, LEVEL_BOTTON_Y);
	}
	bottonX = LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * casol);
	//pPlayer->RenderBottonDraw(13, bottonX, LEVEL_BOTTON_Y);
	CasolRender();
	//pPlayer->RenderLevelUpImg();
	pPlayer->RenderLevelUpFont(casol);
	text->textDraw(SCREEN_WIDTH_HALF / 2+16, SCREEN_HEIGHT_HALF + 320-32, 2.0f, "press [b][a] to enter!");
	text->textDraw(SCREEN_WIDTH_HALF/2+32, SCREEN_HEIGHT_HALF+320, 2.0f, "press [y] to back");
	pPlayer->RenderSkill(400, 400);
}

void CLevelUp::CasolMove(CManager * pManager, CSound *sound)
{
	//左右キーを一回押すごとにそちらにカーソルが動く
	if (pManager->GetKey()[KEY_INPUT_LEFT] == 1 ||
		pManager->GetKey()[KEY_INPUT_A] == 1 ||
		(pManager->GetControl()[CONTROL_LEFT]==1))
	{
		sound->PlaySounds(eCasolSound, DX_PLAYTYPE_BACK);
		casol--;
		casolAdd = 0;
	}
	if (pManager->GetKey()[KEY_INPUT_RIGHT] == 1 ||
		pManager->GetKey()[KEY_INPUT_D] == 1 ||
		(pManager->GetControl()[CONTROL_RIGHT] == 1))
	{
		sound->PlaySounds(eCasolSound, DX_PLAYTYPE_BACK);
		casol++;
		casolAdd = 0;
	}

	int casolRightRimit = eC;
	if (attackLevel < P_CAN_SHOT_PLUS_LEVEL + 1)
	{
		casolRightRimit = eZ;
	}

	//Hpより左に行こうとするとCへ行く
	if (casol < eAttack)
	{
		casol = casolRightRimit;
	}
	//Cより右に行こうとするとHpへ行く
	if (casol > casolRightRimit)
	{
		casol = eAttack;
	}
}

void CLevelUp::CasolRender()
{
	casolAdd++;
	if (casolAdd <= 32)
	{
		DrawBoxAA((float)((LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * casol)) - 32 - casolAdd),
			(float)(LEVEL_BOTTON_Y - 32 - casolAdd - 1),
			(float)((LEVEL_BOTTON_X + (LEVEL_BOTTON_GRAP * casol)) + 32 + casolAdd),
			(float)(LEVEL_BOTTON_Y + 32 + casolAdd - 1),
			GetColor(255, 255, 255), FALSE);
	}
	else if (casolAdd > 48)
	{
		casolAdd = 0;
	}
}
