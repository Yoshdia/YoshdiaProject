#include"DxLib.h"
#include"EffectManager.h"
#include"Define.h"


CEffectManager::CEffectManager()
{
	//NULL�ŏ�����
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		effect[num] = NULL;
	}
	//�G�t�F�N�g���Ƃ̃O���t�B�b�N��ǂݍ���
	//LoadDivGraph("img/effect/bomb.png", EF_BOMB_GRAPHIC, 8, 2, 100, 100, bombGraphic, TRUE);
	LoadDivGraph("img/Space Shooter - 1/Fx/Fx8.png", EF_BOMB_GRAPHIC, 7, 1, 32, 32, bombGraphic, TRUE);
	LoadDivGraph("img/Space Shooter - 1/Fx/Fx7.png", EF_AIR_GRAPHIC, 8, 1, 82, 72, airGraphic, TRUE);
	LoadDivGraph("img/UI/StatusUp.png", EF_STATUS_LEVEL_GRAPHIC, 10, 1, 96, 96, statusLevelUoGraphic, TRUE);

	dangerGraphic = new int;
	*dangerGraphic = LoadGraph("img/UI/DangerLavel.JPG");
	yellowGraphic = new  int;
	*yellowGraphic = LoadGraph("img/UI/YellowBack.JPG");

}

CEffectManager::~CEffectManager()
{
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		delete effect[num];
	}
	delete dangerGraphic;
	delete yellowGraphic;

}

void CEffectManager::Update()
{
	//�������ꂽ�G�t�F�N�g���X�V������
	//�G�t�F�N�g���Đ����I������猚�t���O�������Ă����ꍇ������J������NULL������
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		if (effect[num] != NULL)
		{
			effect[num]->Update();
			if (effect[num]->GetFlag() == false)
			{
				delete effect[num];
				effect[num] = NULL;
			}
		}
	}
}

void CEffectManager::EffectSpawn(VECTOR pPos, int efNum, double size, double rad, int diray)
{
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		if (effect[num] == NULL)
			//Bomb�̂Ƃ��͔����G�t�F�N�g
			if (efNum == eBomb)
			{
				effect[num] = new CBomb(pPos, bombGraphic, size, rad, diray);
				break;

			}
		//Air�̂Ƃ��͋�C�̂悤�ȃG�t�F�N�g
		if (efNum == eAir)
		{
			effect[num] = new CAirBomb(pPos, airGraphic, size, rad, diray);
			break;
		}
		if (efNum == eStatusLevelUp)
		{
			effect[num] = new CStatusLevelUp(pPos,statusLevelUoGraphic, size, rad, diray);
			break;
		}
		if (efNum == eBossReady)
		{
			effect[num] = new CBossReady(pPos, dangerGraphic, yellowGraphic);
			break;
		}
	}
}

void CEffectManager::FontSpawn(VECTOR pPos, int efNum, int scoreNum)
{
	for (int num = 1; num < EFFECT_NUM; num++)
	{
		if (effect[num] == NULL)
		{
			if (efNum == ePlusScore)
			{
				effect[num] = new CPlusScoreFont(pPos, scoreNum);
				break;
			}
			if (efNum == eLevelUpFont)
			{
				effect[num] = new CLevelUpFont(pPos);
				break;
			}
		}
	}
}

void CEffectManager::ShapeSpawn(VECTOR pPos, int efNum)
{
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		if (efNum == eCircle)
		{
			if (effect[num] == NULL)
			{
				effect[num] = new CLevelUpCircle(pPos);
				break;
			}
		}
	}
}

void CEffectManager::ImageSpawn(VECTOR pPos, int * graphic)
{
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		if (effect[num] == NULL)
		{
			effect[num] = new CImg(pPos, graphic);
			break;
		}
	}
}

void CEffectManager::Render(BitmapText *text)
{
	for (int num = 0; num < EFFECT_NUM; num++)
	{
		if (effect[num] != NULL)
		{
			effect[num]->Render(text);
		}
	}
}