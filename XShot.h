#pragma once

class CXBullet :public CBullet
{
public:
	CXBullet(int *tex, VECTOR &pPos, SBulletStatus &xStatu);
    //”í’e‚ÉÁ‚¦‚éˆ—
    void HitAction() {}
	void Update();
private:
	void Move();
	float speed;
};