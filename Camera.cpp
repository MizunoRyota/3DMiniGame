#include "DxLib.h"
#include <vector>
#include "Player.h"
#include "Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
    //奥行0.1～1000までをカメラの描画範囲とする
    SetCameraNearFar(0.1f, 10000.0f);
    zoom = -3.5;
    Hight = 1.8;
    pos = VGet(0, 0, 0);
}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
    // 処理なし.
}

void Camera::Init()
{
    pos = VGet(-1, 0, 0);
    Hight = 1.0;
    zoom = -1.5;
}
/// @brief 
/// @param playerpos 
void Camera::GameTitle(const VECTOR& playerpos)
{

    pos = VGet(pos.x, playerpos.y + Hight, playerpos.z + zoom);
    targtpos = VGet(playerpos.x, playerpos.y + 1, playerpos.z);
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}
/// @brief 
/// @param playerpos 
void Camera::ReadyUpdate(const VECTOR& playerpos)
{

    if (zoom>=-3.5)
    {
        zoom-=0.04;
    }
    if (Hight <= 1.7)
    {
        Hight += 0.04;
    }

    pos = VGet(playerpos.x, playerpos.y + Hight, playerpos.z + zoom);
    targtpos = VGet(playerpos.x, playerpos.y + 1, playerpos.z);

    SetCameraPositionAndTarget_UpVecY(pos, targtpos);

}

/// <summary>
/// 更新
/// </summary>
void Camera::Update(const VECTOR playerpos)
{

    // TODO:z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
    // カメラに位置を反映.
    pos = VGet(playerpos.x, playerpos.y + Hight, playerpos.z + zoom);
    targtpos = VGet(playerpos.x, playerpos.y + 1, playerpos.z);
    // lerpを使用して実装.
    // lerp(VECTOR a, VECTOR b, float t)は
    // answer = a + ((b-a) * t)
    // answer = start + ((end - start) * t)
    //VECTOR   targetPos = VGet(playerpos.x, playerpos.y+0.1, playerpos.z -5);     // b 
    //VECTOR   aimPos = VSub(targetPos, pos);              // (b-a)
    //VECTOR   scalsepos = VScale(aimPos, 0.5);         // ((b-a) * t)
    //pos = VAdd(pos, scalsepos);         // a + ((b-a) * t)
    SetCameraPositionAndTarget_UpVecY(pos, targtpos);
}

void Camera::GameEnd(const VECTOR playerpos)
{
    // TODO:z軸上で、プレイヤーから一定距離離れた状態でプレイヤーを常に見続けるよう位置調整
    // カメラに位置を反映.
    if (zoom >= -10)
    {
        zoom -= 0.1;
        pos = VGet(playerpos.x, playerpos.y + Hight, playerpos.z + zoom);
    }
    //targtpos = VGet(playerpos.x, playerpos.y + 1, 0);

    SetCameraPositionAndTarget_UpVecY(pos, targtpos);

}