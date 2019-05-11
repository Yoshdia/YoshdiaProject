#pragma once

class CManager;
class CPlayer;
class CSound;
class BitmapText;
class CEffectManager;

#include"DxLib.h"


class CPause
{
public:
	virtual bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound) = 0;
	virtual void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text) = 0;
};

class CChargePause :public CPause
{
public:
	CChargePause(int *pGraphic, VECTOR plaPos, int *plaGraphic, float plaSize);
	bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound);
	void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text);
private:
	VECTOR playerPos;
	int playerGraphic;
	float playerSize;

	int graphic[6];
	int animCnt;
	float animSize;
	float animRad;
};

class CTutorial :public CPause
{
public:
	CTutorial();
	~CTutorial();
	bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound);
	virtual void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text);
private:
	VECTOR pos;
	int *tutorialGraphic;
	bool moveFlag;
	int moveCase;

	int yaGraphic[7];
	VECTOR yaPos;
};

class CWait :public CPause
{
public:
	CWait();
	~CWait();
	bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound);
	virtual void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text);
private:
	int waitTime;
};

class CPress0 :public CPause
{
public:
	CPress0();

	bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound);
	virtual void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text);
};

class CChangeStagePause :public CPause
{
public:
	CChangeStagePause();
	bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound);
	virtual void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text);
	private:
	int changeTime;

};