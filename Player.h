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
	//Bullet.hで宣言{攻撃力,速度,サイズ,個別能力,レベル}
	SBulletStatus Status;
	//カウント
	float Cnt;
	//発射可能上限
	float Interval;
	//グラフィック
	int Graphic[30];
};

class CPlayer :public CPlayerEnemyCommon
{
	CManager *manager;
	//CBulletManager *bulletManager;
public:
	//コンストラクタ（インスタンス生成時に最初に呼ばれる関数）
	CPlayer(CManager *, int point);
	//デストラクタ（インスタンス削除時に呼ばれる関数）
	~CPlayer();
	//更新
	void Render(CEffectManager *effectManager, BitmapText *text);
	//更新
	void Update(CBulletManager *bullet, CEffectManager *effectManager, CSound *sound);
	//レベルアップ条件
	CPause* CreateLevelUp();

	//BottonGraohic内の黒枠を描写させる LevelUpから呼ばれる
	//void RenderBlackBotton(int bottonX, int bottonY);
	//レベルアップ関連 LevelUpから呼ばれる
	bool LevelUp(int casol, CSound *sound);
	bool LevelUpEnd();
	//受け取った数をスコアに足す
	void PlusScore(int plusScore);
	int GetcStatus() { return cStatus.Status.aStatus; };

	void ShotBirst();

	//インターバルZC画像のみ描画 
	void RenderFrontBotton(int bottonX, int bottonY);
	void RenderBackBotton(int bottonX, int bottonY);
	//受け取った座標にborranGraphicのbotton番目の画像を表示する
	void RenderBottonDraw(int botton, int x, int y);
	//Hpが1増える。Gameでアイテムを入手したときに呼ばれる
	void PlusHp() { hp++; };
	//レベルアップ画面の説明画像、LevelUpから呼ばれる
	void RenderLevelUpImg();
	//レベルアップ画面の説明文字、LevelUpから呼ばれる
	void RenderLevelUpFont(int casol);

	int GetHp() { return hp; }
	//残りskillPointの描画	PlayerとLevelUpか呼ばれる
	void RenderSkill(float skillX, float skillY);

	int GetPlayerAllHp() { return playerAllHp; };

	void SetPos(VECTOR returnPos){pos=returnPos;};

	void SubAllHp(){playerAllHp--;};

	void SetInvincible(){damegedInvincibleFlag=true;};
private:
	float moveSpeed;
	//ChargePauseから呼ばれる、フラグが経ったらバーストする
	bool BirstReadyFlag;
	int *chargeGraphic;
	int drawRad;
	//ステータスの初期化
	void InitStatus();
	//弾ごとの初期化
	void InitBulletStatus(SCommonStatus *iStatus, float iSpeed, float iInterval);
	//発射ルーチン,受け取ったbulletManagerのShotへ球のステータスや座標を与える
	void Shot(CBulletManager *bullet, SCommonStatus *SStatus, bool key, int beforeShot, int shot);
	//移動ルーチン
	void Move();
	//移動制限
	void MoveRimit();
	//総合レベル
	int levelSum;
	//スコア、経験値
	int score;
	//レベルアップに必要なscore、レベルアップの度に数が増える
	int levelUpScore;
	//levelUpScoreにプラスされる量。レベルアップの度に増える
	int levelUpScorePlus;
	//スコアが一定以上になるとレベルが上がる
	void ScoreLevelUp(CEffectManager *effectManager, CSound *sound);
	//球ごとのステータス
	SCommonStatus zStatus;
	SCommonStatus cStatus;
	SCommonStatus vStatus;
	//インターバルZXCVの画像
	int *bottonGraphic;
	//インターバルゲージの画像
	int *blackGraphic;
	//skillPointの画像
	int *skillGraphic;
	//Playerのサイズ
	float size;
	//アーマーを所持しているか、持っていたらフラグが建つ
	bool haveArmor;
	//アーマーを所持する際の処理
	void ArmorProcces();
	int *armorGraphic;
	float armorDrawRad;

	//残りインターバルの描画
	void RenderInterval(float &interval, float &intervalMax, int x);

	int *birstCaseGraphic;
	int *birstGraphic;
	void RenderBirstGauge();

	//プレイヤーは一方向だけでなく二方向以上画面外に出る場合があるため衝突状況を保存する関数を別に用意
	void ComeOutScreenPlayer(double ScreenOut, int *direction);

	//スキルポイント
	int skillPoint;

	int attackLevel;
	int diffendLevel;
	bool AttackLevelUp();
	bool DiffendLevelUp();
	void ShotLevelUp(SCommonStatus* bulletStatu);
	//球を一つ多く撃てるように
	bool canShotPlus;
	bool canShotBirst;
	void LevelUpSizeDown();
	void LevelUpSpeedUp();
	//bool LevelMaxCheck();
	//レベルアップできることを伝えるカウント
	int drawLevelCnt;
	//バーストの文字を描写するカウント
	//int drawBirstCnt;
	//レベルアップ画面に表示される説明画像。LevelUpから呼ばれる関数にて使用
	int *levelUpGraphic;
	//レベルアップ画面の説明画像を切り返るためのカウント
	int levelUpGraphicCnt;

	void RenderArmor();

	int birstMin;
	int birstMax;
	//コントローラーのボタンABXY画像
	int *controlerGraphic;
	//バーストゲージに表示するY画像を点滅させるためのカウント
	int controlerXCnt;
	int controlerYCnt;

	int *levelGuideBlack;
	int *levelGuideGraphic;
	void RenderGuide(int num, int guideX);
	int *levelGuideFont;
	int *levelGuideFontBlack;
	int *needSkillPointGraphic;
	//プレイヤーの残り残機
	int playerAllHp;
};