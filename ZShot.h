#pragma once

//struct SBulletStatus;


class CZBullet :public CBullet
{
public:
	CZBullet(int *tex,VECTOR &pPos,SBulletStatus &zStatu,int uoCheck);
    //”í’e‚ÉÁ‚¦‚éˆ—
    void HitAction() { flag = false; }
	void Update();
private:
	VECTOR firstPos;
	void Move();
	int underOnCheck;
};