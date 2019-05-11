#pragma once

#define EF_BOMB_GRAPHIC 7
#define EF_AIR_GRAPHIC 8
#define EF_STATUS_LEVEL_GRAPHIC 10

class BitmapText;

//�G�t�F�N�g�̊��N���X
class CEffect
{
protected:
	//���W
	VECTOR pos;
	//�O���t�B�b�N
	int graphic[16];
	//�`�ʎ��Ɏg�p����ԍ�
	int animCnt;
	//�O���t�B�b�N����
	int graphicNumber;
	//�`�ʊp�x
	double animRad;
	//�`�ʃT�C�Y
	double animSize;
	//�G�t�F�N�g�̐����t���O�@true=����
	bool flag;
	//�ҋ@���ԁB�A���ŃG�t�F�N�g���ĂԂƂ��Ɏg�p
	int dirayTime;
	//�ҋ@���Ԃ����ׂčς񂾂��ǂ���
	bool dirayOk;
	//Diray��Cnt
	int dirayCnt;
public:
	CEffect(int liveCnt, VECTOR pPos);
	CEffect(int graphicNum, double size, double rad, VECTOR pPos, int diray);
	//~CEffect() { delete[] graphic; };
	//animCnt�𑫂�����graphicNumber�ȏ�ɂȂ�����t���O��|��
	void Update();
	//�`��
	virtual void Render(BitmapText *text) = 0;
	//�����t���O��Ԃ�
	bool GetFlag() { return flag; };
};

//���j�G�t�F�N�g
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

//�X�R�A�����G�t�F�N�g
class CPlusScoreFont :public CEffect
{
public:
	CPlusScoreFont(VECTOR &pPos, int plusScore);
private:
	int score;
	void Render(BitmapText *text);
};

//���x���A�b�v���̉~
class CLevelUpCircle :public CEffect
{
public:
	CLevelUpCircle(VECTOR &pPos);
	void Render(BitmapText *text);
};

//���x���A�b�v���̕���
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