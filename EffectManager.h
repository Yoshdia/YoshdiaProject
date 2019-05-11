#pragma once

class CEffect;

#include"Effect.h"
#define EFFECT_NUM 100

enum eEffect
{
	eBomb,
	eAir,
	ePlusScore,
	eLevelUpFont,
	eCircle,
	eStatusLevelUp,
	eBossReady,
};

class CEffectManager
{
	CEffect *effect[EFFECT_NUM];
public:
	CEffectManager();
	~CEffectManager();
	//enemyManager,bulletManagerから呼ばれる。efNumに応じたエフェクトを作成する
	//アニメーションを行うエフェクト。CEffectManagerで画像をロード
	void EffectSpawn(VECTOR pPos, int efNum, double size, double rad, int diray);
	//文字を描画する。文字はCEffectで指定
	void FontSpawn(VECTOR pPos, int efNum, int scoreNum);
	//関数を使用した図形を描画する。
	void ShapeSpawn(VECTOR pPos, int efNum);
	//受け取った画像を表示する。
	void ImageSpawn(VECTOR pPos, int *graphic);
	//更新
	void Update();
	//描写
	void Render(BitmapText *text);
private:
	//爆発エフェクト
	int bombGraphic[EF_BOMB_GRAPHIC];
	int airGraphic[EF_AIR_GRAPHIC];
	int statusLevelUoGraphic[EF_STATUS_LEVEL_GRAPHIC];

	int *dangerGraphic;
	int *yellowGraphic;
};