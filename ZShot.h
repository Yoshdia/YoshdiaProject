#pragma once

//struct SBulletStatus;


class CZBullet :public CBullet
{
public:
	CZBullet(int *tex,VECTOR &pPos,SBulletStatus &zStatu,int uoCheck);
    //被弾時に消える処理
    void HitAction() { flag = false; }
	void Update();
private:
	VECTOR firstPos;
	void Move();
	int underOnCheck;
};