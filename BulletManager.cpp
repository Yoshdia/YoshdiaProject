#include"DxLib.h"
//#include"Define.h"
#include"BulletManager.h"
#include"ZShot.h"
#include"XShot.h"
#include"CShot.h"
#include"VShot.h"

CBulletManager::CBulletManager()
{
}

CBulletManager::~CBulletManager()
{
	bulletList.clear();
}

void CBulletManager::Update()
{
	for (std::list<CBullet*>::const_iterator itr = bulletList.begin(); itr != bulletList.end();)
	{
		(*itr)->Update();
		if ((*itr)->GetFlag() == false)
		{
			itr = bulletList.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void CBulletManager::Shot(int *tex, VECTOR &pos, SBulletStatus &status, int minNum, int maxNum)
{

	//player����󂯎�������̃X�e�[�^�X���R�s�[����
	SBulletStatus sStatus = status;
	//Null�������l��num��
	int underOnCheck = 0;
	//maxNum��zShot�������Ƃ���zShot
	if (maxNum == zShot)
	{
		//zStatus��aStatus�ɂ���Ĕ��˂���鋅�̐����ς��
		//�����֔���
		underOnCheck = eStraightShot;
		bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
		//aStatus��1�ȏ�Ȃ��ɂ�����
		if ((&status)->aStatus >= eOnShot)
		{
			underOnCheck = eOnShot;
			bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
		}
		//aStatus��2�ȏ�Ȃ牺�ɂ�����
		if ((&status)->aStatus >= eUnderShot)
		{
			underOnCheck = eUnderShot;
			bulletList.emplace_back(new CZBullet(tex, pos, sStatus, underOnCheck));
		}
	}
	//maxNum��cShot�������Ƃ���cShot
	else if (maxNum == cShot)
	{
		//zStatus��aStatus�ɂ���Ĕ��˂���鋅�̐����ς��
		//�����֔���
		underOnCheck = eStraightShot;
		bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
		//aStatus��1�ȏ�Ȃ��ɂ�����
		if ((&status)->aStatus >= eOnShot)
		{
			underOnCheck = eOnShot;
			bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
		}
		//aStatus��2�ȏ�Ȃ牺�ɂ�����
		if ((&status)->aStatus >= eUnderShot)
		{
			underOnCheck = eUnderShot;
			bulletList.emplace_back(new CCBullet(tex, pos, sStatus, underOnCheck));
		}
	}
	//maxNum��vShot�������Ƃ���vShot
	else if (maxNum == vShot)
	{
		bulletList.emplace_back(new CVBullet(tex, pos, sStatus));
	}
}

VECTOR CBulletManager::GetBulletPos(int num)
{
	int cnt=0;
	VECTOR bulletPos = VGet(0, 0, 0);
	for (std::list<CBullet*>::const_iterator itr = bulletList.begin(); itr != bulletList.end(); ++itr)
	{
		cnt++;
		if (num == cnt)
		{
			bulletPos=(*itr)->GetPos();
		}
	}

	return bulletPos;
}

void CBulletManager::Render()
{
	for (auto itr : bulletList)
	{
		itr->Render();
	}
}

CBullet * CBulletManager::GetBullet(int num)
{
	int cnt = 0;

	for (auto itr : bulletList)
	{
		cnt++;
		if (num == cnt)
		{
			return itr;
		}
	}
	return nullptr;
}
