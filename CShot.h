#pragma once

class CCBullet :public CBullet
{
public:
	CCBullet(int *tex, VECTOR &pPos, SBulletStatus &cStatu, int uoCheck);
    //被弾時に消える処理
    void HitAction() { flag = false; }
	void Update();
private:
	void Move();
	int underOnCheck;
};
