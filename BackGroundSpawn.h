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
	//ゲーム開始時にいくつかの星を生成しておく必要があるためpublicにnewするだけの関数をおいておく
	void MoveBackGround(float starX,int graphicNum);
	void NoMoveBackGroundSpawn();
	void Render(int &pGraphic);
	void changeStageGraphic(int stanum);
private:
	void Spawn();
	//0~10が大きな隕石、11~19が小さな隕石、20,21が部品
	int *backGroundGraphic;
	int *noMoveBackGroundGraphic;
};