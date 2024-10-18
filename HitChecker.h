#pragma once
#include"Player.h"
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    void BusCheck(const VECTOR& player, const VECTOR& obs,bool Invicible);              //バスとプレイヤーの当たり判定
    bool CarCheck(const VECTOR& player, const VECTOR& obs, bool Invicible);             //
    bool CoinCheck(const VECTOR& player, const VECTOR& obs);                            //
    bool NewsPaperCheck(const VECTOR& player, const VECTOR& obs, bool Invicible);       //
    void PuddleCheck(const VECTOR& playerpos, const VECTOR& obs,Player*player, bool Invicible);//
    bool DeadJudge();                                            //ゲームオーバーのなったかを返す
    void circleDraw();                                           //当たり判定の球描画
    const bool & GetDead() const { return deadgudge; }           //ゲームオーバーの判定を返す
    const bool& GetSpeed() const { return SpeedDownjudge; }      //スピードダウンの判定を返す
private:
    //プレイヤー
    VECTOR PlayerCircle;        //プレイヤーの当たり判定のポジション
    float PlayerRadius;         //プレイヤーの当たり判定の半径
    bool deadgudge;             //プレイヤーが接触した時の判定
    bool SpeedDownjudge;        //プレイヤーのスピードダウン判定
    //バス
    VECTOR BusCircle[3];        //バスの当たり判定のポジション
    VECTOR BusDistancepos[3];   //バスの当たり判定それぞれのポジション
    float Busdistance[3];       //バスとプレイヤーとの距離の減算を保持する
    float BusRadius;            //バスの当たり判定の半径
    const int BusNum = 3;       //バスの当たり判定の数
    float Length;               //バスとプレイヤーとの半径同士の合計
    //車
    VECTOR CarCircle;           //普通自動車の当たり判定のポジション
    VECTOR Cardistance;         //普通自動車とプレイヤーとの距離の減算の結果を保持する
    float CarLength;            //普通自動車とプレイヤーとの半径同士の合計
    float CarRadius;            //普通自動車の当たり判定の半径
    float CarDistance;          //普通自動車とプレイヤーの距離
    //コイン
    VECTOR CoinCircle;          //コインの当たり判定のポジション
    VECTOR Coindistance;        //コインとプレイヤーとの距離の減算の結果を保持する
    float CoinDistance;         //コインとプレイヤーとの距離
    float CoinLength;           //コインとプレイヤーとの半径同士の合計
    float CoinRadius;           //コインの当たり判定の半径
    //新聞紙
    VECTOR NewsPaperCircle;     //新聞紙の当たり判定のポジション
    VECTOR NewsPaperdistance;   //新聞紙とプレイヤーとの距離の減算の結果を保持する
    float NewsPaperDistance;    //新聞紙とプレイヤーとの距離
    float NewsPaperLength;      //新聞紙とプレイヤーの当たり判定の合計
    float NewsPaperRadius;      //新聞紙の当たり判定の半径
    //みずたまり
    VECTOR PuddleCircle[3];     //水たまりのポジション
    VECTOR Puddledistance[3];   //水たまりとプレイヤーの距離の減算の結果を保持する
    const int PuddleNum = 3;    //みずたまりの当たり判定の数
    float PuddleLength;         //みずたまりとプレイヤーとの半径同士の合計
    float PuddleRadius;         //みずたまりのあたる判定の半径
    float PuddleDistance[3];    //みずたまりとプレイヤーの距離
};