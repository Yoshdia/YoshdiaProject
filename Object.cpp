//#include"DxLib.h"
#include"Define.h"
#include"Object.h"

//ノックバック速度　低いほど早い
#define NOCKBACK_SPEED 10

bool CObject::ComeOutScreen(VECTOR & pPos, double ScreenOut)
{
    if (pPos.y < 0 - ScreenOut)
    {
        return true;
    }
    if (pPos.x > SCREEN_WIDTH + ScreenOut)
    {
        return true;
    }
    if (pPos.y > SCREEN_HEIGHT + ScreenOut)
    {
        return true;
    }
    if (pPos.x < 0 - ScreenOut)
    {
        return true;
    }
    return false;
}

void CObject::normPos(VECTOR *pos, VECTOR vPos, float speedX, float speedY)
{
    if (VSquareSize(vPos) != 0)
    {
        //vPosを正規化
        vPos = VNorm(vPos);
        //vPosをP_SPEED倍する
        vPos.x*=speedX;
		vPos.y*=speedY;
        //現在の座標に移動量を加算する
        *pos = VAdd(*pos, vPos);
    }
}

void CPlayerEnemyCommon::DamegeProcess(float distance)
{
	float aaaa = distance;
    //被弾状態なら呼ばれる
    if (damegedInvincibleFlag == true)
    {
        //ノックバック距離が総合ノックバック距離を上回るまで移動し続ける
        damageDistance += distance / NOCKBACK_SPEED;
        //pos.x += damageDistance;
        //現在のノックバック距離が受け取ったdistanceより多くなったらdamegedInvincibleFlagを倒す
        if ((damageDistance*damageDistance) >= (distance*distance))
        {
            damegedInvincibleFlag = false;
        }
    }
}

void CPlayerEnemyCommon::HitAction()
{
    damageDistance = 0;
    damegedInvincibleFlag = true;
}

void CPlayerEnemyCommon::HitDamage(int damege)
{
    hp -= damege;
}
