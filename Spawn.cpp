#include"Spawn.h"
#include"Enemys.h"
//#include"DxLib.h"
#include"Define.h"

enum eSpawn
{
	//��т̂ݏo�����邽��ShotInterval������Spawn�ɓn��
	eNoInterval = 10
};

CSpawn::CSpawn(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck)
{
	spawnflg = false;
	spawnEnd = false;
	enemyGraphic = pEnemyGraphic;
	pos = pPos;
	vPos = pvPos;
	bullet = bulletCheck;
}

void CSpawn::Update()
{
	//�ŏ���cnt��r�o�Ԋu�̍ő吔�ŏ���������
	static int cnt = spawnInterval;
	cnt++;

	//cnt���r�o�Ԋu�ɒB�����Ƃ�
	if (cnt >= spawnInterval)
	{
		//�r�o�����鏀�����ł������Ƃ�m�点��t���O
		spawnflg = true;
		//�J�E���g���Z�b�g
		cnt = 0;
		//�c��̔r�o�������炷
		spawnNum--;
	}

	//�S�Ă̔r�o���I��������Ƀt���O����������
	if (spawnNum <= 0)
	{
		spawnEnd = true;
	}
}

/************************************************************************/
CSpawn1::CSpawn1(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic,pPos, pvPos, bulletCheck)
{
	spawnNum = 3;
	spawnInterval = 30;
}

CEnemy* CSpawn1::Spawn()
{
	spawnflg = false;
	return new CEnemyTurn(enemyGraphic, pos, vPos, bullet);
}

/************************************************************************/
CSpawn2::CSpawn2(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 3;
	spawnInterval = 30;
	bulletPos = pPos;
}

CEnemy* CSpawn2::Spawn()
{
	bulletPos = pos;
	switch (spawnNum)
	{
	case(1):
		bulletPos.y -= 100;
		break;
	case(0):
		bulletPos.y += 100;
		break;
	}
	spawnflg = false;
	return new CEnemyStraight(enemyGraphic, bulletPos, vPos, bullet);
}

/************************************************************************/
CSpawn3::CSpawn3(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 1;
	spawnInterval = eNoInterval;
}

CEnemy* CSpawn3::Spawn()
{
	spawnflg = false;
	return new CEnemyAddSpeed(enemyGraphic, pos, vPos, bullet);
}

/************************************************************************/
CSpawn4::CSpawn4(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 1;
	spawnInterval = eNoInterval;
}

CEnemy* CSpawn4::Spawn()
{
	spawnflg = false;
	return new CEnemyFirstBoss(enemyGraphic, pos, vPos, bullet);
}

/************************************************************************/
CSpawn5::CSpawn5(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 6;
	spawnInterval = 15;
}

CEnemy * CSpawn5::Spawn()
{
	spawnflg = false;
	return new CEnemySnake(enemyGraphic, pos, vPos, bullet);
}

/************************************************************************/
CSpawn6::CSpawn6(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 1;
	spawnInterval = eNoInterval;
}

CEnemy * CSpawn6::Spawn()
{
	spawnflg = false;
	return new CEnemySudden(enemyGraphic, pos, vPos, bullet);
}

/************************************************************************/
CSpawn7::CSpawn7(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 1;
	spawnInterval = eNoInterval;
}

CEnemy* CSpawn7::Spawn()
{
	spawnflg = false;
	return new CEnemySecondBoss(enemyGraphic, pos, vPos, bullet);
}

/************************************************************************/
CSpawn8::CSpawn8(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck) :CSpawn(pEnemyGraphic, pPos, pvPos, bulletCheck)
{
	spawnNum = 1;
	spawnInterval = eNoInterval;
}

CEnemy* CSpawn8::Spawn()
{
	spawnflg = false;
	return new CEnemyThirdBoss(enemyGraphic, pos, vPos, bullet);
}