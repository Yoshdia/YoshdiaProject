#include"Manager.h"
#include"Title.h"
#include"Select.h"
#include"Sound.h"
#include"BitMapFont.h"
#include"Define.h"
#include"DemoPlay.h"
#define STOPDEMOTIME 300


CTitle::CTitle(CManager * pManager) :CScene(pManager)
{
	secondBackPosition = 1920.0f;
	firstBackPosition = 0;
	manager = pManager;
	graphic = new int;
	*graphic = LoadGraph("img/UI/Title.png", TRUE);
	fontGraphic = new int;
	*fontGraphic = LoadGraph("img/UI/TitleFont.png", TRUE);

	int allGraphic[3];
	LoadDivGraph("img/UI/yazirusi.png", 3, 1, 3, 2000, 192, allGraphic, TRUE);

	yaGraphic = new int[7];

	yaGraphic[0] = allGraphic[0];
	yaPos[0] = VGet(0 - 700, 425 + 700, 0);
	vYaPos[0] = 7;
	moveCase[0];

	yaGraphic[1] = allGraphic[2];
	yaPos[1] = VGet(0 - 600, 820 + 600, 0);
	vYaPos[1] = 15;
	moveCase[1] = 0;

	yaGraphic[2] = allGraphic[1];
	yaPos[2] = VGet(0 - 500, 1150 + 500, 0);
	vYaPos[2] = 20;
	moveCase[2] = 0;

	yaGraphic[3] = allGraphic[0];
	yaPos[3] = VGet(850 - 600, SCREEN_HEIGHT + 600, 0);
	vYaPos[3] = 20;
	moveCase[3] = 0;

	yaGraphic[4] = allGraphic[2];
	yaPos[4] = VGet(-SCREEN_HEIGHT + 450, SCREEN_HEIGHT * 2, 0);
	vYaPos[4] = 37;
	moveCase[4] = 0;

	yaGraphic[5] = allGraphic[1];
	yaPos[5] = VGet(1250 - 600, SCREEN_HEIGHT + 600, 0);
	vYaPos[5] = 20;
	moveCase[5] = 0;

	yaGraphic[6] = allGraphic[2];
	yaPos[6] = VGet(1600 - 800, SCREEN_HEIGHT + 800, 0);
	vYaPos[6] = 7;
	moveCase[6] = 0;

	demoPlayTime = 0;

	controlerGraphic = new int[4];
	LoadDivGraph("img/UI/Controler.png", 4, 1, 4, 128, 128, controlerGraphic, TRUE);
	controlerSize = 1;
	controlerSizeFlag = false;
}

CTitle::~CTitle()
{
	delete graphic;
	delete[] yaGraphic;
	delete controlerGraphic;
	demoPlayTime = 0;
}

void CTitle::Update(CSound *sound)
{
	//すべてのBGMを止める
	if (sound->PlayCheck(eStageClearBGM) == true)
	{
		sound->StopSound(eStageClearBGM);
	}
	if (sound->PlayCheck(eStageOverBGM) == true)
	{
		sound->StopSound(eStageOverBGM);
	}

	for (int num = 0; num < 7; num++)
	{
		yaPos[num].x += vYaPos[num];
		yaPos[num].y -= vYaPos[num];
	}

	//1番目の矢印
	switch (moveCase[0])
	{
	case(0):
		vYaPos[0] -= 0.1f;
		if (vYaPos[0] < -2.0)
		{
			moveCase[0] = 1;
			vYaPos[0] = 0;
		}
		break;
	case(1):
		break;
	case(2):
		vYaPos[0]++;
		if (vYaPos[0] > 30)
		{
			vYaPos[0] = 0;
			moveCase[0] = 3;
		}
		break;
	}

	//2番目の矢印
	switch (moveCase[1])
	{
	case(0):
		vYaPos[1] -= 0.3f;
		if (vYaPos[1] < -4.5)
		{
			vYaPos[1] = 0;
			moveCase[1] = 1;
		}
		break;
	case(2):
		vYaPos[1]++;
		if (vYaPos[1] > 30)
		{
			vYaPos[1] = 0;
			moveCase[1] = 3;
		}
		break;
	}

	//3番目の矢印
	switch (moveCase[2])
	{
	case(0):
		vYaPos[2] -= 0.5f;
		if (vYaPos[2] < -9.5)
		{
			vYaPos[2] = 0;
			moveCase[2] = 1;
		}
		break;
	case(2):
		vYaPos[2]++;
		if (vYaPos[2] > 40)
		{
			vYaPos[2] = 0;
			moveCase[2] = 3;
		}
		break;
	}

	//4番目の矢印
	switch (moveCase[3])
	{
	case(0):
		vYaPos[3] -= 0.5f;
		if (vYaPos[3] < -9.5)
		{
			vYaPos[3] = 0;
			moveCase[3] = 1;
		}
		break;
	case(2):
		vYaPos[3]++;
		if (vYaPos[3] > 40)
		{
			vYaPos[3] = 0;
			moveCase[3] = 3;
		}
		break;
	}

	//5番目の矢印
	switch (moveCase[4])
	{
	case(0):
		vYaPos[4] -= 0.5f;
		if (vYaPos[4] < -6)
		{
			vYaPos[4] = 0;
			moveCase[4] = 1;
		}
		break;
	case(2):
		vYaPos[4]++;
		if (vYaPos[4] > 28)
		{
			moveCase[4] = 3;
			vYaPos[4] = 0;
		}
		break;

	}

	//6番目の矢印
	switch (moveCase[5])
	{
	case(0):
		vYaPos[5] -= 0.5f;
		if (vYaPos[5] < -9.5)
		{
			vYaPos[5] = 0;
			moveCase[5] = 1;
		}
		break;
	case(2):
		vYaPos[5]++;
		if (vYaPos[5] > 40)
		{
			vYaPos[5] = 0;
			moveCase[5] = 3;
		}
		break;
	}

	//7番目の矢印
	switch (moveCase[6])
	{
	case(0):
		vYaPos[6] -= 0.1f;
		if (vYaPos[6] < -2.0)
		{
			moveCase[6] = 1;
			vYaPos[6] = 0;
		}
		break;
	case(1):
		break;
	case(2):
		vYaPos[6]++;
		if (vYaPos[6] > 30)
		{
			vYaPos[6] = 0;
			moveCase[6] = 3;
		}
		break;
	}

	bool case1 = true;
	for (int num = 0; num < 7; num++)
	{
		if (moveCase[num] != 1)
		{
			case1 = false;
		}
	}

	if (case1 == true)
	{
		if (manager->GetKey()[KEY_INPUT_RETURN] == 1 ||
			//Bボタン
			(manager->GetControl()[CONTROL_B] == 1) ||
			//Aボタン
			(manager->GetControl()[CONTROL_A] == 1))
		{
			for (int num = 0; num < 7; num++)
			{
				moveCase[num] = 2;
			}
		}
		demoPlayTime++;

	}

	bool case3 = true;

	for (int num = 0; num < 7; num++)
	{
		if (moveCase[num] != 3)
		{
			case3 = false;
		}
	}

	if (case3 == true || demoPlayTime > STOPDEMOTIME)
	{
		if (case3 == true)
		{
			manager->scene = new CSelect(manager);
		}
		if (demoPlayTime > STOPDEMOTIME)
		{
			manager->scene = new CDemoPlay(manager);
		}
		delete this;
	}
	firstBackPosition -= 1.0f;
	if (firstBackPosition <= -1920)
	{
		firstBackPosition = 1920;
	}
	secondBackPosition -= 1.0f;
	if (secondBackPosition <= -1920)
	{
		secondBackPosition = 1920;
	}

	if (controlerSize < 1.1)
	{
		controlerSizeFlag = true;
	}
	if (controlerSize > 1.3)
	{
		controlerSizeFlag = false;
	}

	if (controlerSizeFlag == true)
	{
		controlerSize += 0.005f;
	}
	else
	{
		controlerSize -= 0.005f;
	}
}

void CTitle::Render(BitmapText *text)
{
	//5.5
	DrawGraph((int)firstBackPosition, 0, *graphic, TRUE);
	DrawGraph((int)secondBackPosition, 0, *graphic, TRUE);

	for (int num = 0; num < 7; num++)
	{
		DrawRotaGraph((int)yaPos[num].x, (int)yaPos[num].y, 1.0, 5.5, yaGraphic[num], TRUE);
	}
	DrawRotaGraph(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 1.0, 0, *fontGraphic, TRUE);
	DrawRotaGraph(SCREEN_WIDTH_HALF - 346, 832, controlerSize, 0, controlerGraphic[1], TRUE);
	DrawRotaGraph(SCREEN_WIDTH_HALF + 306, 832, controlerSize, 0, controlerGraphic[0], TRUE);



}
