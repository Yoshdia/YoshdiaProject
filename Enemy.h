#pragma once

#include"Object.h"
//#define E_SPEED 3

class CEnemy :public CPlayerEnemyCommon
{
protected:
	VECTOR vPos;
	bool flag;
	void ComeOut();
	//hp�̌��ݒl�͌p����ɂĐ錾
	//�e�̔��ˊԊu
	int interval;
	//���ˊԊu�J�E���g
	int intervalCnt;
	//���ˏ���
	bool shotReadyflag;
	//���ˏ�������
	void ShotReady();
	//���˂��鋅�̎��
	int shotCheck;
	//���̃G�l�~�[�����̃X�e�[�W�̃{�X���ǂ����B�󂯎����bullet�̒l�Ŕ��f����
	bool bossFlag;
	//�`�ʂ����ۂ̃T�C�Y�B�`�b�v�T�C�Y��range���������l
	float size;
	//�`�ʂ����ۂ̊p�x�B��{�I�Ƀ{�X����]����
	float drawRad;

	float addSpeedX;
	float addSpeedY;
	//�G�l�~�[�ɂ���ĈႤ�A�ړ��ɂ���ĕς��G�l�~�[�̌�����ύX������֐�
	virtual void DrawRadMath()=0;
	//�i�s��������������֐�
	void MoveRadMath();

	void CheckRange();

public:
	CEnemy(VECTOR &pPos, VECTOR &pvPos, float rangeSize, int bullet,int pGraphic);
	~CEnemy() { delete graphic; };
	void Update();
	virtual void Move() = 0;
	bool GetFlag() { return flag; };
	void Render();
	bool GetShotReady() { return shotReadyflag; }
	void SetShotReady() { shotReadyflag = false; }
	int GetShotCheck() { return shotCheck; };
	int GetHp() { return hp; }
	bool GetBossFlag() { return bossFlag; };
	virtual void BossShot() {};
	int hpMax;
	int gaugeGraphic;

	void RenderBossHp();
};
