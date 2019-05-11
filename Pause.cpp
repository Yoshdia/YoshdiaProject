#include "Pause.h"
#include"Player.h"
#include"Manager.h"
#include"Define.h"
#include"BitMapFont.h"
#include"EffectManager.h"

CChargePause::CChargePause(int *pGraphic, VECTOR plaPos, int *plaGraphic, float plaSize)
{
	playerPos = plaPos;
	memcpy(graphic, pGraphic, 6 * sizeof(pGraphic[0]));
	playerSize = plaSize;
	playerGraphic = *plaGraphic;
	animCnt = 0;
	animSize = 15;
	animRad = 0;
}

bool CChargePause::Update(CEffectManager *effectManager, CPlayer * pPlayer, CManager * pManager, CSound * sound)
{
	animCnt++;
	animSize -= 0.3f;
	animRad += 0.2f;
	if (animCnt >= 6 * 8)
	{
		pPlayer->ShotBirst();
		delete this;
		return true;
	}
	return false;
}

void CChargePause::Render(CPlayer * pPlayer, int pBlackScreenImg, BitmapText *text)
{
	DrawGraph(0, 0, pBlackScreenImg, TRUE);
	DrawRotaGraph((int)playerPos.x, (int)playerPos.y, animSize, animRad, graphic[animCnt / 8], TRUE);
	DrawRotaGraph((int)playerPos.x, (int)playerPos.y, playerSize, 1.57, playerGraphic, TRUE);
}

/*********************************************************************/

CTutorial::CTutorial()
{
	tutorialGraphic = new int;
	*tutorialGraphic = LoadGraph("img/UI/tutorial.png");
	moveFlag = false;
	moveCase = 0;
	pos = VGet(0, 0, 0);

	int allGraphic[3];
	LoadDivGraph("img/UI/yazirusi.png", 3, 1, 3, 2000, 192, allGraphic, TRUE);

	yaPos = VGet(0, SCREEN_HEIGHT + 1000, 0);

	yaGraphic[0] = allGraphic[0];
	yaGraphic[1] = allGraphic[1];
	yaGraphic[2] = allGraphic[2];
	yaGraphic[3] = allGraphic[1];
	yaGraphic[4] = allGraphic[2];
	yaGraphic[5] = allGraphic[0];
	yaGraphic[6] = allGraphic[1];
	yaGraphic[7] = allGraphic[0];
}

CTutorial::~CTutorial()
{
	delete tutorialGraphic;
}

bool CTutorial::Update(CEffectManager *effectManager, CPlayer * pPlayer, CManager * pManager, CSound * sound)
{
	if (pManager->GetKey()[KEY_INPUT_RETURN] == 1 ||
		//Bボタン
		(pManager->GetControl()[CONTROL_B] == 1) ||
		//Aボタン
		(pManager->GetControl()[CONTROL_A] == 1))
	{
		moveFlag = true;
	}

	if (moveFlag == true)
	{
		switch (moveCase)
		{
		case(0):
			pos.y += 10;
			if (pos.y > -100)
			{
				moveCase = 1;
			}
			break;
		case(1):
			yaPos.y -= 100;
			pos.y -= 100;
			if (yaPos.y < -1920)
			{
				delete this;
				return true;
			}
			break;
		}
	}
	return false;
}

void CTutorial::Render(CPlayer * pPlayer, int pBlackScreenImg, BitmapText *text)
{
	DrawGraph(0, 0, pBlackScreenImg, TRUE);
	DrawGraph((int)pos.x, (int)pos.y, *tutorialGraphic, TRUE);

	//for (int num = 1; num < 8; num++)
	//{
	//	DrawRotaGraph(250 * num, (int)yaPos.y, 1.0, -1.57, yaGraphic[num - 1], TRUE);
	//}

}

CWait::CWait()
{
	waitTime = 0;
}

CWait::~CWait()
{
}

bool CWait::Update(CEffectManager *effectManager, CPlayer * pPlayer, CManager * pManager, CSound * sound)
{
	waitTime++;

	if (waitTime > 180)
	{
		delete this;
		return true;
	}

	return false;
}

void CWait::Render(CPlayer * pPlayer, int pBlackScreenImg, BitmapText * text)
{
	//DrawGraph(0, 0, pBlackScreenImg, TRUE);
}

CPress0::CPress0()
{
}

bool CPress0::Update(CEffectManager * effectManager, CPlayer * pPlayer, CManager * pManager, CSound * sound)
{
	if (pManager->GetKey()[KEY_INPUT_RETURN] == 1)
	{
		delete this;
		return true;
	}
	return false;
}

void CPress0::Render(CPlayer * pPlayer, int pBlackScreenImg, BitmapText * text)
{
}

CChangeStagePause::CChangeStagePause()
{
	changeTime = 0;
}

bool CChangeStagePause::Update(CEffectManager * effectManager, CPlayer * pPlayer, CManager * pManager, CSound * sound)
{

	changeTime++;
	if (changeTime > 180)
	{
		pPlayer->PlusHp();
		VECTOR returnPos = VGet(P_DEF_X, P_DEF_Y, 0);
		pPlayer->SetPos(returnPos);
		pPlayer->SetInvincible();
		return true;
	}
	return false;
}

void CChangeStagePause::Render(CPlayer * pPlayer, int pBlackScreenImg, BitmapText * text)
{
}