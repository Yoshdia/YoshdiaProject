#pragma once

class CEnemy;
class CEffectManager;
class CWave;
class CPlayerEnemyCommon;
class CSound;

#define ENEMY_NUM 30

class CEnemyManager
{
	CEnemy *enemy[ENEMY_NUM];
	CEffectManager *effectManager;
	CWave *wave;
public:
	CEnemyManager(int stageNum);
	~CEnemyManager();

	void Spawn();
	//�G�l�~�[��CPlayerEnemyCommon�^�ɃL���X�g���ĕԂ�
	CPlayerEnemyCommon *GetEnemy(int num) { return (CPlayerEnemyCommon*)enemy[num]; }

	//�X�V
	void Update(CEffectManager *effect,CSound *sound);
    //enemy��Flag���|�ꂽ�Ƃ��Ƀ����_���񐔔���������
    void EnemyBomb(int enemyNum, CEffectManager *effect);
	//�`��
	void Render();
	//enemy��shotReadyFlag��Ԃ�
	bool GetShotReady(int num);
	void SetShotReady(int num);
	int GetShotCheck(int num);
	int GetHp(int num);
	bool GetBossFlag(int num);
	//delete Wave��Game���ōs����悤��
	void StageChangeInitWave(int stageNum);
private:
	//�G�̉摜
	int enemyGraphic[8];

};