#pragma once

class CBackGround;
#define BACK_NUM 100
#define BG_NUM 12

class CBackGroundSpawn
{
	CBackGround *backGround[BACK_NUM];
public:
	CBackGroundSpawn();
	~CBackGroundSpawn();

	void Update();
	//�Q�[���J�n���ɂ������̐��𐶐����Ă����K�v�����邽��public��new���邾���̊֐��������Ă���
	void MoveBackGround(float starX,int graphicNum);
	void NoMoveBackGroundSpawn();
	void Render(int &pGraphic);
	void changeStageGraphic(int stanum);
private:
	void Spawn();
	//0~10���傫��覐΁A11~19��������覐΁A20,21�����i
	int *backGroundGraphic;
	int *noMoveBackGroundGraphic;
};