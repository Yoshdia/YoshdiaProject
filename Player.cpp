#include"DxLib.h"
#include"Object.h"
#include"Manager.h"
#include"Define.h"
#include"BulletManager.h"
#include"Player.h"
#include"LevelUp.h"
#include"EffectManager.h"
#include"Sound.h"
#include"Pause.h"
#include"BitMapFont.h"

//チップサイズ
#define P_CHIP_SIZE 91
//プレイヤーが画面外に出れる限界
#define P_RIMIT 16
//デフォルトHP
//#define P_DEF_HP 10
//デフォルトAP
#define P_DEF_AP 200
#define P_DEF_ATK 1

//弾のデフォルトステータス
//スピード
#define Z_DEF_SPEED 50.0f
#define C_DEF_SPEED 50.0f

//弾ごとのチップサイズ
#define Z_CHIP_SIZE 8.0f
#define C_CHIP_SIZE 8.0f
#define V_CHIP_SIZE 54.0f
//弾のインターバルボタンのチップサイズ
#define BOT_CHIP_SIZE 96
//弾ごとのデフォルトインターバル
#define Z_INTERVAL 40.0f
#define C_INTERVAL 40.0f
#define V_INTERVAL 40.0f
//HPを表示させる座標
#define HP_X 320
#define HP_Y 64
//APを表示させる座標
#define AP_X 32
#define AP_Y SCREEN_HEIGHT-128
//インターバルボタンを表示させる座標
#define BOTTON_X 128
#define BOTTON_Y 64
//インターバルボタンのグラフィック枚数
#define KEY_GRAPHIC 18

#define DEF_SCORE_LEVEL 3000
#define SCORE_PLUS_DEF 3000
#define SCORE_PLUS 1000

#define BIRST_NEED 20000

CPlayer::CPlayer(CManager *pManager, int point)
{
	//CManagerのアドレス格納
	manager = pManager;
	//画像データ格納
	graphic = new int;
	*graphic = LoadGraph("img/Space Shooter - 1/Ship/Player.png");

	//位置を初期化
	pos = VGet(P_DEF_X, P_DEF_Y, 0);
	//ステータス初期化
	InitStatus();

	//弾ごとの初期化,画像のロード
	InitBulletStatus(&zStatus, Z_DEF_SPEED, Z_INTERVAL);
	LoadDivGraph("img/Shot/8Shots.png", (int)Z_GRAPHIC, 5, 6, (int)Z_CHIP_SIZE, (int)Z_CHIP_SIZE, zStatus.Graphic, TRUE);

	InitBulletStatus(&cStatus, C_DEF_SPEED, C_INTERVAL);
	LoadDivGraph("img/Shot/8Shots.png", (int)C_GRAPHIC, 5, 6, (int)C_CHIP_SIZE, (int)C_CHIP_SIZE, cStatus.Graphic, TRUE);

	InitBulletStatus(&vStatus, 0, V_INTERVAL);
	LoadDivGraph("img/effect/fire.png", (int)V_GRAPHIC, 1, 1, (int)V_CHIP_SIZE, (int)V_CHIP_SIZE, vStatus.Graphic, TRUE);

	//インターバルボタンの読み込み
	bottonGraphic = new int[KEY_GRAPHIC];
	LoadDivGraph("img/Ui/Botton.png", KEY_GRAPHIC, 6, 3, BOT_CHIP_SIZE, BOT_CHIP_SIZE, bottonGraphic, TRUE);
	//弾の残りインターバルを表示する際に表示する黒い線
	blackGraphic = new int;
	*blackGraphic = LoadGraph("img/UI/BlackGauge.png");
	skillGraphic = new int[4];
	LoadDivGraph("img/Space Shooter - 1/Item/Gem3.png", 4, 4, 1, 20, 20, skillGraphic, TRUE);

	chargeGraphic = new int[6];
	LoadDivGraph("img/Space Shooter - 1/Fx/Fx2.png", 6, 6, 1, 34, 34, chargeGraphic, TRUE);

	birstCaseGraphic = new int;
	*birstCaseGraphic = LoadGraph("img/UI/GaugeCase.png", TRUE);
	birstGraphic = new int;
	LoadDivGraph("img/UI/Gauge.png", 2, 2, 1, 4, 104, birstGraphic, TRUE);

	damegedInvincibleFlag = false;
	levelSum = 1;
	score = 0;
	levelUpScore = DEF_SCORE_LEVEL;
	levelUpScorePlus = SCORE_PLUS_DEF;
	canShotPlus = false;
	canShotBirst = false;

	armorGraphic = new int[2];
	armorGraphic[0] = LoadGraph("img/Space Shooter - 1/Fx/Shield.png");
	armorGraphic[1] = LoadGraph("img/Space Shooter - 1/Fx/Shield2.png");
	armorDrawRad = 0;
	//drawBirstCnt = 0;
	drawLevelCnt = 0;

	levelUpGraphic = new int[20];
	LoadDivGraph("img/UI/LevelUps.png", 20, 2, 10, 64, 64, levelUpGraphic, TRUE);

	birstMin = 0;
	birstMax = 0 + BIRST_NEED;

	controlerGraphic = new int[4];
	LoadDivGraph("img/UI/Controler.png", 4, 1, 4, 128, 128, controlerGraphic, TRUE);
	controlerXCnt = 0;
	controlerYCnt = 0;
	moveSpeed = P_SPEED;

	levelGuideGraphic = new int[30];
	LoadDivGraph("img/UI/Guide.png", 30, 3, 10, 128, 128, levelGuideGraphic, TRUE);
	levelGuideBlack = new int;
	*levelGuideBlack = LoadGraph("img/UI/BlackGuide.png", FALSE);
	levelGuideFont = new int[11];
	LoadDivGraph("img/UI/GuideFont.png", 11, 1, 11, 517, 128, levelGuideFont, TRUE);
	levelGuideFontBlack = new int[11];
	LoadDivGraph("img/UI/GuideFontBlack.png", 11, 1, 11, 517, 128, levelGuideFontBlack, TRUE);
	needSkillPointGraphic = new int;
	*needSkillPointGraphic = LoadGraph("img/UI/スキルポイント.png");

	playerAllHp = 3;
	//タイトル画面から受け取った難易度、0から2の値で初期スキルポイントを設定する
	switch (point)
	{
	case(1):
		skillPoint = 6;
		break;
	case(2):
		skillPoint = 10;
		break;
	}
}

CPlayer::~CPlayer()
{
	delete graphic;
	delete[] bottonGraphic;
	delete blackGraphic;
	delete[] skillGraphic;
	delete armorGraphic;
	delete[] levelUpGraphic;
	delete[] chargeGraphic;
	delete[] controlerGraphic;
	delete[] levelGuideGraphic;
	delete levelGuideBlack;
	delete[] levelGuideFont;
	delete[] levelGuideFontBlack;
	delete needSkillPointGraphic;
}

//更新
void CPlayer::Update(CBulletManager *bullet, CEffectManager *effectManager, CSound *sound)
{
	DamegeProcess(600);
	Move();
	ScoreLevelUp(effectManager, sound);
	//Shotそれぞれの発射ルーチン 
	Shot(bullet, &zStatus,
		manager->GetKey()[KEY_INPUT_SPACE] ||
		//Bボタン
		(manager->GetControl()[CONTROL_B] > 1) ||
		//Aボタン
		(manager->GetControl()[CONTROL_A] > 1),
		0, zShot);
	//背後に発射できるフラグが建っているとき、背後にも発射する
	if (canShotPlus == true)
	{
		Shot(bullet, &cStatus,
			manager->GetKey()[KEY_INPUT_SPACE] ||
			//Bボタン
			(manager->GetControl()[CONTROL_B] > 1) ||
			//Aボタン
			(manager->GetControl()[CONTROL_A] > 1),
			zShot, cShot);
	}
	//バーストのフラグが建っているときに発射できる
	if (canShotBirst == true)
	{
		Shot(bullet, &vStatus, BirstReadyFlag, cShot, vShot);
		BirstReadyFlag = false;
	}
	ArmorProcces();
}


CPause* CPlayer::CreateLevelUp()
{
	if ((manager->GetKey()[KEY_INPUT_RSHIFT] ||
		manager->GetKey()[KEY_INPUT_LSHIFT] ||
		//Xボタンが押されたときにレベルアップを開始する
		(manager->GetControl()[CONTROL_Y] == 1)) &&
		skillPoint >= 1)
	{
		return new CLevelUp(attackLevel);
	}
	if (vStatus.Cnt >= vStatus.Interval &&
		birstMin >= birstMax &&
		((manager->GetKey()[KEY_INPUT_V] == 1) ||
			//Yボタンが押されたときにバーストを撃つ
		(manager->GetControl()[CONTROL_X] == 1)))
	{
		birstMin = 0;
		return new CChargePause(chargeGraphic, pos, graphic, size);
	}
	if (manager->GetKey()[KEY_INPUT_0] == 1)
	{
		return new CPress0();
	}
	return NULL;
}

bool CPlayer::LevelUpEnd()
{
	//Xキーを押すかスキルポイントが0になるとレベルアップを終了する
	if ((manager->GetKey()[KEY_INPUT_Y] == 1 ||
		//Yボタン
		(manager->GetControl()[CONTROL_Y] == 1)) ||
		skillPoint <= 0)
	{
		return true;
	}
	return false;
}

void CPlayer::InitStatus()
{
	hp = 0;
	size = 2.0;
	float chipSizeX;
	float chipSizeY;
	GetGraphSizeF(*graphic, &chipSizeX, &chipSizeY);
	range = ((chipSizeX)*size) + 1;
	skillPoint = 0;
	attackLevel = 0;
	diffendLevel = 0;
}

void CPlayer::InitBulletStatus(SCommonStatus *iStatus, float iSpeed, float iInterval)
{
	(*iStatus).Status = { iSpeed,4,0,0 };
	(*iStatus).Cnt = 0;
	(*iStatus).Interval = iInterval;
}

void CPlayer::Shot(CBulletManager *bullet, SCommonStatus *SStatus, bool key, int beforeShot, int shot)
{
	//その球のカウント
	(*SStatus).Cnt++;
	//その弾のインターバルが発射間隔を上回っているか
	if ((*SStatus).Cnt > (*SStatus).Interval)
	{
		//cntが発射間隔以上に行き過ぎないように
		(*SStatus).Cnt = (*SStatus).Interval;
		//受け取ったキーが入力されているか
		if (key == true)
		{
			//bulletManagerのShotに画像、座標、ステータスと球の識別子を送る。
			bullet->Shot((*SStatus).Graphic, pos, (*SStatus).Status, beforeShot, shot);
			//cntをリセット
			(*SStatus).Cnt = 0;
		}
	}
}

//移動ルーチン
void CPlayer::Move()
{
	//移動する向き
	VECTOR vPos = VGet(0, 0, 0);
	//弾の発射を抑制するトリガー
	static int cnt = 0;
	//移動していないときは正規化する必要がないのでこれで移動しているか確認する
	bool moveFlag = false;

	if (manager->GetKey()[KEY_INPUT_LEFT] > 0 ||
		manager->GetKey()[KEY_INPUT_A] > 0 ||
		manager->GetControl()[CONTROL_LEFT] > 0)
	{
		vPos.x -= 1.0f;
		moveFlag = true;
	}
	if (manager->GetKey()[KEY_INPUT_RIGHT] > 0 ||
		manager->GetKey()[KEY_INPUT_D] > 0 ||
		manager->GetControl()[CONTROL_RIGHT] > 0)
	{
		vPos.x += 1.0f;
		moveFlag = true;
	}
	if (manager->GetKey()[KEY_INPUT_UP] > 0 ||
		manager->GetKey()[KEY_INPUT_W] > 0 ||
		manager->GetControl()[CONTROL_UP] > 0)
	{
		vPos.y -= 1.0f;
		moveFlag = true;
	}
	if (manager->GetKey()[KEY_INPUT_DOWN] > 0 ||
		manager->GetKey()[KEY_INPUT_S] > 0 ||
		manager->GetControl()[CONTROL_DOWN] > 0)
	{
		vPos.y += 1.0f;
		moveFlag = true;
	}
	//フラグが立っていてかつvPosが0でないときに正規化した値を座標に足す
	if (moveFlag == true)
	{
		normPos(&pos, vPos, moveSpeed, moveSpeed);
	}
	//移動制限
	MoveRimit();
}

void CPlayer::MoveRimit()
{
	//画面外に出る限界
	double rimit = -P_RIMIT;
	//四方向どこかに出ていないかをチェックする
	int direction[6];
	ComeOutScreenPlayer(rimit, direction);

	if (direction[up] == out)
	{
		pos.y = P_RIMIT;
	}
	if (direction[right] == out)
	{
		pos.x = SCREEN_WIDTH - P_RIMIT;
	}
	if (direction[down] == out)
	{
		pos.y = SCREEN_HEIGHT - P_RIMIT;
	}
	if (direction[left] == out)
	{
		pos.x = P_RIMIT;
	}
}

void CPlayer::ScoreLevelUp(CEffectManager *effectManager, CSound *sound)
{
	if (score >= levelUpScore)
	{
		sound->PlaySounds(eLevelUpSound, DX_PLAYTYPE_BACK);
		levelSum++;
		skillPoint++;
		levelUpScorePlus += SCORE_PLUS;
		if (levelUpScorePlus >= 9000)
		{
			levelUpScorePlus = 9000;
		}
		levelUpScore += levelUpScorePlus;
		effectManager->FontSpawn(pos, eLevelUpFont, 0);
		effectManager->ShapeSpawn(pos, eCircle);
		effectManager->ImageSpawn(pos, skillGraphic);
	}
}

#define LEVEL_X 1010
#define LEVEL_Y 16

//読みこんだグラフィックを描画
void CPlayer::Render(CEffectManager *effectManager, BitmapText *text)
{
	//残り残機を左下に表示
	for (int num = 0; num < playerAllHp; num++)
	{
		DrawRotaGraph(96 + (96 * num), SCREEN_HEIGHT - 96, 1.0, 0, *graphic, TRUE);
	}

	//右上に現レベルとスコアを表示
	text->textDraw(LEVEL_X, LEVEL_Y + 16, 2.0f, "level:   score:");
	SetFontSize(32);
	DrawFormatString(LEVEL_X + 32, LEVEL_Y, GetColor(255, 255, 255), "        %d              %d/%d", levelSum, score, levelUpScore);

	//ボタンを50カウントごとに点滅させる
	drawLevelCnt++;
	if (skillPoint > 0)
	{
		if (drawLevelCnt < 50)
		{
			text->textDraw(1010, 96, 2.0, "press [  ] to level up!");
			DrawRotaGraph(1232, 88, 0.4, 0, controlerGraphic[3], TRUE);
		}
		else if (drawLevelCnt > 100)
		{
			drawLevelCnt = 0;
		}
	}

	//その球に応じた球とそのインターバルを表示させる
	int bottonX = 0;
	bottonX = BOTTON_X + BOTTON_X * 0;
	RenderFrontBotton(bottonX, BOTTON_Y);
	RenderInterval(zStatus.Cnt, zStatus.Interval, bottonX);
	if (canShotPlus == true)
	{
		bottonX = BOTTON_X + BOTTON_X * 1;
		RenderBackBotton(bottonX, BOTTON_Y);
		RenderInterval(cStatus.Cnt, cStatus.Interval, bottonX);
	}

	//バーストできる状態ならボタン、クールタイムを表示する
	if (canShotBirst == true)
	{
		RenderBirstGauge();
		bool intervalMax = false;
		if (vStatus.Cnt >= vStatus.Interval)
		{
			intervalMax = true;
		}
	}
	//プレイヤーのバリアを表示
	RenderArmor();

	//現在のスキルポイントを表示　
	float skillPosX = pos.x;
	int animCnt = GetNowCount() % (12 * 100);
	skillPosX -= (skillPoint - 1) * 16;
	for (int num = 0; num < skillPoint; num++)
	{
		if (animCnt > 300)
		{
			animCnt = 0;
		}

		DrawRotaGraph((int)(skillPosX + (num * 32)), (int)pos.y - 90, 1.5f, 0, skillGraphic[animCnt / 100], TRUE);
	}

	//撃破状態でなければプレイヤーを表示
	if (hp >= 0)
	{
		DrawRotaGraph((int)pos.x, (int)pos.y, size, 1.57, *graphic, TRUE);
	}
	//撃破された状態なら、下へ移動させながら爆破エフェクトを産ませ続ける
	else
	{
		pos.y += 3.0f;
		for (int num = 0; num < 1; num++)
		{
			VECTOR playerPos = pos;
			playerPos.x += (GetRand(3) - 1) * 16;
			playerPos.y += (GetRand(3) - 1) * 16;
			int size = GetRand(3) + 5;
			int dirayTime = GetRand(5) * 10;
			effectManager->EffectSpawn(playerPos, eBomb, size, 0, dirayTime);
		}

	}
}

void CPlayer::RenderFrontBotton(int bottonX, int bottonY)
{
	int drawLevel = zStatus.Status.level / 3;;
	RenderBottonDraw(drawLevel, bottonX, bottonY);
}

void CPlayer::RenderBackBotton(int bottonX, int bottonY)
{
	int drawLevel = cStatus.Status.level / 3;;
	RenderBottonDraw(drawLevel + 6, bottonX, bottonY);
}

void CPlayer::RenderBirstGauge()
{
	int birstNum = 0;
	bool controlerYFlag = false;
	if (birstMin >= birstMax)
	{
		birstMin = birstMax;
		birstNum = 1;
		controlerYFlag = true;
	}

	float percent = (float)((birstMin * 100) / birstMax);
	percent *= 4.5;

	for (float num = 0; num <= percent; num += 4)
	{
		DrawRotaGraph((int)(430 + (num * 1)), 64, 1.0, 0, birstGraphic[birstNum], TRUE);
	}
	DrawRotaGraph(650, 64, 1.0, 0, *birstCaseGraphic, TRUE);

	if (controlerYFlag == true)
	{
		controlerXCnt++;
		if (controlerXCnt < 50)
		{
			DrawRotaGraph(650, 64, 1.0, 0, controlerGraphic[2], TRUE);
		}
		else if (controlerXCnt > 100)
		{
			controlerXCnt = 0;
		}
	}
}

//RenderBottonから受けとった画像を描写
void CPlayer::RenderBottonDraw(int botton, int x, int y)
{
	DrawRotaGraph(x, y, 1, 0, bottonGraphic[botton], TRUE);
}

void CPlayer::ArmorProcces()
{
	if (hp > 0)
	{
		haveArmor = true;
	}
	else
	{
		haveArmor = false;
	}
}

void CPlayer::RenderSkill(float skillX, float skillY)
{
	int animCnt = GetNowCount() % (12 * 100);
	for (int num = 0; num < skillPoint; num++)
	{
		if (animCnt > 300)
		{
			animCnt = 0;
		}
		DrawRotaGraph((int)(skillX + (32 * num)), (int)(skillY), 1.5f, 0, skillGraphic[animCnt / 100], TRUE);
	}
}

void CPlayer::RenderInterval(float & interval, float & intervalMax, int x)
{
	//現在のインターバルが現在何％か
	float rate = (interval * 100) / intervalMax;
	//描写したいサイズをrateにかける
	rate *= BOT_CHIP_SIZE;
	//%に戻す
	rate /= 100;

	//0からインターバルではなくインターバルから発射間隔までを描写するためrateから描写したいサイズを4pixelごとに描写させる
	for (float num = rate; num < BOT_CHIP_SIZE; num++)
	{
		if ((int)num % 4 == 0)
		{
			DrawRotaGraph(x, (int)((BOTTON_Y + (96 / 2)) - num - 2), 1, 0, *blackGraphic, TRUE);
		}
	}
}

void CPlayer::ComeOutScreenPlayer(double ScreenOut, int *direction)
{
	if (pos.y < 0 - ScreenOut)
	{
		direction[up] = out;
	}
	if (pos.x > SCREEN_WIDTH + ScreenOut)
	{
		direction[right] = out;
	}
	if (pos.y > SCREEN_HEIGHT + ScreenOut)
	{
		direction[down] = out;
	}
	if (pos.x < 0 - ScreenOut)
	{
		direction[left] = out;
	}
}

#define LEVEL_MAX 15

//レベルの総合管理、レベルマックスであったりスキルポイントが足りない場合falseを返し無反応に見せる
bool CPlayer::LevelUp(int casol, CSound *sound)
{
	//受け取ったcasolの値でどのステータスをレベルアップするのか決める
	switch (casol)
	{
	case(eAttack):
		if (AttackLevelUp() == true)
		{
			return false;
		}
		break;
	case(eDiffend):
		if (DiffendLevelUp() == true)
		{
			return false;
		}
		break;
	case(eZ):
		//レベルマックスの場合falseを返しもう一度選ばせる
		if (zStatus.Status.level >= LEVEL_MAX)
		{
			return false;
		}
		ShotLevelUp(&zStatus);
		zStatus.Status.level++;
		skillPoint--;
		break;
	case(eC):
		//レベルマックスの場合falseを返しもう一度選ばせる
		if (cStatus.Status.level >= LEVEL_MAX || canShotPlus == false)
		{
			return false;
		}
		ShotLevelUp(&cStatus);
		cStatus.Status.level++;
		skillPoint--;
		break;
	}
	//スキルポイントを減らしレベルアップが正常に完了したことを返す
	sound->PlaySounds(eEnterSound, DX_PLAYTYPE_BACK);
	return true;
}

#define INTERVAL_DOWN_LEVELUP 5.0f
#define SIZE_UP_LEVELUP 3.0f
#define P_SPEED_UP 0.5f
#define SPEED_UP_LEVELUP 1.0f
#define PLAYER_SIZE_DOWN 0.5f

//Playerのレベルアップ　スキルポイントが足りない場合trueを返しもう一度行わせる
bool CPlayer::AttackLevelUp()
{
	int needSkillPoint = 0;
	switch (attackLevel)
	{
	case(0):
		//フラグを建てバーストできるようになる
		needSkillPoint = 2;
		if (skillPoint < needSkillPoint)
		{
			return true;
		}
		skillPoint -= needSkillPoint;
		canShotBirst = true;
		break;
	case(1):
		needSkillPoint = 1;
		if (skillPoint < needSkillPoint)
		{
			return true;
		}
		skillPoint -= needSkillPoint;
		//移動速度が上がる
		LevelUpSpeedUp();
		break;
	case(P_CAN_SHOT_PLUS_LEVEL):
		needSkillPoint = 2;
		if (skillPoint < needSkillPoint)
		{
			return true;
		}
		skillPoint -= needSkillPoint;
		//フラグを建て背後へ撃てるようになる
		canShotPlus = true;
		birstMin = birstMax;
		break;
	}
	attackLevel++;
	return false;
}

#define DIFFEND_MAX 5

bool CPlayer::DiffendLevelUp()
{
	int needSkillPoint = 0;
	int whichLevelUp = diffendLevel % 2;
	if (diffendLevel > DIFFEND_MAX)
	{
		whichLevelUp = 10;
	}
	switch (diffendLevel)
	{
	case(0):
		needSkillPoint = 1;
		if (skillPoint < needSkillPoint)
		{
			return true;
		}
		skillPoint -= needSkillPoint;
		//アーマーが1増える
		hp++;
		break;
	case(1):
		needSkillPoint = 1;
		if (skillPoint < needSkillPoint)
		{
			return true;
		}
		skillPoint -= needSkillPoint;
		//サイズが小さくなる
		LevelUpSizeDown();
		break;
	default:
		return true;
		break;
	}
	diffendLevel++;
	return false;
}

enum eLevelUp
{
	//サイズアップ
	eSizeUp = 1,
	//インターバル減少
	eIntervalDown = 2,
	//銃口が増える
	ePlusShot = 6,
	//この球でヒットさせたときの獲得スコアが増える
	eScoreUp = 9,
	//弾速が上がる
	eSpeedUp = 12
};

void CPlayer::ShotLevelUp(SCommonStatus * bulletStatu)
{
	//レベルアップの項目を４つに分け現レベルに応じてステータスを変化させる
	int whichLevelUp = (bulletStatu->Status.level + 1) % 3;
	switch (whichLevelUp)
	{
	case(eSizeUp):
		bulletStatu->Status.size += SIZE_UP_LEVELUP;
		break;
	case(eIntervalDown):
		bulletStatu->Interval -= INTERVAL_DOWN_LEVELUP;
		break;
	default:
		if (bulletStatu->Status.level + 1 <= ePlusShot)
		{
			bulletStatu->Status.aStatus++;
		}
		else if (bulletStatu->Status.level + 1 == eSpeedUp)
		{
			bulletStatu->Status.speed += SPEED_UP_LEVELUP;
		}
		else if (bulletStatu->Status.level + 1 >= eScoreUp)
		{
			bulletStatu->Status.aStatus++;
		}
		break;
	}
}

void CPlayer::LevelUpSizeDown()
{
	size -= PLAYER_SIZE_DOWN;
	float chipSizeX;
	float chipSizeY;
	GetGraphSizeF(*graphic, &chipSizeX, &chipSizeY);
	range = ((chipSizeX)*size) + 1.0f;
}

void CPlayer::LevelUpSpeedUp()
{
	moveSpeed += P_SPEED_UP;
}

#define ARMOR_RIMIT 3

void CPlayer::RenderArmor()
{
	if (hp >= ARMOR_RIMIT)
	{
		hp = ARMOR_RIMIT;
	}
	if (haveArmor == true)
	{
	}

	for (int num = 0; num < hp; num++)
	{
		int armor = armorGraphic[0];
		if (num == 1)
		{
			armor = armorGraphic[1];
		}
		DrawRotaGraph((int)pos.x, (int)pos.y, 3.0 - (0.5*num), armorDrawRad += 0.01f, armor, TRUE);
	}
}

void CPlayer::PlusScore(int plusScore)
{
	score += plusScore;
	if (canShotBirst == true)
	{
		birstMin += plusScore;
	}
}

void CPlayer::ShotBirst()
{
	BirstReadyFlag = true;
}

void CPlayer::RenderLevelUpImg()
{
	levelUpGraphicCnt++;
	//縦4横2で説明画像を描画させる
	for (int num = 0; num < 8; num++)
	{
		int drawX = (int)SCREEN_WIDTH_HALF + 128;
		int drawY = (int)SCREEN_HEIGHT_HALF + 128 + (num * 96);
		if (num > 3)
		{
			drawX += 96;
			drawY = (int)SCREEN_HEIGHT_HALF + 128 + ((num - 4) * 96);
		}
		if (levelUpGraphicCnt < 100)
		{
			DrawRotaGraph(drawX, drawY, 1.0, 0, levelUpGraphic[num * 2], TRUE);
		}
		else if (levelUpGraphicCnt < 200)
		{
			DrawRotaGraph(drawX, drawY, 1.0, 0, levelUpGraphic[num * 2 + 1], TRUE);
		}
		else
		{
			levelUpGraphicCnt = 0;
			DrawRotaGraph(drawX, drawY, 1.0, 0, levelUpGraphic[num * 2], TRUE);
		}
	}
}

void CPlayer::RenderLevelUpFont(int casol)
{
	SetFontSize(32);
	int whichLevelUp = 0;
	int needSkillPoint = 0;
	int guideNum = 0;
	int gudeiFontNum = 0;
	int guideX = 0;
	int animCnt = 0;
	switch (casol)
	{
	case(eAttack):
		switch (attackLevel)
		{
		case(0):
			guideNum = 1;
			guideX = 0;
			gudeiFontNum = 1;
			needSkillPoint = 2;
			break;
		case(1):
			guideNum = 4;
			guideX = 1;
			gudeiFontNum = 4;
			needSkillPoint = 1;
			break;
		case(P_CAN_SHOT_PLUS_LEVEL):
			guideNum = 3;
			guideX = 2;
			gudeiFontNum = 3;
			needSkillPoint = 2;
			break;
		default:
			gudeiFontNum = 10;
			break;
		}

		if (attackLevel < 3)
		{
			RenderGuide(1 * 3, 128 * (0 + 1));
			RenderGuide(4 * 3, 128 * (1 + 1));
			RenderGuide(3 * 3, 128 * (2 + 1));
			animCnt = (GetNowCount() % 6000);
			DrawRotaGraph(1600 - 512, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideGraphic[(guideNum * 3) + (animCnt / 2000)], TRUE);
			DrawRotaGraph(1500, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideFont[gudeiFontNum], TRUE);
		}

		break;
	case(eDiffend):
		whichLevelUp = diffendLevel % 2;
		switch (diffendLevel)
		{
		case(0):
			guideNum = 0;
			guideX = 0;
			gudeiFontNum = 0;
			needSkillPoint = 1;
			break;
		case(1):
			guideNum = 2;
			guideX = 1;
			gudeiFontNum = 2;
			needSkillPoint = 1;
			break;
		default:
			gudeiFontNum = 10;
			break;
		}

		if (diffendLevel < 2)
		{
			RenderGuide(0 * 3, 128 * (0 + 1));
			RenderGuide(2 * 3, 128 * (1 + 1));
			animCnt = (GetNowCount() % 6000);
			DrawRotaGraph(1600 - 512, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideGraphic[(guideNum * 3) + (animCnt / 2000)], TRUE);
			DrawRotaGraph(1500, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideFont[gudeiFontNum], TRUE);
		}

		break;
	case(eZ):
		needSkillPoint = 1;
		whichLevelUp = (zStatus.Status.level + 1) % 3;
		if (zStatus.Status.level == 15)
		{
			gudeiFontNum = 10;
		}
		else
		{
			switch (whichLevelUp)
			{
			case(eSizeUp):
				guideX = 0;
				gudeiFontNum = 5;
				guideNum = 5;
				break;
			case(eIntervalDown):
				guideX = 1;
				gudeiFontNum = 6;
				guideNum = 6;
				break;
			default:
				if (zStatus.Status.level + 1 <= ePlusShot)
				{
					guideX = 2;
					gudeiFontNum = 7;
					guideNum = 7;
				}
				else if (zStatus.Status.level + 1 == eSpeedUp)
				{
					guideX = 4;
					gudeiFontNum = 9;
					guideNum = 9;
				}
				else if (zStatus.Status.level + 1 >= eScoreUp)
				{
					guideX = 3;
					gudeiFontNum = 8;
					guideNum = 8;
				}
				break;
			}
			for (int num = 5; num < 10; num++)
			{
				RenderGuide(num * 3, 128 * (num + 1 - 5));
			}
			animCnt = (GetNowCount() % 6000);
			DrawRotaGraph(1600 - 512, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideGraphic[(guideNum * 3) + (animCnt / 2000)], TRUE);
			DrawRotaGraph(1500, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideFont[gudeiFontNum], TRUE);
		}
		break;
	case(eC):
		needSkillPoint = 1;
		whichLevelUp = (cStatus.Status.level + 1) % 3;
		if (cStatus.Status.level == 15)
		{
			gudeiFontNum = 10;
		}
		else
		{
			switch (whichLevelUp)
			{
			case(eSizeUp):
				guideX = 0;
				gudeiFontNum = 5;
				guideNum = 5;
				break;
			case(eIntervalDown):
				guideX = 1;
				gudeiFontNum = 6;
				guideNum = 6;
				break;
			default:
				if (cStatus.Status.level + 1 <= ePlusShot)
				{
					guideX = 2;
					gudeiFontNum = 3;
					guideNum = 3;
				}
				else if (cStatus.Status.level + 1 == eSpeedUp)
				{
					guideX = 4;
					gudeiFontNum = 9;
					guideNum = 9;
				}
				else if (cStatus.Status.level + 1 >= eScoreUp)
				{
					guideX = 3;
					gudeiFontNum = 8;
					guideNum = 8;
				}
				break;
			}
			for (int num = 5; num < 10; num++)
			{
				RenderGuide(num * 3, 128 * (num + 1 - 5));
			}
			animCnt = (GetNowCount() % 6000);
			DrawRotaGraph(1600 - 512, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideGraphic[(guideNum * 3) + (animCnt / 2000)], TRUE);
			DrawRotaGraph(1500, ((guideX + 1) * 128) + 218, 1.0, 0, levelGuideFont[gudeiFontNum], TRUE);
		}
		break;
	}
	DrawRotaGraph((int)SCREEN_WIDTH_HALF - 256, (SCREEN_HEIGHT_HALF + SCREEN_HEIGHT_HALF / 2) - 128, 1.0, 0, levelGuideFont[gudeiFontNum], TRUE);

	DrawRotaGraph((int)SCREEN_WIDTH_HALF - 288, (SCREEN_HEIGHT_HALF + SCREEN_HEIGHT_HALF / 2) - 64, 1.0, 0, *needSkillPointGraphic, TRUE);
	SetFontSize(64);
	DrawFormatString((int)SCREEN_WIDTH_HALF - 64, (SCREEN_HEIGHT_HALF + SCREEN_HEIGHT_HALF / 2) - 96, GetColor(255, 255, 255), "%d", needSkillPoint);
}

void CPlayer::RenderGuide(int num, int guideX)
{
	int animCnt = (GetNowCount() % 6000);
	DrawRotaGraph(1600 - 512, guideX + 218, 1.0, 0, levelGuideGraphic[num + (animCnt / 2000)], TRUE);
	DrawRotaGraph(1600 - 512, guideX + 218, 1.0, 0, *levelGuideBlack, TRUE);
	DrawRotaGraph(1500, guideX + 218, 1.0, 0, levelGuideFont[num / 3], TRUE);
	DrawRotaGraph(1500, guideX + 218, 1.0, 0, levelGuideFontBlack[num / 3], TRUE);
}