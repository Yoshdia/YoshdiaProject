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
//画面外に出る限界
#define P_SCREEN_OUT 100

#define P_DEF_X	32
#define P_DEF_Y SCREEN_HEIGHT_HALF

#define P_SPEED 10

#define P_CAN_SHOT_PLUS_LEVEL 2

//弾のグラフィック枚数
#define Z_GRAPHIC 30
#define C_GRAPHIC 30	
#define V_GRAPHIC 1

#define G_GRAPHIC 5
//敵の球グラフィック枚数
#define E_GRAPHIC 30
//#define C_GRAPHIC 24

#define NOCKBACK 64

#define E_CHIPSIZE 91

enum enemyBullet
{
	//弾を撃たない敵
	enemyShotNo,
	//追尾弾
	enemyShotTracking,
	enemyShotStraight,
	enemyShotRandam,
	eFirstBoss,
	eSecondBoss,
	eThirdBoss,
};
//スタート地点。Titleで決定したものをGameで受け取る
//どこからスタートするか。Playerはこの値で初期化の値が変わりWaveも途中からの再生になる
enum eWhereStart
{
	eFirst,
	eSecond,
	eThird
};