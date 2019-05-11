#include "DxLib.h"
#include "Effect.h"
#include "Define.h"
#include<string.h>
#include"BitMapFont.h"

CEffect::CEffect(int liveCnt, VECTOR pPos)
{
	graphicNumber = liveCnt;
	flag = true;
	animCnt = -1;
	animSize = 0;
	animRad = 0;
	pos = pPos;
	dirayCnt = 0;
	dirayTime = 0;
	dirayOk = true;
}

CEffect::CEffect(int graphicNum, double size, double rad, VECTOR pPos, int diray)
{
	//�O���t�B�b�N�������R�s�[
	graphicNumber = graphicNum;
	flag = true;
	//Render�������Update���Ă΂�邽��0�ŏ����������1���ڂ���X�^�[�g���Ă��܂��̂�-1�ŏ�����
	animCnt = -1;
	animSize = size;
	animRad = rad;
	pos = pPos;
	dirayCnt = 0;
	dirayTime = diray;
	dirayOk = false;
	//graphic = new int[graphicNumber];
}

void CEffect::Update()
{
	dirayCnt++;

	if (dirayCnt >= dirayTime)
	{
		dirayOk = true;
	}
	if (dirayOk == true)
	{
		//�A�j���[�V�����J�E���g
		animCnt++;

		//�A�j���[�V�������Đ����I������琶���t���O��|��
		if (animCnt == graphicNumber)
		{
			flag = false;
		}
	}
}


/******�G�����j���ꂽ�Ƃ��ɔ��j�G�t�F�N�g���o��******/

CBomb::CBomb(VECTOR &pPos, int *tex, double &size, double &rad, int diray) :CEffect(EF_BOMB_GRAPHIC, size, rad, pPos, diray)
{
	memcpy(graphic, tex, EF_BOMB_GRAPHIC * sizeof(tex[0]));
	graphicNumber *= 3;
}

void CBomb::Render(BitmapText *text)
{
	if (dirayOk == true)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, animSize, animRad, graphic[animCnt / 3], TRUE);
	}
}

/******�G�����j���ꂽ�Ƃ��ɋ�C�̔����G�t�F�N�g���o��******/

CAirBomb::CAirBomb(VECTOR &pPos, int *tex, double &size, double &rad, int diray) :CEffect(EF_BOMB_GRAPHIC, size, rad, pPos, diray)
{
	memcpy(graphic, tex, EF_AIR_GRAPHIC * sizeof(tex[0]));
	graphicNumber *= 5;
}

void CAirBomb::Render(BitmapText *text)
{
	if (dirayOk == true)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, animSize, animRad, graphic[animCnt / 5], TRUE);
	}
}

/******�X�e�[�^�X�̃��x���A�b�v���s��ꂽ�Ƃ��ɃG�t�F�N�g���o��******/

CStatusLevelUp::CStatusLevelUp(VECTOR &pPos, int *tex, double &size, double &rad, int diray) :CEffect(EF_STATUS_LEVEL_GRAPHIC, size, rad, pPos, diray)
{
	memcpy(graphic, tex, EF_STATUS_LEVEL_GRAPHIC * sizeof(tex[0]));
	graphicNumber *= 3;
}

void CStatusLevelUp::Render(BitmapText *text)
{
	if (dirayOk == true)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, animSize, animRad, graphic[EF_STATUS_LEVEL_GRAPHIC - (animCnt / 3)], TRUE);
	}
}

#define FONT_EF_LIVE 40
/******�G�����j�����Ƃ���+1000���̕������o��******/
CPlusScoreFont::CPlusScoreFont(VECTOR &pPos, int plusScore) : CEffect(FONT_EF_LIVE, pPos)
{
	score = plusScore;
}

void CPlusScoreFont::Render(BitmapText *text)
{
	if (score == 1000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+1000");
	}
	if (score == 2000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+2000");
	}
	if (score == 3000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+3000");
	}
	if (score == 5000)
	{
		text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "score+5000");
	}
}

/******���x���A�b�v�����Ƃ���LevelUp�̕������o��******/
CLevelUpFont::CLevelUpFont(VECTOR &pPos) : CEffect(64, pPos)
{
	pos = VGet(pPos.x - 80, pPos.y - 64, 0);
}

void CLevelUpFont::Render(BitmapText *text)
{
	text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "level up!");

}

/*******���x���A�b�v�����Ƃ���Player�𒆐S�Ɋg�傷��~�����*******/
#define CIRCLR_EF_LIVE 64

CLevelUpCircle::CLevelUpCircle(VECTOR & pPos) :CEffect(CIRCLR_EF_LIVE, pPos)
{
}

void CLevelUpCircle::Render(BitmapText *text)
{
	DrawCircle((int)pos.x, (int)pos.y, animCnt * 3, GetColor(255, 255, 255), FALSE);
}

/*********���x���A�b�v�����Ƃ��ɃX�L���|�C���g�摜��`��*********/
#define IMG_EF_LIVE 64

CImg::CImg(VECTOR & pPos, int * pGraphic) :CEffect(IMG_EF_LIVE, pPos)
{
	graphic = pGraphic;
	pos.y += 16;
}

void CImg::Render(BitmapText *text)
{
	text->textDraw((int)pos.x, (int)pos.y--, 2.0f, "+");
	DrawRotaGraph((int)pos.x + 64, (int)pos.y--, 1.5, 0, *graphic, TRUE);
}

CBossReady::CBossReady(VECTOR & pPos, int * pDangerGraphic, int* pYellowGraphic) : CEffect(150, pPos)
{
	dangerGraphic = pDangerGraphic;
	yellowGraphic = pYellowGraphic;
	a = 0;
	plusFlag = true;
}

void CBossReady::Render(BitmapText * text)
{
	if (plusFlag == false)
	{
		a -= 5;
	}
	else
	{
		a += 5;
	}
	if (a > 180)
	{
		plusFlag = false;
	}
	if (a < 0)
	{
		plusFlag = true;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, a);
	DrawGraph(0, 0, *yellowGraphic, TRUE);
	DrawRotaGraph((int)SCREEN_WIDTH_HALF, (int)SCREEN_HEIGHT_HALF, 1.0, 0, *dangerGraphic, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
