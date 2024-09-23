#include"DxLib.h"
#include"Pallet.h"
#include"HitChecker.h"
#include"Player.h"

Player player;

HitChecker::HitChecker()
{
    Length = PlayerRadius + ObstacleRadius;
    CarLength = PlayerRadius + CarRadius;
    ObstacleRadius = 1.50f;
    PlayerRadius = 1.0f;
    PuddleRadius = 1.3f;
    CarRadius = 1.3f;
    deadgudge = false;
}
HitChecker::~HitChecker()
{}

void HitChecker::Init()
{
    deadgudge = false;
}

void HitChecker::BusCheck(const VECTOR& player, const VECTOR& obs)
{
    PlayerCircle = VGet(player.x, player.y + 0.6f, player.z);
    ObstacleCircle[1] = VGet(obs.x, obs.y, obs.z);
    ObstacleCircle[0] = VGet(obs.x, obs.y, obs.z-3.0f);
    ObstacleCircle[2] = VGet(obs.x, obs.y, obs.z+3.0f);
    Length = PlayerRadius + ObstacleRadius;
    for (int i = 0; i < BusNum; i++)
    {
        Distancepos[i] = VSub(player, ObstacleCircle[i]);
        Distance[i] = VSquareSize( Distancepos[i]);
        if (Distance[i] <= (Length))
        {
            DeadJudge();
        }
    }
}

void HitChecker::PuddleCheck(const VECTOR& playerpos, const VECTOR& obs)
{
    PuddleCircle[1] = VGet(obs.x-2.5, obs.y + 0.6, obs.z);
    PuddleCircle[0] = VGet(obs.x+0.5, obs.y + 0.6, obs.z);
    PuddleLength = PlayerRadius + CarRadius;

    for (int i = 0; i < PuddleNum; i++)
    {
        Puddledistance[i] = VSub(playerpos, PuddleCircle[i]);

        PuddleDistance[i] = VSquareSize(Puddledistance[i]);

        if (PuddleDistance[i] <= (PuddleLength))
        {
            Player::ChangeSpeedFlag();
        } 
    }
}

bool HitChecker::CarCheck(const VECTOR& player, const VECTOR& obs)
{
    CarCircle = VGet(obs.x, obs.y+0.6, obs.z);

    Cardistance = VSub(player, obs);

    CarLength = PlayerRadius + CarRadius;

    CarDistance = VSquareSize(Cardistance);

    return CarDistance <= (CarLength);
}


bool HitChecker::DeadJudge()
{
    deadgudge = true;

    return deadgudge;
}

void HitChecker::circleDraw()
{
    //for (int i = 0; i < 3; i++)
    //{
    //    if (Distance[i] <= (Length))
    //    {
    //        DrawSphere3D(ObstacleCircle[i], ObstacleRadius, 16, Pallet::AliceBlue.GetHandle(), Pallet::AliceBlue.GetHandle(), false);
    //    }
    //    else
    //    {
    //    DrawSphere3D(ObstacleCircle[i], ObstacleRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    //    }
    //}

    //DrawSphere3D(CarCircle, CarRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    //DrawSphere3D(PlayerCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);

    for (size_t i = 0; i < 2; i++)
    {
        DrawSphere3D(PuddleCircle[i], PuddleRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}