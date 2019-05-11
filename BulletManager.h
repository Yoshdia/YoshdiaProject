#pragma once

//BULLETNUM�̒���0����B_Z��ZShot�AB_Z����B_X��XShot�̂悤�ɂ���
#define B_Z 40
#define B_C 20
#define B_V 1
#define BULLET_NUM B_Z+B_C+B_V

//Shot�̎��ʎq
enum Shot
{
	zShot = B_Z,
	cShot = B_Z  + B_C,
	vShot = B_Z  + B_C + B_V
};

#include"Bullet.h"

class CBulletManager
{
	CBullet *bullet[BULLET_NUM];
public:
	CBulletManager();
	~CBulletManager();
	//bullet[num]�̌����W��Ԃ�
	VECTOR GetBulletPos(int num);
	//player�ɌĂ΂��B�������ۂɔ��˂�����֐�
	void Shot(int *tex, VECTOR &pos, SBulletStatus &status, int minNum, int maxNum);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�e��CObject�^�ɃL���X�g���ĕԂ�
	CBullet *GetBullet(int num) { return (CBullet*)bullet[num]; }
private:
	//bullet��minNum����maxNum�̊Ԃ�Null�̂��̂��������炻�̒l��Ԃ�
	int NullCheck(int mixNum, int maxNum);
};