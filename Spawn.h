#pragma once
#include"DxLib.h"

class CEnemy;

//�X�|�[�������N���X
class CSpawn
{
protected:
	CSpawn(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//�X�|�[������G�̐�
	int spawnNum;
	//spawnNum�������̏ꍇ�A����炪�N���Ԋu
	int spawnInterval;
	//�G���X�|�[�����钼�O�Ɍ��t���O
	bool spawnflg;
	//���ׂĂ̓G��r�o���I������猚�t���O
	bool spawnEnd;
	//CWave����󂯎��A�r�o���W�ƈړ��������
	VECTOR pos;
	VECTOR vPos;
	//�r�o�����G�����˂��鋅�̎���
	int bullet;
public:
	//cnt��spawnInterval�𒴂����Ƃ���spawnFlag����������֐�
	void Update();
	//spawnFlg�������Ă����ԂŌĂ΂��B�����������G��Ԃ�
	virtual CEnemy* Spawn() = 0;
	//spawnFlg��Ԃ�
	bool GetFlag() { return spawnflg; }
	//���ׂĂ̓G��r�o���I�������delete�����
	bool GetEndFlag() { return spawnEnd; }
	//�G�̉摜
	int enemyGraphic;
};

//EnemyTurn��3�̏o������
class CSpawn1 :public CSpawn
{
public:
	CSpawn1(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos,int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};

//EnemyStraight��3�̏o������
class CSpawn2 :public CSpawn
{
public:
	CSpawn2(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
private:
	VECTOR bulletPos;
};

//EnemyAddSpeed��1�̏o������
class CSpawn3 :public CSpawn
{
public:
	CSpawn3(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};

//Stage1�̃{�X�B���j�ŃX�e�[�W�`�F���W
class CSpawn4 :public CSpawn
{
public:
	CSpawn4(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};

//EnemySnake��5�̏o������
class CSpawn5 :public CSpawn
{
public:
	CSpawn5(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};

//�}�ɉ������Ă���
class CSpawn6 :public CSpawn
{
public:
	CSpawn6(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};

//Stage2�̃{�X�B���j�ŃX�e�[�W�`�F���W
class CSpawn7 :public CSpawn
{
public:
	CSpawn7(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};

//Stage3�̃{�X�B���j�ŃX�e�[�W�`�F���W
class CSpawn8 :public CSpawn
{
public:
	CSpawn8(int pEnemyGraphic, VECTOR pPos, VECTOR pvPos, int bulletCheck);
	//���N���X�Q��
	CEnemy* Spawn();
};