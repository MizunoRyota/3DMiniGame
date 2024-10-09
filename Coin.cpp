#include"DxLib.h"
#include"Coin.h"

const float Coin::Scale = 0.015f;		// スケール
const float Coin::CoinNum = 11.0f;		// コインの数

Coin::Coin()
{
    // ３Ｄモデルの読み込み
    CoinHandle = MV1LoadModel("Data/3Dmodel/Obstacle/Coin/Coin.mv1");
    isActive = false;
    Rotation = 0;
    Hight = 1.5f;
    // 3Dモデルのスケール決定
    MV1SetScale(CoinHandle, VGet(Scale, Scale, Scale));
    pos = VGet(0.0f, 0.0f, 0.0f);
    // ３Dモデルのポジション設定
    MV1SetPosition(CoinHandle, pos);
}

Coin::~Coin()
{
    // モデルのアンロード.
    MV1DeleteModel(CoinHandle);
}

void Coin::CoinInitalize()
{
    pos = VGet(0.0f, 0.0f, 0.0f);
    // ３Dモデルのポジション設定
    MV1SetPosition(CoinHandle, pos);
}

void Coin::Update(const VECTOR& carpos)
{
    Rotation += 0.1f;
    pos = VGet(carpos.x, carpos.y + Hight, carpos.z);
    MV1SetRotationXYZ(CoinHandle, VGet(0.0f, Rotation, 0.0f));
    MV1SetPosition(CoinHandle, pos);
}

void Coin::CoinMove()
{
    pos = VGet(80.0f, 0.0f, 0.0f);
    // ３Dモデルのポジション設定
    MV1SetPosition(CoinHandle, pos);
}

void Coin::Draw()
{
    MV1DrawModel(CoinHandle);
}