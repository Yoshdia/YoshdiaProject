#pragma once

#include"Pause.h"
class CSound;
class CEffectManager;

enum EBotton
{
	eAttack,
	eDiffend,
	eZ,
	eC
};

class CLevelUp:public CPause
{
public:
	CLevelUp(int pLevel);
	bool Update(CEffectManager *effectManager, CPlayer *pPlayer, CManager *pManager, CSound *sound);
	void Render(CPlayer *pPlayer, int pBlackScreenImg, BitmapText *text);
private:
	//ÉJÅ[É\Éã
	int casol;
	int casolAdd;
	int attackLevel;
	void CasolMove(CManager *pManager, CSound *sound);
	void CasolRender();
};