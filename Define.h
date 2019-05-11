#pragma once

#define CONTROL_LEFT 0
#define CONTROL_RIGHT 1
#define CONTROL_UP 2
#define CONTROL_DOWN 3
#define CONTROL_B 4
#define CONTROL_A 5
#define CONTROL_X 6
#define CONTROL_Y 7

//#define SCREEN_HEIGHT 980
#define SCREEN_HEIGHT 1080
#define SCREEN_HEIGHT_HALF (SCREEN_HEIGHT/2)
//#define SCREEN_WIDTH  1820
#define SCREEN_WIDTH  1920
#define SCREEN_WIDTH_HALF  (SCREEN_WIDTH/2)
//��ʊO�ɏo����E
#define P_SCREEN_OUT 100

#define P_DEF_X	32
#define P_DEF_Y SCREEN_HEIGHT_HALF

#define P_SPEED 10

#define P_CAN_SHOT_PLUS_LEVEL 2

//�e�̃O���t�B�b�N����
#define Z_GRAPHIC 30
#define C_GRAPHIC 30	
#define V_GRAPHIC 1

#define G_GRAPHIC 5
//�G�̋��O���t�B�b�N����
#define E_GRAPHIC 30
//#define C_GRAPHIC 24

#define NOCKBACK 64

#define E_CHIPSIZE 91

enum enemyBullet
{
	//�e�������Ȃ��G
	enemyShotNo,
	//�ǔ��e
	enemyShotTracking,
	enemyShotStraight,
	enemyShotRandam,
	eFirstBoss,
	eSecondBoss,
	eThirdBoss,
};
//�X�^�[�g�n�_�BTitle�Ō��肵�����̂�Game�Ŏ󂯎��
//�ǂ�����X�^�[�g���邩�BPlayer�͂��̒l�ŏ������̒l���ς��Wave���r������̍Đ��ɂȂ�
enum eWhereStart
{
	eFirst,
	eSecond,
	eThird
};