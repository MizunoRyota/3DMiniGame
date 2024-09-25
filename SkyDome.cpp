#include"DxLib.h"
#include"skydome.h"

const float Skydome::Scale = 1.5f;		// �X�P�[��

Skydome::Skydome()
{

    // �R�c���f���̓ǂݍ���
    SkydomeHandle = MV1LoadModel("Data/3Dmodel/Skydome/Sunny/Dome_X501.pmx");
    pos = VGet(0, 0, 0);
    // 3D���f���̃X�P�[������
    MV1SetScale(SkydomeHandle, VGet(Scale, Scale, Scale));
    
}

Skydome::~Skydome()
{
    // ���f���̃A�����[�h.
    MV1DeleteModel(SkydomeHandle);
}

void Skydome::SkydomeUpdate()
{
    pos.y -= 0.0003;
    MV1SetRotationXYZ(SkydomeHandle, VGet(0.0f, pos.y, 0.0f));
}

void Skydome::SkydomeTitle()
{
    pos.y -= 0.001;
    MV1SetRotationXYZ(SkydomeHandle, VGet(0.0f, pos.y, 0.0f));
}

void Skydome::SkydomeDraw()
{
    // �R�c���f���̕`��
    MV1DrawModel(SkydomeHandle);
}