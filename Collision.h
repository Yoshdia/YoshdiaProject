#pragma once

class CObject;

class CCollision
{
public:
	//CObject型として受け取った二つのオブジェクトの当たり判定を行い当たった時にHitActionを呼びTrueを返すoneObjectNoHitActionは、trueのとき一つ目のHitActionを呼ばない
	bool CheckCollision(CObject *o1, CObject *o2, bool oneObjectNoHitAction);
};