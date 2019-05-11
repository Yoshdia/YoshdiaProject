#include"BackGroundSpawn.h"
#include"BackGround.h"
#include"Define.h"

CBackGroundSpawn::CBackGroundSpawn()
{
	for (int num = 0; num < BACK_NUM; num++)
	{
		backGround[num] = NULL;
	}
	backGroundGraphic = new int[BG_NUM];
	int num = 0;
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Meteor1.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Meteor2.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Meteor3.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Meteor4.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Meteor5.png");

	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Star.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Star2.png");

	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Moon.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Planet1.png");
	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Planet2.png");

	backGroundGraphic[num++] = LoadGraph("img/Space Shooter - 1/BackGround/Black hole.png");


	noMoveBackGroundGraphic = new int[3];
	noMoveBackGroundGraphic[0] = LoadGraph("img/Space Shooter - 1/BackGround/3b.png");
	noMoveBackGroundGraphic[1] = LoadGraph("img/Space Shooter - 1/BackGround/4.png");
	noMoveBackGroundGraphic[2] = LoadGraph("img/Space Shooter - 1/BackGround/4b.png");
}

CBackGroundSpawn::~CBackGroundSpawn()
{
	for (int num = 0; num < BACK_NUM; num++)
	{
		delete backGround[num];
	}
	delete[] backGroundGraphic;
	delete[] noMoveBackGroundGraphic;
}

void CBackGroundSpawn::Update()
{
	Spawn();
	for (int num = 0; num < BACK_NUM; num++)
	{
		if (backGround[num] != NULL)
		{
			backGround[num]->Update();
			if (backGround[num]->GetFlag() == false)
			{
				delete backGround[num];
				backGround[num] = NULL;
			}
		}
	}
}

#define BG_METEOR_RAND 1000
#define BG_PLANET_RAND 20000
#define BG_STAR_RAND 5000
#define BG_BLACKHOLE_RAND 30000

void CBackGroundSpawn::Spawn()
{
	//大きな隕石、小さな隕石、壊れた部品それぞれ湧く確率が違う
	//そのRandの値が1のときにそのFlagを建てグラフィック番号をその画像の番号にする
	int drawGraphic = 0;

	int meteorRand = GetRand(BG_METEOR_RAND);
	bool meteorRandFlag = false;

	if (meteorRand == 1)
	{
		meteorRandFlag = true;
		drawGraphic = GetRand(4);
	}

	int planetRand = GetRand(BG_PLANET_RAND);
	bool planetRandFlag = false;

	if (planetRand == 1)
	{
		planetRandFlag = true;
		drawGraphic = GetRand(3)+5;
	}
	int starRand = GetRand(BG_STAR_RAND);
	bool starRandFlag = false;

	if (starRand == 1)
	{
		starRandFlag = true;
		drawGraphic = GetRand(2) + 8;
	}

	int blackholeRand = GetRand(BG_BLACKHOLE_RAND);
	bool blackholeRandFlag = false;

	if (blackholeRand == 1)
	{
		blackholeRandFlag = true;
		drawGraphic = BG_NUM-1;
	}

	//建っているFlagに応じた画像をnewさせる
	if (meteorRandFlag == true || planetRandFlag == true || blackholeRandFlag == true || starRandFlag==true)
	{
		float bgStarX = (float)SCREEN_WIDTH + 100;
		MoveBackGround(bgStarX,drawGraphic);
	}
}

void CBackGroundSpawn::MoveBackGround(float starX, int graphicNum)
{
	for (int num = 0; num < BACK_NUM; num++)
	{
		if (backGround[num] == NULL)
		{
			VECTOR backPos = VGet(starX, (float)GetRand(SCREEN_HEIGHT) /*- BG_HEIGHT_MAX*/, 0);
			bool spinFlag = false;
			//drawGraphicが22。星の画像の場合は回転させないためにこのフラグを建てる
			if (graphicNum >5)
			{
				spinFlag = true;
			}
			backGround[num] = new CMoveBackGround(backPos, backGroundGraphic[graphicNum], spinFlag);
			break;
		}
	}
}

void CBackGroundSpawn::Render(int &pGraphic)
{
	for (int num = 0; num < BACK_NUM; num++)
	{
		if (backGround[num] != NULL)
		{
			backGround[num]->Render();
		}
	}
	DrawGraph(0, 0, pGraphic, TRUE);
}

void CBackGroundSpawn::changeStageGraphic(int stanum)
{
	for (int num = 0; num < BACK_NUM; num++)
	{
		if (backGround[num] == NULL)
		{
			VECTOR backPos = VGet(0, 0, 0);
			backGround[num] = new CNoMoveBackGround(noMoveBackGroundGraphic[stanum], backPos);
			break;
		}
	}
}

void CBackGroundSpawn::NoMoveBackGroundSpawn()
{
	for (int num = 0; num < BACK_NUM; num++)
	{
		if (backGround[num] == NULL)
		{
			VECTOR backPos = VGet(0, 0, 0);
			backGround[num] = new CNoMoveBackGround(noMoveBackGroundGraphic[0],backPos);
			break;
		}
	}
}
