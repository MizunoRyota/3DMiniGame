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
    //オブジェクトの位置獲得
    PlayerCircle = VGet(player.x, player.y + 0.6f, player.z);
    BusCircle[1] = VGet(obs.x, obs.y, obs.z);
    BusCircle[0] = VGet(obs.x, obs.y, obs.z-3.0f);
    BusCircle[2] = VGet(obs.x, obs.y, obs.z+3.0f);
    //オブジェクトとプレイヤーの半径の合計
    Length = PlayerRadius + BusRadius;

    for (int i = 0; i < BusNum; i++)
    {
        //プレイヤーとオブジェクトの距離の合計を獲得
        Distancepos[i] = VSub(player, BusCircle[i]);
        Distance[i] = VSquareSize( Distancepos[i]);
        if (Distance[i] <= (Length))
        {
            DeadJudge();
        }
    }
}

/// <summary>
/// みずたまりチェック
/// </summary>
/// <param name="playerpos"></param>
/// <param name="obs"></param>
/// <param name="player"></param>
void HitChecker::PuddleCheck(const VECTOR& playerpos, const VECTOR& obs, Player* player)
{
    //オブジェクトの位置獲得
    PuddleCircle[1] = VGet(obs.x - 2.5, obs.y + 0.6, obs.z);
    PuddleCircle[0] = VGet(obs.x + 0.5, obs.y + 0.6, obs.z);

    //オブジェクトとプレイヤーの半径の合計
    PuddleLength = PlayerRadius + CarRadius;

    for (int i = 0; i < PuddleNum; i++)
    {

        //プレイヤーとオブジェクトの距離の合計を獲得
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
    //オブジェクトの位置獲得
    CarCircle = VGet(obs.x, obs.y+0.6, obs.z);

    //プレイヤーとオブジェクトの距離の合計を獲得
    Cardistance = VSub(player, obs);

    //オブジェクトとプレイヤーの半径の合計
    CarLength = PlayerRadius + CarRadius;

    CarDistance = VSquareSize(Cardistance);

    return CarDistance <= (CarLength);
}


bool HitChecker::DeadJudge()
{
    //ゲームオーバー判定
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