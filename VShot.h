#pragma once

class CVBullet :public CBullet
{
public:
	CVBullet(int *tex, VECTOR &pPos, SBulletStatus &vStatu);
    //��e���ɏ����鏈��
    void HitAction() { }
	void Update();
private:
	void Move() {};
};