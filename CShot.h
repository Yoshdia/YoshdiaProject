#pragma once

class CCBullet :public CBullet
{
public:
	CCBullet(int *tex, VECTOR &pPos, SBulletStatus &cStatu, int uoCheck);
    //��e���ɏ����鏈��
    void HitAction() { flag = false; }
	void Update();
private:
	void Move();
	int underOnCheck;
};
