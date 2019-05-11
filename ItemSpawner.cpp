#include "ItemSpawner.h"

CItemSpawner::CItemSpawner()
{
	for (int num = 0; num < ITEM_NUM; num++)
	{
		item[num] = NULL;
	}
	itemGraphic = new int[2];
	itemGraphic[0]=LoadGraph("img/Space Shooter - 1/Item/shieldItem.png", TRUE);
	itemGraphic[1] = LoadGraph("img/Space Shooter - 1/Item/PowerUp1.png", TRUE);
}

CItemSpawner::~CItemSpawner()
{
	for (int num = 0; num < ITEM_NUM; num++)
	{
		delete item[num];
	}
	delete[] itemGraphic;
}

void CItemSpawner::Update()
{
	for (int num = 0; num < ITEM_NUM; num++)
	{
		if (item[num] != NULL)
		{
			item[num]->Update();
			if (item[num]->GetFlag() == false)
			{
				delete item[num];
				item[num] = NULL;
			}
		}
	}
}

void CItemSpawner::Spawn(VECTOR pos)
{
	for (int num = 0; num < ITEM_NUM; num++)
	{
		if (item[num] == NULL)
		{
			int itemNum = GetRand(1);
			item[num] = new CItem(itemGraphic[itemNum], pos,itemNum);
			break;
		}
	}
}

void CItemSpawner::Render()
{
	for (int num = 0; num < ITEM_NUM; num++)
	{
		if (item[num] != NULL)
		{
			item[num]->Render();
		}
	}
}
