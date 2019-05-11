#pragma once

struct SBulletStatus
{
	float speed;
	float size;
	int aStatus;
	int level;
};


enum eOnUnderCheck
{
	eStraightShot,
	eOnShot,
	eUnderShot,
};

#include"Object.h"

class CBullet :public CObject
{
protected:
	//�`�ʊp�x
	int drawRad;
	//�����t���O�Btrue������
	bool flag;
	//Player����󂯎�����e�̃X�e�[�^�X���R�s�[
	SBulletStatus status;
	int bGraphic[30];
public:
	CBullet();
	CBullet(SBulletStatus &Status);
	int GetaStatus() { return status.aStatus; };
	//���݂̐����t���O��Ԃ�
	bool GetFlag() { return flag; };
	//�X�e�[�^�X
	virtual void Update() = 0;
	//�ړ����[�`��
	virtual void Move() = 0;
	//�`��
	void Render();
	//�`�ʊp�x�𑝂₵������
	void DrawRadPlus();
};