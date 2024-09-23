#include "DxLib.h"
#include <vector>
#include "Player.h"
#include "Camera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Camera::Camera()
{
    //���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
    SetCameraNearFar(0.1f, 10000.0f);
    zoom = -3.5;
    Hight = 1.8;
    pos = VGet(0, 0, 0);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Camera::~Camera()
{
    // �����Ȃ�.
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
/// �X�V
/// </summary>
void Camera::Update(const VECTOR playerpos)
{

    // TODO:z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
    // �J�����Ɉʒu�𔽉f.
    pos = VGet(playerpos.x, playerpos.y + Hight, playerpos.z + zoom);
    targtpos = VGet(playerpos.x, playerpos.y + 1, playerpos.z);
    // lerp���g�p���Ď���.
    // lerp(VECTOR a, VECTOR b, float t)��
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
    // TODO:z����ŁA�v���C���[�����苗�����ꂽ��ԂŃv���C���[����Ɍ�������悤�ʒu����
    // �J�����Ɉʒu�𔽉f.
    if (zoom >= -10)
    {
        zoom -= 0.1;
        pos = VGet(playerpos.x, playerpos.y + Hight, playerpos.z + zoom);
    }
    //targtpos = VGet(playerpos.x, playerpos.y + 1, 0);

    SetCameraPositionAndTarget_UpVecY(pos, targtpos);

}