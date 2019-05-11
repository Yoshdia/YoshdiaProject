#pragma once

class CManager;
class CSound;
class BitmapText;
#include"DxLib.h"

class CDemoPlay :public CScene
{
	CManager *manager;
public:
	CDemoPlay(CManager *pManager);
	~CDemoPlay();

	void Update(CSound *sound);
	void Render(BitmapText *text);
private:
	int demoPlayMovie;
};