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
	//生存フラグ　true=生存
	bool flag;
};

//動き続ける背景
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

//動かない背景
class CNoMoveBackGround :public CBackGround
{
public:
	CNoMoveBackGround(int pGraphic,VECTOR pPos);
	void Update();
	void Render();
private:
	int graphic;
};