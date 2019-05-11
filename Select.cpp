#include"Manager.h"
#include"Select.h"
#include"Game.h"
#include"Sound.h"
#include"BitMapFont.h"
#include"Define.h"

CSelect::CSelect(CManager * pManager) :CScene(pManager)
{
	manager = pManager;
	backGroundGraphic = new int;
	*backGroundGraphic = LoadGraph("img/UI/Title.png");

	playerGraphic = new int;
	*playerGraphic = LoadGraph("img/Space Shooter - 1/Ship/Player.png");

	yazirusi = new int;
	*yazirusi = LoadGraph("img/UI/Yazirusi1.png");

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

	fontGraphic = new int;
	*fontGraphic = LoadGraph("img/UI/SelectFont.png");
}

CSelect::~CSelect()
{
	delete backGroundGraphic;
	delete playerGraphic;
	delete[] yaGraphic;
	delete fontGraphic;
}

void CSelect::Update(CSound *sound)
{
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
		CasolMove(sound);
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
	}

	bool case3 = true;

	for (int num = 0; num < 7; num++)
	{
		if (moveCase[num] != 3)
		{
			case3 = false;
		}
	}

	if (case3 == true)
	{
		manager->scene = new CGame(manager, casol);
		delete this;
	}
}

void CSelect::Render(BitmapText *text)
{
	DrawGraph(0, 0, *backGroundGraphic, TRUE);

	for (int num = 0; num < 7; num++)
	{
		DrawRotaGraph((int)yaPos[num].x, (int)yaPos[num].y, 1.0, 5.5, yaGraphic[num], TRUE);
	}

	playerCnt++;
	if (playerCnt < 30)
	{
		DrawRotaGraph(550 + (casol * 480), SCREEN_HEIGHT_HALF - 160 + 48, 1.0, 3.14, *playerGraphic, TRUE);
		DrawRotaGraph(450 + (casol * 480), SCREEN_HEIGHT_HALF - 160, 1.0, 3.14, *yazirusi, TRUE);
	}
	else if (playerCnt < 60)
	{
		DrawRotaGraph(560 + (casol * 480), SCREEN_HEIGHT_HALF - 160 + 48, 1.0, 3.14, *playerGraphic, TRUE);
		DrawRotaGraph(450 + (casol * 480), SCREEN_HEIGHT_HALF - 160 - 10, 1.0, 3.14, *yazirusi, TRUE);
	}
	else
	{
		playerCnt = 0;
		DrawRotaGraph(550 + (casol * 480), SCREEN_HEIGHT_HALF - 160 + 48, 1.0, 3.14, *playerGraphic, TRUE);
		DrawRotaGraph(450 + (casol * 480), SCREEN_HEIGHT_HALF - 160, 1.0, 3.14, *yazirusi, TRUE);
	}
	DrawRotaGraph(SCREEN_WIDTH_HALF, SCREEN_HEIGHT_HALF, 1.0, 0, *fontGraphic, TRUE);
}

void CSelect::CasolMove(CSound *sound)
{
	if (manager->GetKey()[KEY_INPUT_LEFT] == 1 ||
		manager->GetKey()[KEY_INPUT_A] == 1 ||
		(manager->GetControl()[CONTROL_LEFT] == 1))
	{
		sound->PlaySounds(eCasolSound, DX_PLAYTYPE_BACK);
		casol--;
	}
	if (manager->GetKey()[KEY_INPUT_RIGHT] == 1 ||
		manager->GetKey()[KEY_INPUT_D] == 1 ||
		(manager->GetControl()[CONTROL_RIGHT] == 1))
	{
		sound->PlaySounds(eCasolSound, DX_PLAYTYPE_BACK);
		casol++;
	}

	if (casol < 0)
	{
		casol = 2;
	}
	if (casol > 2)
	{
		casol = 0;
	}
}
