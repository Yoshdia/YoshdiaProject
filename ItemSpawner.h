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
//Item��Item�^�ɃL���X�g���ĕԂ�
	CItem *GetItem(int num) { return (CItem*)item[num]; }
	//enemyManager����Ă΂��AItem��N������֐�
	void Spawn(VECTOR pos);
	//�X�V
	void Update();
	//�`��
	void Render();
	int *itemGraphic;
};