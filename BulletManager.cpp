#include"DxLib.h"
//#include"Define.h"
#include"BulletManager.h"
#include"ZShot.h"
#include"XShot.h"
#include"CShot.h"
#include"VShot.h"



CBulletManager::CBulletManager()
{
	//弾全ての初期化
	//for (int num = 0; num < BULLET_NUM; num++)
	//{
	//	bullet[num] = NULL;
	//}
}

CBulletManager::~CBulletManager()
{
	bulletList.clear();
	//弾全ての削除
	//for (int num = 0; num < BULLET_NUM; num++)
	//{
	//	delete bullet[num];
	//}
}

void CBulletManager::Update()
{
	for (auto itr : bulletList)
	{
		if (bulletList.empty() == false)
		{
			itr->Update();
		}
		//bulletList.remove_if(itr.GetFlag == false);
	}

	//for (int num = 0; num < BULLET_NUM; num++)
	//{
	//	//NULLでない場合
	//	if (bullet[num] != NULL)
	//	{
	//		bullet[num]->Update();
	//		//弾が画面外に出た場合
	//		if (bullet[num]->GetFlag() == false)
	//		{
	//			//削除してからNULLを入れる
	//			delete bullet[num];
	//			bullet[num] = NULL;
	//		}
	//	}
	//}
}

void CBulletManager::Shot(int *tex, VECTOR &pos, SBulletStatus &status, int minNum, int maxNum)
{

	//playerから受け取った球のステータスをコピーする
	SBulletStatus sStatus = status;
	//Nullだった値をnumへ
	int num = NullCheck(minNum, maxNum);
	int underOnCheck = 0;
	//maxNumがzShotだったときはzShot
	if (maxNum == zShot)
	{
		//zStatusのaStatusによって発射される球の数が変わる
		//直線へ発射
		underOnCheck = eStraightShot;
		bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
		//bullet[num] = new CZBullet(tex, pos, sStatus, underOnCheck);
		//aStatusが1以上なら上にも発射
		if ((&status)->aStatus >= eOnShot)
		{
			underOnCheck = eOnShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CZBullet(tex, pos, sStatus, underOnCheck);
		}
		//aStatusが2以上なら下にも発射
		if ((&status)->aStatus >= eUnderShot)
		{
			underOnCheck = eUnderShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CZBullet(tex, pos, sStatus, underOnCheck);
		}
	}
	//maxNumがcShotだったときはcShot
	else if (maxNum == cShot)
	{
		//zStatusのaStatusによって発射される球の数が変わる
		//直線へ発射
		underOnCheck = eStraightShot;
		bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
		//bullet[num] = new CCBullet(tex, pos, sStatus, underOnCheck);
		//aStatusが1以上なら上にも発射
		if ((&status)->aStatus >= eOnShot)
		{
			underOnCheck = eOnShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CCBullet(tex, pos, sStatus, underOnCheck);
		}
		//aStatusが2以上なら下にも発射
		if ((&status)->aStatus >= eUnderShot)
		{
			underOnCheck = eUnderShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CCBullet(tex, pos, sStatus, underOnCheck);
		}
	}
	//maxNumがvShotだったときはvShot
	else if (maxNum == vShot)
	{
		bulletList.emplace_back(new CVBullet(tex, pos, sStatus));
		//bullet[num] = new CVBullet(tex, pos, sStatus);
	}
}

int CBulletManager::NullCheck(int mixNum, int maxNum)
{
	//for (int num = mixNum; num < maxNum; num++)
	//{
	//	if (bullet[num] == NULL)
	//	{
	//		return num;
	//	}
	//}
	//全てのbulletが更新中の場合NULLを返す
	return NULL;
}

VECTOR CBulletManager::GetBulletPos(int num)
{
	//return bulletList[num];
	//return bullet[num]->GetPos();
	return VGet(0, 0, 0);
}

void CBulletManager::Render()
{
	//for (int num = 0; num < BULLET_NUM; num++)
	//{
	//	if (bullet[num] != NULL)
	//	{
	//		bullet[num]->Render();
	//	}
	//}
	for (auto itr : bulletList)
	{
		itr->Render();
	}
}
