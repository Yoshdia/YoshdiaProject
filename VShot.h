#pragma once

class CVBullet :public CBullet
{
public:
	CVBullet(int *tex, VECTOR &pPos, SBulletStatus &vStatu);
    //被弾時に消える処理
    void HitAction() { }
	void Update();
private:
	void Move() {};
};