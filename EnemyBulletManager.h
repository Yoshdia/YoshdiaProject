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
	//弾をCObject型にキャストして返す
	CBullet *GetBullet(int num) { return (CBullet*)bullet[num]; }
private:
	//bulletにminNumからmaxNumの間にNullのものがあったらその値を返す
	int NullCheck(int mixNum, int maxNum);
	void Shot(CEnemyManager *enemyManager, VECTOR playerPos);
	int bulletGraphic[E_GRAPHIC];
};