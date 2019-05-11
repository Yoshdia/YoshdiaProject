#pragma once

enum direction
{
	inside,
	out,
	up,
	right,
	down,
	left
};

#include"DxLib.h"

//CBullet,CPlayerEnemyCommonへ継承
class CObject
{
protected:
	//座標
	VECTOR pos;
	//画像のアドレス
	int *graphic;
	//画像の幅
	float range;
	//受け取った座標が上下左右いずれかにScreenOut以上出ていたらtrueを返す
	bool ComeOutScreen(VECTOR &pPos, double ScreenOut);
	//受け取ったベクトルを正規化しspeed倍する
	void normPos(VECTOR *pos, VECTOR vPos, float speedX, float speedY);
	//被弾時に建つ無敵フラグ Bulletでは使用しない
	bool damegedInvincibleFlag;
public:
	//そのObjectが無敵かどうか返す Bulletでは意味なし
	bool GetInvincible() { return damegedInvincibleFlag; }
	//描画
	//virtual void Render() = 0;
	//座標を返す
	VECTOR GetPos() { return pos; }
	//画像の幅を返す
	float GetRange() { return range; }
	//被弾時の処理
	virtual void HitAction() = 0;
};

class CPlayerEnemyCommon :public CObject
{
protected:
	//被弾時の処理 damegedInvincibleが建っているときに呼ばれる
	void DamegeProcess(float distance);
	//ノックバック距離、この値が上で受け取ったdistanceを上回ると被弾処理終了
	float damageDistance;
	//HP
	int hp;
public:
	//被弾処理
	void HitAction();
	//damageの値をHpから引く
	void HitDamage(int damege);
};