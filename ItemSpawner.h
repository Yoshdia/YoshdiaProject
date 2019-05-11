#pragma once

#define ITEM_NUM 10

#include"Item.h"

enum
{
	eShieldItem,
	eScore
};

class CItem;

class CItemSpawner
{
	CItem *item[ITEM_NUM];
public:
	CItemSpawner();
	~CItemSpawner();
//ItemをItem型にキャストして返す
	CItem *GetItem(int num) { return (CItem*)item[num]; }
	//enemyManagerから呼ばれる、Itemを湧かせる関数
	void Spawn(VECTOR pos);
	//更新
	void Update();
	//描画
	void Render();
	int *itemGraphic;
};