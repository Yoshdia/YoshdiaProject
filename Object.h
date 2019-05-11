#pragma once

enum direction
{
	inside,
	out,
	up,
	right,
	down,
	left
};

#include"DxLib.h"

//CBullet,CPlayerEnemyCommon�֌p��
class CObject
{
protected:
	//���W
	VECTOR pos;
	//�摜�̃A�h���X
	int *graphic;
	//�摜�̕�
	float range;
	//�󂯎�������W���㉺���E�����ꂩ��ScreenOut�ȏ�o�Ă�����true��Ԃ�
	bool ComeOutScreen(VECTOR &pPos, double ScreenOut);
	//�󂯎�����x�N�g���𐳋K����speed�{����
	void normPos(VECTOR *pos, VECTOR vPos, float speedX, float speedY);
	//��e���Ɍ����G�t���O Bullet�ł͎g�p���Ȃ�
	bool damegedInvincibleFlag;
public:
	//����Object�����G���ǂ����Ԃ� Bullet�ł͈Ӗ��Ȃ�
	bool GetInvincible() { return damegedInvincibleFlag; }
	//�`��
	//virtual void Render() = 0;
	//���W��Ԃ�
	VECTOR GetPos() { return pos; }
	//�摜�̕���Ԃ�
	float GetRange() { return range; }
	//��e���̏���
	virtual void HitAction() = 0;
};

class CPlayerEnemyCommon :public CObject
{
protected:
	//��e���̏��� damegedInvincible�������Ă���Ƃ��ɌĂ΂��
	void DamegeProcess(float distance);
	//�m�b�N�o�b�N�����A���̒l����Ŏ󂯎����distance������Ɣ�e�����I��
	float damageDistance;
	//HP
	int hp;
public:
	//��e����
	void HitAction();
	//damage�̒l��Hp�������
	void HitDamage(int damege);
};