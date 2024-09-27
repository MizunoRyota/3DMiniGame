#include"DxLib.h"
#include"Stage.h"

// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Stage::Speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Stage::Scale = 0.04f;		// �X�P�[��

Stage::Stage()
{
	StageHandle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 20.0f);
	MV1SetRotationXYZ(StageHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3D���f���̃X�P�[������
	MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(StageHandle, pos);
}

Stage::~Stage()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(StageHandle);
}

void Stage::Init()
{
	StageHandle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 20.0f);
	MV1SetRotationXYZ(StageHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3D���f���̃X�P�[������
	MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(StageHandle, pos);
}

void Stage::Update()
{
	pos.z -= 0.2;
	if (pos.z<=-80)
	{
		pos.z = 90;
	}
	MV1SetPosition(StageHandle, pos);
}

void Stage::GameDraw()
{
	MV1DrawModel(StageHandle);
}