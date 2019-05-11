#pragma once

#define EF_BOMB_GRAPHIC 7
#define EF_AIR_GRAPHIC 8
#define EF_STATUS_LEVEL_GRAPHIC 10

class BitmapText;

//エフェクトの基底クラス
class CEffect
{
protected:
	//座標
	VECTOR pos;
	//グラフィック
	int graphic[16];
	//描写時に使用する番号
	int animCnt;
	//グラフィック枚数
	int graphicNumber;
	//描写角度
	double animRad;
	//描写サイズ
	double animSize;
	//エフェクトの生存フラグ　true=生存
	bool flag;
	//待機時間。連続でエフェクトを呼ぶときに使用
	int dirayTime;
	//待機時間がすべて済んだかどうか
	bool dirayOk;
	//DirayのCnt
	int dirayCnt;
public:
	CEffect(int liveCnt, VECTOR pPos);
	CEffect(int graphicNum, double size, double rad, VECTOR pPos, int diray);
	//~CEffect() { delete[] graphic; };
	//animCntを足し続けgraphicNumber以上になったらフラグを倒す
	void Update();
	//描写
	virtual void Render(BitmapText *text) = 0;
	//生存フラグを返す
	bool GetFlag() { return flag; };
};

//爆破エフェクト
class CBomb :public CEffect
{
public:
	CBomb(VECTOR &pPos, int *tex, double &size, double &rad, int diray);
	void Render(BitmapText *text);
};

class CAirBomb :public CEffect
{
public:
	CAirBomb(VECTOR &pPos, int *tex, double &size, double &rad, int diray);
	void Render(BitmapText *text);
};

class CStatusLevelUp :public CEffect
{
public:
	CStatusLevelUp(VECTOR &pPos, int *tex, double &size, double &rad, int diray);
	void Render(BitmapText *text);
};

//スコア増加エフェクト
class CPlusScoreFont :public CEffect
{
public:
	CPlusScoreFont(VECTOR &pPos, int plusScore);
private:
	int score;
	void Render(BitmapText *text);
};

//レベルアップ時の円
class CLevelUpCircle :public CEffect
{
public:
	CLevelUpCircle(VECTOR &pPos);
	void Render(BitmapText *text);
};

//レベルアップ時の文字
class CLevelUpFont :public CEffect
{
public:
	CLevelUpFont(VECTOR &pPos);
	void Render(BitmapText *text);
};

class CImg :public CEffect
{
public:
	CImg(VECTOR &pPos,int *pGraphic);
	void Render(BitmapText *text);
private:
	int *graphic;
};

class CBossReady :public CEffect
{
public:
	CBossReady(VECTOR &pPos,int *pDangerGraphic,int *pYellowGraphic);
	void Render(BitmapText *text);
private:
	int *dangerGraphic;
	int *yellowGraphic;
	int a;
	bool plusFlag;
};