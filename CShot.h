#pragma once

class CCBullet :public CBullet
{
public:
	CCBullet(int *tex, VECTOR &pPos, SBulletStatus &cStatu, int uoCheck);
    //”í’e‚ÉÁ‚¦‚éˆ—
    void HitAction() { flag = false; }
	void Update();
private:
	void Move();
	int underOnCheck;
};
