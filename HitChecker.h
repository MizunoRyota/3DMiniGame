#pragma once

class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    void BusCheck(const VECTOR& player, const VECTOR& obs);
    bool CarCheck(const VECTOR& player, const VECTOR& obs);
    void PuddleCheck(const VECTOR& player, const VECTOR& obs);
    bool DeadJudge();
    void circleDraw();
    const bool & GetDead() const { return deadgudge; }
    const bool& GetSpeed() const { return SpeedDownjudge; }

private:
    VECTOR PlayerCircle;        //プレイヤーの当たり判定のポジション
    VECTOR Distancepos[3];      //バスの当たり判定それぞれのポジション
    VECTOR ObstacleCircle[3];   //バスとプレイヤーとの距離の減算を保持する
    VECTOR Cardistance;         //普通自動車とプレイヤーとの距離の減算の保持する
    VECTOR CarCircle;           //普通自動車の当たり判定のポジション
    VECTOR Puddledistance[2];   //
    VECTOR PuddleCircle[2];     //
    float Distance[3];          //
    const int BusNum = 3;       //バスの当たり判定の数
    const int PuddleNum = 2;    //みずたまりの当たり判定の数
    bool deadgudge;             //プレイヤーが接触した時の判定
    bool SpeedDownjudge;        //プレイヤーのスピードダウン判定
    float CarLength;            //普通自動車とプレイヤーとの半径同士の合計
    float Length;               //バスとプレイヤーとの半径同士の合計
    float PuddleLength;         //
    float ObstacleRadius;       //バスの当たり判定の半径
    float PlayerRadius;         //プレイヤーの当たり判定の半径
    float PuddleRadius;         //みずたまりのあたる判定の半径
    float CarRadius;            //普通自動車の当たり判定の半径
    float CarDistance;          //普通自動車とプレイヤーの距離
    float PuddleDistance[2];       //みずたまりとプレイヤーの距離
};