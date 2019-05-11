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
	//enemyManager,bulletManager����Ă΂��BefNum�ɉ������G�t�F�N�g���쐬����
	//�A�j���[�V�������s���G�t�F�N�g�BCEffectManager�ŉ摜�����[�h
	void EffectSpawn(VECTOR pPos, int efNum, double size, double rad, int diray);
	//������`�悷��B������CEffect�Ŏw��
	void FontSpawn(VECTOR pPos, int efNum, int scoreNum);
	//�֐����g�p�����}�`��`�悷��B
	void ShapeSpawn(VECTOR pPos, int efNum);
	//�󂯎�����摜��\������B
	void ImageSpawn(VECTOR pPos, int *graphic);
	//�X�V
	void Update();
	//�`��
	void Render(BitmapText *text);
private:
	//�����G�t�F�N�g
	int bombGraphic[EF_BOMB_GRAPHIC];
	int airGraphic[EF_AIR_GRAPHIC];
	int statusLevelUoGraphic[EF_STATUS_LEVEL_GRAPHIC];

	int *dangerGraphic;
	int *yellowGraphic;
};