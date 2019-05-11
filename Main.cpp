#include "DxLib.h"
#include "Manager.h"
#include "Game.h"
#include "Title.h"
#include "Define.h"
#include"Sound.h"
#include"BitMapFont.h"

#define KEY_NUM 256
#define CONTROL_NUM 8

//http://haina.hatenablog.com/entry/2016/09/25/004108

#pragma warning(disable:4129)
//画面の更新処理　エラーでゲーム終了
bool ScreenUpdate();
//キーボード、コントローラーからのキー取得
bool UpdateKey(char *key, char *control);
int GetKeyBoard(char *key);
int GetControler(char *control);

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//ウインドウモードに変更
	ChangeWindowMode(TRUE);

	//DXライブラリを初期化する。
	if (DxLib_Init() == -1) return -1;

	//キー取得
	char key[KEY_NUM];
	char control[CONTROL_NUM];

	//描画先画面を裏にする
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetDrawScreen(DX_SCREEN_BACK);

	BitmapText *text;
	text = new BitmapText;

	text->setFontImage(15, 8, "img/Space Shooter - 1/Font20x20.png");
	text->reMapText(" !_#$%&_()*+,-./0123456789:_<=>?@abcdefghijklmnopqrstuvwxyz[\_]^_");

	CSound *sound;
	sound = new CSound();

	//管理システムを動的確保
	CManager *manager;
	manager = new CManager(key, control);
	//シーンを動的確保
	//manager->scene = new CGame(manager,0);
	manager->scene = new CTitle(manager);

	SetMouseDispFlag(FALSE);

	while (ScreenUpdate()&& UpdateKey(key, control))
	{
		//シーンごとの処理
		manager->Render(text);
		manager->Update(sound);
	}
	//後始末
	delete text;
	delete sound;
	delete manager;
	//DXライブラリを終了する。
	DxLib_End();

	return 0;
}


//画面の更新
bool ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//画面の裏ページの内容を表ページに反映する
	if (ScreenFlip() != 0) return false;
	//画面を初期化
	if (ClearDrawScreen() != 0) return false;
	return true;
}

//キーの入力状態を更新する
bool UpdateKey(char *key, char *control)
{
	//キー取得
	if (GetKeyBoard(key) != 0) return false;
	//コントローラー取得
	if (GetControler(control) != 0)return false;
	//エスケープで終了
	if (key[KEY_INPUT_ESCAPE] >= 1) return false;
	return true;
}

int GetKeyBoard(char *key)
{
	//現在のキーの入力状態を格納する
	char tmpKey[KEY_NUM];
	//全てのキーの入力状態を得る
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < KEY_NUM; i++) {
		if (tmpKey[i] != 0)
		{//i番のキーコードに対応するキーが押されていたら加算
			if (key[i] == 120)
			{
				key[i] = 0;
			}
			key[i]++;
		}
		else
		{//押されていなければ0にする
			key[i] = 0;
		}
	}
	return 0;
}

int GetControler(char * control)
{
	char tmpkey[CONTROL_NUM];

	tmpkey[0] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_LEFT;
	tmpkey[1] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_RIGHT;
	tmpkey[2] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_UP;
	tmpkey[3] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_DOWN;
	tmpkey[4] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_1;
	tmpkey[5] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_2;
	tmpkey[6] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_3;
	tmpkey[7] = GetJoypadInputState(DX_INPUT_PAD1)&PAD_INPUT_4;

	for (int num = 0; num < CONTROL_NUM; num++)
	{
		if (tmpkey[num] != 0)
		{
			if (control[num] == 120)
			{
				control[num] = 0;
			}
			control[num]++;
		}
		else
		{
			control[num] = 0;
		}
	}
	return 0;
}
