#include"DxLib.h"
#include"Stage2.h"

// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Stage2::Speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Stage2::Scale = 0.04f;		// �X�P�[��

Stage2::Stage2()
{
	Stage2Handle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 0.0f);
	MV1SetRotationXYZ(Stage2Handle, VGet(0.0f, 180.0f * DX_PI_F, 0.0f));
	// 3D���f���̃X�P�[������
	MV1SetScale(Stage2Handle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(Stage2Handle, pos);
}

Stage2::~Stage2()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(Stage2Handle);
}

void Stage2::Init()
{
	Stage2Handle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 110.0f);
	MV1SetRotationXYZ(Stage2Handle, VGet(0.0f, 180.0f * DX_PI_F, 0.0f));
	// 3D���f���̃X�P�[������
	MV1SetScale(Stage2Handle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(Stage2Handle, pos);
}

void Stage2::Update()
{
	pos.z -= 0.2;
	if (pos.z <= -70)
	{
		pos.z = 110;
	}
	MV1SetPosition(Stage2Handle, pos);
}

void Stage2::GameDraw()
{
	MV1DrawModel(Stage2Handle);
}