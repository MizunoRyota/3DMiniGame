#include"DxLib.h"
#include"Coin.h"

const float Coin::Scale = 0.01f;		// スケール
const float Coin::CoinNum = 11.0f;		// コインの数

Coin::Coin()
{
    // ３Ｄモデルの読み込み
    Rotation = 0;
    isActive = false;
    CoinHandle[0] = MV1LoadModel("Data/3Dmodel/Obstacle/Coin/Coin.mv1");
    // 3Dモデルのスケール決定
    for (int i = 1; i < CoinNum; i++)
    {
        CoinHandle[i] = MV1DuplicateModel(CoinHandle[0]);
        pos[i] = VGet(1, 0.5, i+20);
        MV1SetScale(CoinHandle[i], VGet(Scale, Scale, Scale));
        MV1SetPosition(CoinHandle[i], pos[i]);
    }
}

Coin::~Coin()
{
    // モデルのアンロード.
    for (int i = 1; i < CoinNum; i++)
    {
        MV1DeleteModel(CoinHandle[i]);
    }
}

void Coin::CoinInitalize()
{
    dir = rand() % 2;
}

void Coin::Update(const VECTOR& buspos, const VECTOR& carpos)
{
    Rotation += 0.1f;
    CoinInitalize();//コインの初期化
    for (int i = 1; i < CoinNum; i++)
    {
        pos[i].z -= 0.5;
        if (pos[i].z <= -20)
        {
            pos[i].z = 70.0f;
            if (buspos.x==carpos.x)
            {
                pos[i].x =buspos.x;
            }
            else
            {
                pos[i].x = carpos.x;;
            }
        }
        MV1SetRotationXYZ(CoinHandle[i], VGet(0.0f, Rotation, 0.0f));
        MV1SetPosition(CoinHandle[i], pos[i]);
    }
}

void Coin::Draw()
{
    for (int i = 1; i < CoinNum; i++)
    {
        MV1DrawModel(CoinHandle[i]);
    }
}