#pragma once

class CManager;
class CSound;
class BitmapText;
#include"DxLib.h"

class CTitle :public CScene
{
	CManager *manager;
public:
	CTitle(CManager *pManager);
	~CTitle();

	void Update(CSound *sound);
	void Render(BitmapText *text);
private:
	int demoPlayTime;
	int *graphic;
	int *fontGraphic;
	int *yaGraphic;
	VECTOR yaPos[7];
	float vYaPos[7];
	int moveCase[7];
	float firstBackPosition;
	float secondBackPosition;
	int *controlerGraphic;
	float controlerSize;
	bool controlerSizeFlag;
};