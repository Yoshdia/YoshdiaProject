#pragma once

#include"DxLib.h"

class CBackGround
{
public:
	//CBackGround(VECTOR pPos);
	virtual void Update() = 0;
	virtual void Render() = 0;
	bool GetFlag() { return flag; }
protected:
	VECTOR pos;
	//ê∂ë∂ÉtÉâÉOÅ@true=ê∂ë∂
	bool flag;
};

//ìÆÇ´ë±ÇØÇÈîwåi
class CMoveBackGround :public CBackGround
{
public:
	CMoveBackGround(VECTOR pPos,int &pGraphic,bool spinFlag);
	void Update();
	void Render();
private:
	float drawSize;
	float drawRad;
	float drawRadAdd;
	int graphic;
};

//ìÆÇ©Ç»Ç¢îwåi
class CNoMoveBackGround :public CBackGround
{
public:
	CNoMoveBackGround(int pGraphic,VECTOR pPos);
	void Update();
	void Render();
private:
	int graphic;
};