#pragma once

//BULLETNUMの中で0からB_ZをZShot、B_ZからB_XをXShotのようにする
#define B_Z 40
#define B_C 20
#define B_V 1
#define BULLET_NUM B_Z+B_C+B_V

//Shotの識別子
enum Shot
{
	zShot = B_Z,
	cShot = B_Z  + B_C,
	vShot = B_Z  + B_C + B_V
};

#include"Bullet.h"
#include<List>

class CBulletManager
{
	std::list<CBullet*> bulletList;
public:
	CBulletManager();
	~CBulletManager();
	//bullet[num]の現座標を返す
	VECTOR GetBulletPos(int num);
	//playerに呼ばれる。球を実際に発射させる関数
	void Shot(int *tex, VECTOR &pos, SBulletStatus &status, int minNum, int maxNum);
	//更新
	void Update();
	//描写
	void Render();
	//弾をCObject型にキャストして返す
	CBullet *GetBullet(int num);

	const int GetListSize() { return (int)bulletList.size(); };
private:
};