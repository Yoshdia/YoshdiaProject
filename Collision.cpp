#include"Collision.h"
#include"Object.h"

bool CCollision::CheckCollision(CObject *o1, CObject *o2, bool oneObjectNoHitAction)
{
	VECTOR obj1Pos = o1->GetPos();
	VECTOR obj2Pos = o2->GetPos();
	float obj1Range = o1->GetRange() / 2;
	float obj2Range = o2->GetRange() / 2;

	float distance = VSquareSize(VSub(obj1Pos, obj2Pos));
	float range = (obj1Range + obj2Range)*(obj1Range + obj2Range);

	//float distance =
	//	(obj1Pos.x - obj2Pos.x)*(obj1Pos.x - obj2Pos.x)
	//	+ (obj1Pos.y - obj2Pos.y)*(obj1Pos.y - obj2Pos.y);

	//float range = (obj1Range + obj2Range)*(obj1Range + obj2Range);

	bool invincible = true;
	if (o1->GetInvincible() == false && o2->GetInvincible() == false)
	{
		invincible = false;
	}

	if (distance < range&&invincible == false)
	{
		if (oneObjectNoHitAction == false)
		{
			o1->HitAction();
		}
		o2->HitAction();
		return true;
	}
	return false;
}

