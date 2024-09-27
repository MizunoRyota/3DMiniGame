#include"DxLib.h"
#include"Pallet.h"
#include"HitChecker.h"
#include"Player.h"

Player player;

HitChecker::HitChecker()
{
    Length = PlayerRadius + BusRadius;
    CarLength = PlayerRadius + CarRadius;
    BusRadius = 1.5f;
    PlayerRadius = 1.0f;
    PuddleRadius = 1.3f;
    CarRadius = 1.3f;
    deadgudge = false;
    SpeedDownjudge = false;
}
HitChecker::~HitChecker()
{}

void HitChecker::Init()
{
    deadgudge = false;
    SpeedDownjudge = false;
}

void HitChecker::BusCheck(const VECTOR& player, const VECTOR& obs)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    PlayerCircle = VGet(player.x, player.y + 0.6f, player.z);
    BusCircle[1] = VGet(obs.x, obs.y, obs.z);
    BusCircle[0] = VGet(obs.x, obs.y, obs.z-3.0f);
    BusCircle[2] = VGet(obs.x, obs.y, obs.z+3.0f);
    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    Length = PlayerRadius + BusRadius;

    for (int i = 0; i < BusNum; i++)
    {
        //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
        Distancepos[i] = VSub(player, BusCircle[i]);
        Distance[i] = VSquareSize( Distancepos[i]);
        if (Distance[i] <= (Length))
        {
            DeadJudge();
        }
    }
}

/// <summary>
/// �݂����܂�`�F�b�N
/// </summary>
/// <param name="playerpos"></param>
/// <param name="obs"></param>
/// <param name="player"></param>
void HitChecker::PuddleCheck(const VECTOR& playerpos, const VECTOR& obs, Player* player)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    PuddleCircle[1] = VGet(obs.x - 2.5, obs.y + 0.6, obs.z);
    PuddleCircle[0] = VGet(obs.x + 0.5, obs.y + 0.6, obs.z);

    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    PuddleLength = PlayerRadius + CarRadius;

    for (int i = 0; i < PuddleNum; i++)
    {

        //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
        Puddledistance[i] = VSub(playerpos, PuddleCircle[i]);

        PuddleDistance[i] = VSquareSize(Puddledistance[i]);

        if (PuddleDistance[i] <= (PuddleLength))
        {
            SpeedDownjudge = true;
            player->Set(SpeedDownjudge);
        }
    }
}

bool HitChecker::CarCheck(const VECTOR& player, const VECTOR& obs)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    CarCircle = VGet(obs.x, obs.y+0.6, obs.z);

    //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
    Cardistance = VSub(player, obs);

    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    CarLength = PlayerRadius + CarRadius;

    CarDistance = VSquareSize(Cardistance);

    return CarDistance <= (CarLength);
}


bool HitChecker::DeadJudge()
{
    //�Q�[���I�[�o�[����
    deadgudge = true;

    return deadgudge;
}

void HitChecker::circleDraw()
{
    //for (int i = 0; i < 3; i++)
    //{
    //    if (Distance[i] <= (Length))
    //    {
    //        DrawSphere3D(BusCircle[i], BusRadius, 16, Pallet::AliceBlue.GetHandle(), Pallet::AliceBlue.GetHandle(), false);
    //    }
    //    else
    //    {
    //    DrawSphere3D(BusCircle[i], BusRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    //    }
    //}

    //DrawSphere3D(CarCircle, CarRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    //DrawSphere3D(PlayerCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);

 /*   for (size_t i = 0; i < 2; i++)
    {
        DrawSphere3D(PuddleCircle[i], PuddleRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }*/
}