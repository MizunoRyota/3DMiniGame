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
    PlayerRadius = 0.5f;
    PuddleRadius = 0.9f;
    CarRadius = 1.3f;
    NewsPaperRadius = 1.5f;
    CoinRadius = 1.0;
    deadgudge = false;
    SpeedDownjudge = false;
}
HitChecker::~HitChecker()
{}
/// <summary>
/// 初期化
/// </summary>
void HitChecker::Init()
{
    deadgudge = false;
    SpeedDownjudge = false;
}

/// <summary>
/// バスの当たり判定
/// </summary>
/// <param name="player"></param>
/// <param name="obs"></param>
void HitChecker::BusCheck(const VECTOR& player, const VECTOR& obs, bool Invicible)
{
    //オブジェクトの位置獲得
    PlayerCircle = VGet(player.x, player.y + 0.6f, player.z);
    BusCircle[1] = VGet(obs.x, obs.y, obs.z);//中心
    BusCircle[0] = VGet(obs.x, obs.y, obs.z-3.0f);//奥
    BusCircle[2] = VGet(obs.x, obs.y, obs.z+3.0f);//手前
    //オブジェクトとプレイヤーの半径の合計の計算
    Length = PlayerRadius + BusRadius;

    for (int i = 0; i < BusNum; i++)
    {
        //プレイヤーのポジションからバスのポジションを減算
        BusDistancepos[i] = VSub(player, BusCircle[i]);
        //プレイヤーとオブジェクトの距離の合計を獲得
        Busdistance[i] = VSquareSize( BusDistancepos[i]);
        if (Busdistance[i] <= (Length))
        {
            //ゲームオーバーフラグの変更
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
void HitChecker::PuddleCheck(const VECTOR& playerpos, const VECTOR& obs, Player* player, bool Invicible)
{
    //オブジェクトの位置獲得
    PuddleCircle[1] = VGet(obs.x , obs.y, obs.z);         //中心
    PuddleCircle[0] = VGet(obs.x + 2, obs.y, obs.z);      //奥
    PuddleCircle[2] = VGet(obs.x + -2, obs.y, obs.z);     //手前 

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

/// <summary>
/// 普通自動車判定
/// </summary>
/// <param name="player"></param>
/// <param name="obs"></param>
/// <returns></returns>
bool HitChecker::CarCheck(const VECTOR& player, const VECTOR& obs, bool Invicible)
{
    //オブジェクトの位置獲得
    CarCircle = VGet(obs.x, obs.y+0.6, obs.z);

    //プレイヤーとオブジェクトの距離の合計を獲得
    Cardistance = VSub(player, obs);

    //オブジェクトとプレイヤーの半径の合計
    CarLength = PlayerRadius + CarRadius;
    //正規化
    CarDistance = VSquareSize(Cardistance);

    return CarDistance <= (CarLength);
}

bool HitChecker::CoinCheck(const VECTOR& player, const VECTOR& obs)
{
    //オブジェクトの位置獲得
    CoinCircle = VGet(obs.x, obs.y + 0.6, obs.z);

    //プレイヤーとオブジェクトの距離の合計を獲得
    Coindistance = VSub(player, obs);

    //オブジェクトとプレイヤーの半径の合計
    CoinLength = PlayerRadius + CoinRadius;
    //正規化
    CoinDistance = VSquareSize(Coindistance);

    return CoinDistance <= (CoinLength);
}

bool HitChecker::NewsPaperCheck(const VECTOR& player, const VECTOR& obs, bool Invicible)
{
    //オブジェクトの位置獲得
    NewsPaperCircle = VGet(obs.x, obs.y + 0.6, obs.z);

    //プレイヤーとオブジェクトの距離の合計を獲得
    NewsPaperdistance = VSub(player, obs);

    //オブジェクトとプレイヤーの半径の合計
    NewsPaperLength = PlayerRadius + NewsPaperRadius;
    //正規化
    NewsPaperDistance = VSquareSize(NewsPaperdistance);

        return NewsPaperDistance <= (NewsPaperLength);
}

bool HitChecker::DeadJudge()
{
    //ゲームオーバー判定
    deadgudge = true;

    return deadgudge;
}

void HitChecker::circleDraw()
{
    for (int i = 0; i < 3; i++)
    {
        if (Busdistance[i] <= (Length))
        {
            DrawSphere3D(BusCircle[i], BusRadius, 16, Pallet::AliceBlue.GetHandle(), Pallet::AliceBlue.GetHandle(), false);
        }
        else
        {
        DrawSphere3D(BusCircle[i], BusRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        }
    }

    DrawSphere3D(CarCircle, CarRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(PlayerCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(CoinCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(NewsPaperCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);

    for (size_t i = 0; i < 3; i++)
    {
        DrawSphere3D(PuddleCircle[i], PuddleRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}