#include"DxLib.h"
//#include"Define.h"
#include"BulletManager.h"
#include"ZShot.h"
#include"XShot.h"
#include"CShot.h"
#include"VShot.h"



CBulletManager::CBulletManager()
{
	//�e�S�Ă̏�����
	//for (int num = 0; num < BULLET_NUM; num++)
	//{
	//	bullet[num] = NULL;
	//}
}

CBulletManager::~CBulletManager()
{
	bulletList.clear();
	//�e�S�Ă̍폜
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
	//	//NULL�łȂ��ꍇ
	//	if (bullet[num] != NULL)
	//	{
	//		bullet[num]->Update();
	//		//�e����ʊO�ɏo���ꍇ
	//		if (bullet[num]->GetFlag() == false)
	//		{
	//			//�폜���Ă���NULL������
	//			delete bullet[num];
	//			bullet[num] = NULL;
	//		}
	//	}
	//}
}

void CBulletManager::Shot(int *tex, VECTOR &pos, SBulletStatus &status, int minNum, int maxNum)
{

	//player����󂯎�������̃X�e�[�^�X���R�s�[����
	SBulletStatus sStatus = status;
	//Null�������l��num��
	int num = NullCheck(minNum, maxNum);
	int underOnCheck = 0;
	//maxNum��zShot�������Ƃ���zShot
	if (maxNum == zShot)
	{
		//zStatus��aStatus�ɂ���Ĕ��˂���鋅�̐����ς��
		//�����֔���
		underOnCheck = eStraightShot;
		bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
		//bullet[num] = new CZBullet(tex, pos, sStatus, underOnCheck);
		//aStatus��1�ȏ�Ȃ��ɂ�����
		if ((&status)->aStatus >= eOnShot)
		{
			underOnCheck = eOnShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CZBullet(tex, pos, sStatus, underOnCheck);
		}
		//aStatus��2�ȏ�Ȃ牺�ɂ�����
		if ((&status)->aStatus >= eUnderShot)
		{
			underOnCheck = eUnderShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CZBullet(tex, pos, sStatus, underOnCheck);
		}
	}
	//maxNum��cShot�������Ƃ���cShot
	else if (maxNum == cShot)
	{
		//zStatus��aStatus�ɂ���Ĕ��˂���鋅�̐����ς��
		//�����֔���
		underOnCheck = eStraightShot;
		bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
		//bullet[num] = new CCBullet(tex, pos, sStatus, underOnCheck);
		//aStatus��1�ȏ�Ȃ��ɂ�����
		if ((&status)->aStatus >= eOnShot)
		{
			underOnCheck = eOnShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CCBullet(tex, pos, sStatus, underOnCheck);
		}
		//aStatus��2�ȏ�Ȃ牺�ɂ�����
		if ((&status)->aStatus >= eUnderShot)
		{
			underOnCheck = eUnderShot;
			num = NullCheck(minNum, maxNum);
			bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
			//bullet[num] = new CCBullet(tex, pos, sStatus, underOnCheck);
		}
	}
	//maxNum��vShot�������Ƃ���vShot
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
	//�S�Ă�bullet���X�V���̏ꍇNULL��Ԃ�
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
