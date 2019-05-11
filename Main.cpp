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
//��ʂ̍X�V�����@�G���[�ŃQ�[���I��
bool ScreenUpdate();
//�L�[�{�[�h�A�R���g���[���[����̃L�[�擾
bool UpdateKey(char *key, char *control);
int GetKeyBoard(char *key);
int GetControler(char *control);

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�C���h�E���[�h�ɕύX
	ChangeWindowMode(TRUE);

	//DX���C�u����������������B
	if (DxLib_Init() == -1) return -1;

	//�L�[�擾
	char key[KEY_NUM];
	char control[CONTROL_NUM];

	//�`����ʂ𗠂ɂ���
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	SetDrawScreen(DX_SCREEN_BACK);

	BitmapText *text;
	text = new BitmapText;

	text->setFontImage(15, 8, "img/Space Shooter - 1/Font20x20.png");
	text->reMapText(" !_#$%&_()*+,-./0123456789:_<=>?@abcdefghijklmnopqrstuvwxyz[\_]^_");

	CSound *sound;
	sound = new CSound();

	//�Ǘ��V�X�e���𓮓I�m��
	CManager *manager;
	manager = new CManager(key, control);
	//�V�[���𓮓I�m��
	//manager->scene = new CGame(manager,0);
	manager->scene = new CTitle(manager);

	SetMouseDispFlag(FALSE);

	while (ScreenUpdate()&& UpdateKey(key, control))
	{
		//�V�[�����Ƃ̏���
		manager->Render(text);
		manager->Update(sound);
	}
	//��n��
	delete text;
	delete sound;
	delete manager;
	//DX���C�u�������I������B
	DxLib_End();

	return 0;
}


//��ʂ̍X�V
bool ScreenUpdate()
{
	if (ProcessMessage() != 0) return false;
	//��ʂ̗��y�[�W�̓��e��\�y�[�W�ɔ��f����
	if (ScreenFlip() != 0) return false;
	//��ʂ�������
	if (ClearDrawScreen() != 0) return false;
	return true;
}

//�L�[�̓��͏�Ԃ��X�V����
bool UpdateKey(char *key, char *control)
{
	//�L�[�擾
	if (GetKeyBoard(key) != 0) return false;
	//�R���g���[���[�擾
	if (GetControler(control) != 0)return false;
	//�G�X�P�[�v�ŏI��
	if (key[KEY_INPUT_ESCAPE] >= 1) return false;
	return true;
}

int GetKeyBoard(char *key)
{
	//���݂̃L�[�̓��͏�Ԃ��i�[����
	char tmpKey[KEY_NUM];
	//�S�ẴL�[�̓��͏�Ԃ𓾂�
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < KEY_NUM; i++) {
		if (tmpKey[i] != 0)
		{//i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�������Z
			if (key[i] == 120)
			{
				key[i] = 0;
			}
			key[i]++;
		}
		else
		{//������Ă��Ȃ����0�ɂ���
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
