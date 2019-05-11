#pragma once

class CXBullet :public CBullet
{
public:
	CXBullet(int *tex, VECTOR &pPos, SBulletStatus &xStatu);
    //被弾時に消える処理
    void HitAction() {}
	void Update();
private:
	void Move();
	float speed;
};