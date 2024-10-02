#pragma once
#include"Player.h"
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    void BusCheck(const VECTOR& player, const VECTOR& obs);
    bool CarCheck(const VECTOR& player, const VECTOR& obs);
    bool CoinCheck(const VECTOR& player, const VECTOR& obs);
    bool NewsPaperCheck(const VECTOR& player, const VECTOR& obs);
    void PuddleCheck(const VECTOR& playerpos, const VECTOR& obs,Player*player);
    bool DeadJudge();
    void circleDraw();
    const bool & GetDead() const { return deadgudge; }
    const bool& GetSpeed() const { return SpeedDownjudge; }
private:
    VECTOR PlayerCircle;        //プレイヤーの当たり判定のポジション
    VECTOR BusDistancepos[3];   //バスの当たり判定それぞれのポジション
    VECTOR BusCircle[3];        //バスの当たり判定のポジション
    VECTOR Cardistance;         //普通自動車とプレイヤーとの距離の減算の結果を保持する
    VECTOR CarCircle;           //普通自動車の当たり判定のポジション
    VECTOR Puddledistance[3];   //水たまりとプレイヤーの距離の減算の結果を保持する
    VECTOR PuddleCircle[3];     //水たまりのポジション
    //コイン
    VECTOR CoinCircle;          //コインの当たり判定のポジション
    VECTOR Coindistance;
    float CoinDistance;
    float CoinLength;
    float CoinRadius;    
    //新聞紙
    VECTOR NewsPaperCircle;          //新聞紙の当たり判定のポジション
    VECTOR NewsPaperdistance;
    float NewsPaperDistance;
    float NewsPaperLength;
    float NewsPaperRadius;
    float Busdistance[3];       //バスとプレイヤーとの距離の減算を保持する
    const int BusNum = 3;       //バスの当たり判定の数
    const int PuddleNum = 3;    //みずたまりの当たり判定の数
    bool deadgudge;             //プレイヤーが接触した時の判定
    bool SpeedDownjudge;        //プレイヤーのスピードダウン判定
    float CarLength;            //普通自動車とプレイヤーとの半径同士の合計
    float Length;               //バスとプレイヤーとの半径同士の合計
    float PuddleLength;         //みずたまりとプレイヤーとの半径同士の合計
    float BusRadius;            //バスの当たり判定の半径
    float PlayerRadius;         //プレイヤーの当たり判定の半径
    float PuddleRadius;         //みずたまりのあたる判定の半径
    float CarRadius;            //普通自動車の当たり判定の半径
    float CarDistance;          //普通自動車とプレイヤーの距離
    float PuddleDistance[3];    //みずたまりとプレイヤーの距離
};