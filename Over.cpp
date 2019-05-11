#include"Manager.h"
#include"Title.h"
#include"Over.h"
#include"DxLib.h"
#include"Sound.h"
#include"BitMapFont.h"
#include"Define.h"

COver::COver(CManager * pManager) :CScene(pManager)
{
	manager = pManager;
	graphic = new int;
	*graphic = LoadGraph("img/UI/Over.png", TRUE);
}

COver::~COver()
{
	delete graphic;
}

void COver::Update(CSound *sound)
{
	if (sound->PlayCheck(eStageOverBGM) == false)
	{
		sound->PlaySounds(eStageOverBGM, DX_PLAYTYPE_LOOP);
	}
	if (manager->GetKey()[KEY_INPUT_RETURN] == 1 ||
		//Bボタン
		(manager->GetControl()[CONTROL_B] == 1) ||
		//Aボタン
		(manager->GetControl()[CONTROL_A] == 1))
	{
		sound->StopSound(eStageOverBGM);
		manager->scene = new CTitle(manager);
		delete this;
	}
}

void COver::Render(BitmapText *text)
{
	DrawGraph(0, -200, *graphic, TRUE);
}
