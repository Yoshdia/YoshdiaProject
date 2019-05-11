#include"Manager.h"
#include"Title.h"
#include"Clear.h"
#include"DxLib.h"
#include"Sound.h"
#include"BitMapFont.h"
#include"Define.h"

CClear::CClear(CManager * pManager) :CScene(pManager)
{
	manager = pManager;
	graphic = new int;
	*graphic = LoadGraph("img/UI/Clear.png", TRUE);
}

CClear::~CClear()
{
	delete graphic;
}

void CClear::Update(CSound *sound)
{
	if (sound->PlayCheck(eStageClearBGM) == false)
	{
		sound->PlaySounds(eStageClearBGM,DX_PLAYTYPE_LOOP);
	}
	if (manager->GetKey()[KEY_INPUT_RETURN] == 1||
	//Bボタン
		(manager->GetControl()[CONTROL_B]==1)||
		//Aボタン
		(manager->GetControl()[CONTROL_A]==1))
	{
		if (sound->PlayCheck(eStageClearBGM) == true)
		{
			sound->StopSound(eStageClearBGM);
		}
		manager->scene = new CTitle(manager);
		delete this;
	}
}

void CClear::Render(BitmapText *text)
{
	DrawGraph(0, -200, *graphic, TRUE);
}
