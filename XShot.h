#pragma once

class CXBullet :public CBullet
{
public:
	CXBullet(int *tex, VECTOR &pPos, SBulletStatus &xStatu);
    //��e���ɏ����鏈��
    void HitAction() {}
	void Update();
private:
	void Move();
	float speed;
};