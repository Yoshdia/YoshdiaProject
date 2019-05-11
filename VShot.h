#pragma once

class CVBullet :public CBullet
{
public:
	CVBullet(int *tex, VECTOR &pPos, SBulletStatus &vStatu);
    //”í’e‚ÉÁ‚¦‚éˆ—
    void HitAction() { }
	void Update();
private:
	void Move() {};
};