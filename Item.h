#pragma once

#include"Object.h"

class CItem :public CObject
{
public:
	CItem(int tex, VECTOR pPos,int pItemNum);
	~CItem();
	void Update();
	void Render();
	bool GetFlag() { return flag; }
	void HitAction() { flag = false; }
	bool GetItemNum() {return itemNum;	}
private:
	//�����J�E���g
	int liveCnt;
	//�_�ł̕\������Ă��Ȃ��J�E���g
	float changeCnt;
	//�����t���O�@true=����
	bool flag;
	//�`��t���O�@false�̂Ƃ��͕`�悷��
	bool draw;
	//�A�C�e���̎��ʎq
	int itemNum;

	float drawRad;
	//��]�ʁA�����_���łƂ�
	float drawRadAdd;
	//�A�C�e���̃O���t�B�b�N
	int *itemGraphic;
};