#pragma once

#define E_BULLET_NUM 100

#include"EnemyBullet.h"
#include"Define.h"

class CEnemyManager;


class CEnemyBulletManager
{
	CBullet *bullet[E_BULLET_NUM];
public:
	CEnemyBulletManager();
	~CEnemyBulletManager();
	void Update(CEnemyManager *enemyManager,VECTOR playerPos);
	void Render();
	//�e��CObject�^�ɃL���X�g���ĕԂ�
	CBullet *GetBullet(int num) { return (CBullet*)bullet[num]; }
private:
	//bullet��minNum����maxNum�̊Ԃ�Null�̂��̂��������炻�̒l��Ԃ�
	int NullCheck(int mixNum, int maxNum);
	void Shot(CEnemyManager *enemyManager, VECTOR playerPos);
	int bulletGraphic[E_GRAPHIC];
};