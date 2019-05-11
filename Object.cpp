//#include"DxLib.h"
#include"Define.h"
#include"Object.h"

//�m�b�N�o�b�N���x�@�Ⴂ�قǑ���
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
        //vPos�𐳋K��
        vPos = VNorm(vPos);
        //vPos��P_SPEED�{����
        vPos.x*=speedX;
		vPos.y*=speedY;
        //���݂̍��W�Ɉړ��ʂ����Z����
        *pos = VAdd(*pos, vPos);
    }
}

void CPlayerEnemyCommon::DamegeProcess(float distance)
{
	float aaaa = distance;
    //��e��ԂȂ�Ă΂��
    if (damegedInvincibleFlag == true)
    {
        //�m�b�N�o�b�N�����������m�b�N�o�b�N����������܂ňړ���������
        damageDistance += distance / NOCKBACK_SPEED;
        //pos.x += damageDistance;
        //���݂̃m�b�N�o�b�N�������󂯎����distance��葽���Ȃ�����damegedInvincibleFlag��|��
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
