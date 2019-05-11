#pragma once

class CManager;
class CSound;
class BitmapText;

#include"DxLib.h"

class CSelect :public CScene
{
	CManager *manager;
public:
	CSelect(CManager *pManager);
	~CSelect();

	void Update(CSound *sound);
	void Render(BitmapText *text);
private:
	int casol;
	char select[3][100];
	void CasolMove(CSound *sound);
	int *backGroundGraphic;
	int *fontGraphic;
	//プレイヤーが消えたり表示されたりするためのカウント
	int playerCnt;
	int *playerGraphic;
	int *yazirusi;

	int *yaGraphic;
	VECTOR yaPos[7];
	float vYaPos[7];
	int moveCase[7];
};