#pragma once

class CPlayer;
class CBulletManager;
class CEffectManager;
class CEnemyManager;
class CCollision;
class CEnemyBulletManager;
class CBackGroundSpawn;
class CPause;
class CItemSpawner;
class CSound;
class BitmapText;

#include"Define.h"
#include"DxLib.h"


class CGame :public CScene
{
    CPlayer *player;
    CBulletManager *bulletManager;
    CEffectManager *effectManager;
    CEnemyManager *enemyManager;
    CCollision *collision;
	CEnemyBulletManager *enemyBulletManager;
	CBackGroundSpawn *backGroundSpawn;
	CPause *pause;
	CItemSpawner *itemSpawner;
public:
    CGame(CManager *pManager,int point);
    ~CGame();
    //�X�V
    void Update(CSound *sound);
    //�`��
    void Render(BitmapText *text);
private:
    //�̗̓Q�[�W�̃O���t�B�b�N�BPlayer��Enemy�ɓn��
    int gaugeGraphic[G_GRAPHIC];
    //�����蔻����s���֐�
    void CheckHit(CSound *sound);
    //�G�Ƃ̓����蔻��܂Ƃ�
    void CheckHitEnemy(CSound *sound);
	//�΃v���C���[
	void CheckHitEnemyPlayer(int enemyNum, CSound *sound);
	//�΃v���C���[�o���b�g
	void CheckHitEnemyPlayerBullet(int enemyNum, CSound *sound);
	//�G�̋��Ƃ̓����蔻��܂Ƃ�
	void CheckHitEnemyBullet(CSound *sound);
	//�΃v���C���[
	void CheckHitEnemyBulletPlayer(int bulletNum, CSound *sound);
	//��VShot
	void CheckHitEnemyBulletVShot(int bulletNum, CSound *sound);
	//�΃A�C�e��
	void CheckHitItemPlayer(CSound *sound);
	//o1��o2�̒��S�ɔ������N����
	void BombSpawn(VECTOR o1Pos,VECTOR o2Pos);
	//�������̍��w�i
	int blackScreenImg;
	//�V�[���ڍs����
	void ChangeScene(CSound *sound);
	//�f�o�b�O�p�̃V�[���ڍs
	//int DebugScene();
	//���݂̃X�e�[�W���L���B�ŏ���Title����󂯎��
	int nowStage;
	//���ׂẴX�e�[�W���N���A������̑ҋ@����
	int finalCnt;
	//�Q�[���I���B���ׂẴX�e�[�W���N���A�����猚��
	bool gameEnd;
	//�G�����j�����Ƃ��ɃX�e�[�W��ς���֐�
	void BreakEnemyChangeStage(CSound *sound);
	//�Q�[���J�n���ɔw�i�ɐ���`�悳���邽�߂̊֐�
	void StartSpawnBackGround();

	bool gameOver;
	int filter;
};