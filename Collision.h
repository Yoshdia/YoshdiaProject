#pragma once

class CObject;

class CCollision
{
public:
	//CObject�^�Ƃ��Ď󂯎������̃I�u�W�F�N�g�̓����蔻����s��������������HitAction���Ă�True��Ԃ�oneObjectNoHitAction�́Atrue�̂Ƃ���ڂ�HitAction���Ă΂Ȃ�
	bool CheckCollision(CObject *o1, CObject *o2, bool oneObjectNoHitAction);
};