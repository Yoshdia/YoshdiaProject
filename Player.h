#pragma once

#include"Object.h"
#include"Bullet.h"

class CManager;
class CBulletManager;
class CEffectManager;
class CPause;
class CSound;
class BitmapText;

struct SCommonStatus
{
	//Bullet.h�Ő錾{�U����,���x,�T�C�Y,�ʔ\��,���x��}
	SBulletStatus Status;
	//�J�E���g
	float Cnt;
	//���ˉ\���
	float Interval;
	//�O���t�B�b�N
	int Graphic[30];
};

class CPlayer :public CPlayerEnemyCommon
{
	CManager *manager;
	//CBulletManager *bulletManager;
public:
	//�R���X�g���N�^�i�C���X�^���X�������ɍŏ��ɌĂ΂��֐��j
	CPlayer(CManager *, int point);
	//�f�X�g���N�^�i�C���X�^���X�폜���ɌĂ΂��֐��j
	~CPlayer();
	//�X�V
	void Render(CEffectManager *effectManager, BitmapText *text);
	//�X�V
	void Update(CBulletManager *bullet, CEffectManager *effectManager, CSound *sound);
	//���x���A�b�v����
	CPause* CreateLevelUp();

	//BottonGraohic���̍��g��`�ʂ����� LevelUp����Ă΂��
	//void RenderBlackBotton(int bottonX, int bottonY);
	//���x���A�b�v�֘A LevelUp����Ă΂��
	bool LevelUp(int casol, CSound *sound);
	bool LevelUpEnd();
	//�󂯎���������X�R�A�ɑ���
	void PlusScore(int plusScore);
	int GetcStatus() { return cStatus.Status.aStatus; };

	void ShotBirst();

	//�C���^�[�o��ZC�摜�̂ݕ`�� 
	void RenderFrontBotton(int bottonX, int bottonY);
	void RenderBackBotton(int bottonX, int bottonY);
	//�󂯎�������W��borranGraphic��botton�Ԗڂ̉摜��\������
	void RenderBottonDraw(int botton, int x, int y);
	//Hp��1������BGame�ŃA�C�e������肵���Ƃ��ɌĂ΂��
	void PlusHp() { hp++; };
	//���x���A�b�v��ʂ̐����摜�ALevelUp����Ă΂��
	void RenderLevelUpImg();
	//���x���A�b�v��ʂ̐��������ALevelUp����Ă΂��
	void RenderLevelUpFont(int casol);

	int GetHp() { return hp; }
	//�c��skillPoint�̕`��	Player��LevelUp���Ă΂��
	void RenderSkill(float skillX, float skillY);

	int GetPlayerAllHp() { return playerAllHp; };

	void SetPos(VECTOR returnPos){pos=returnPos;};

	void SubAllHp(){playerAllHp--;};

	void SetInvincible(){damegedInvincibleFlag=true;};
private:
	float moveSpeed;
	//ChargePause����Ă΂��A�t���O���o������o�[�X�g����
	bool BirstReadyFlag;
	int *chargeGraphic;
	int drawRad;
	//�X�e�[�^�X�̏�����
	void InitStatus();
	//�e���Ƃ̏�����
	void InitBulletStatus(SCommonStatus *iStatus, float iSpeed, float iInterval);
	//���˃��[�`��,�󂯎����bulletManager��Shot�֋��̃X�e�[�^�X����W��^����
	void Shot(CBulletManager *bullet, SCommonStatus *SStatus, bool key, int beforeShot, int shot);
	//�ړ����[�`��
	void Move();
	//�ړ�����
	void MoveRimit();
	//�������x��
	int levelSum;
	//�X�R�A�A�o���l
	int score;
	//���x���A�b�v�ɕK�v��score�A���x���A�b�v�̓x�ɐ���������
	int levelUpScore;
	//levelUpScore�Ƀv���X�����ʁB���x���A�b�v�̓x�ɑ�����
	int levelUpScorePlus;
	//�X�R�A�����ȏ�ɂȂ�ƃ��x�����オ��
	void ScoreLevelUp(CEffectManager *effectManager, CSound *sound);
	//�����Ƃ̃X�e�[�^�X
	SCommonStatus zStatus;
	SCommonStatus cStatus;
	SCommonStatus vStatus;
	//�C���^�[�o��ZXCV�̉摜
	int *bottonGraphic;
	//�C���^�[�o���Q�[�W�̉摜
	int *blackGraphic;
	//skillPoint�̉摜
	int *skillGraphic;
	//Player�̃T�C�Y
	float size;
	//�A�[�}�[���������Ă��邩�A�����Ă�����t���O������
	bool haveArmor;
	//�A�[�}�[����������ۂ̏���
	void ArmorProcces();
	int *armorGraphic;
	float armorDrawRad;

	//�c��C���^�[�o���̕`��
	void RenderInterval(float &interval, float &intervalMax, int x);

	int *birstCaseGraphic;
	int *birstGraphic;
	void RenderBirstGauge();

	//�v���C���[�͈���������łȂ�������ȏ��ʊO�ɏo��ꍇ�����邽�ߏՓˏ󋵂�ۑ�����֐���ʂɗp��
	void ComeOutScreenPlayer(double ScreenOut, int *direction);

	//�X�L���|�C���g
	int skillPoint;

	int attackLevel;
	int diffendLevel;
	bool AttackLevelUp();
	bool DiffendLevelUp();
	void ShotLevelUp(SCommonStatus* bulletStatu);
	//������������Ă�悤��
	bool canShotPlus;
	bool canShotBirst;
	void LevelUpSizeDown();
	void LevelUpSpeedUp();
	//bool LevelMaxCheck();
	//���x���A�b�v�ł��邱�Ƃ�`����J�E���g
	int drawLevelCnt;
	//�o�[�X�g�̕�����`�ʂ���J�E���g
	//int drawBirstCnt;
	//���x���A�b�v��ʂɕ\�����������摜�BLevelUp����Ă΂��֐��ɂĎg�p
	int *levelUpGraphic;
	//���x���A�b�v��ʂ̐����摜��؂�Ԃ邽�߂̃J�E���g
	int levelUpGraphicCnt;

	void RenderArmor();

	int birstMin;
	int birstMax;
	//�R���g���[���[�̃{�^��ABXY�摜
	int *controlerGraphic;
	//�o�[�X�g�Q�[�W�ɕ\������Y�摜��_�ł����邽�߂̃J�E���g
	int controlerXCnt;
	int controlerYCnt;

	int *levelGuideBlack;
	int *levelGuideGraphic;
	void RenderGuide(int num, int guideX);
	int *levelGuideFont;
	int *levelGuideFontBlack;
	int *needSkillPointGraphic;
	//�v���C���[�̎c��c�@
	int playerAllHp;
};