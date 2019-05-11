#include"BackGround.h"
#include"Define.h"


/***********************************************************/

//�`��T�C�Y�ƕ`��p�x�̑������̓����_���łƂ�
CMoveBackGround::CMoveBackGround(VECTOR pPos, int &pGraphic, bool spinFlag)
{
	pos = pPos;
	flag = true;
	drawSize = (GetRand(15)*0.1f) + 1;
	drawRad = 0;
	drawRadAdd = (GetRand(70) - 35)*0.0001f;
	//�󂯎�����摜�����̏ꍇ�Ɍ��t���O�������Ă���ꍇ��]���x��0�ɂ���
	if (spinFlag == true)
	{
		drawRadAdd = 0;
	}
	graphic = pGraphic;
}

void CMoveBackGround::Update()
{
	pos.x -= 0.5f;
	if (pos.x <= 0 - 50)
	{
		flag = false;
	}
}

void CMoveBackGround::Render()
{
	DrawRotaGraph((int)pos.x, (int)pos.y, drawSize, drawRad += drawRadAdd, graphic, TRUE);
}

/***********************************************************/
//�ꏊ���w�肵�ē����Ȃ��w�i��`�ʂ���
CNoMoveBackGround::CNoMoveBackGround(int pGraphic, VECTOR pPos)
{
	pos = pPos;
	graphic=pGraphic;
	flag = true;
}

void CNoMoveBackGround::Update()
{
}


//�󂯎�������W����width,height�֎l�p�`�����
void CNoMoveBackGround::Render()
{
	float drawSize = 6.0f;
	DrawRotaGraph((int)pos.x, (int)pos.y, drawSize, 0, graphic, TRUE);

}