#pragma once

#include"Object.h"

class CItem :public CObject
{
public:
	CItem(int tex, VECTOR pPos,int pItemNum);
	~CItem();
	void Update();
	void Render();
	bool GetFlag() { return flag; }
	void HitAction() { flag = false; }
	bool GetItemNum() {return itemNum;	}
private:
	//生存カウント
	int liveCnt;
	//点滅の表示されていないカウント
	float changeCnt;
	//生存フラグ　true=生存
	bool flag;
	//描画フラグ　falseのときは描画する
	bool draw;
	//アイテムの識別子
	int itemNum;

	float drawRad;
	//回転量、ランダムでとる
	float drawRadAdd;
	//アイテムのグラフィック
	int *itemGraphic;
};