#include"DxLib.h"
#include"Puddle.h"

const float Puddle::Scale = 0.001f;		// �X�P�[��

Puddle::Puddle()
{
	PuddleHandle = MV1LoadModel("Data/3Dmodel/Obstacle/puddle/puddle.mv1");
	MV1SetScale(PuddleHandle, VGet(0.002f, Scale, Scale));
	pos = VGet(0.0f,0.0f,0.0f);
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PuddleHandle, pos);
}

Puddle::~Puddle()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(PuddleHandle);
}


void Puddle::Init()
{
	pos = VGet(0.0f, 0.50f, 40.0f);
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Update()
{
	pos.z -= 0.5f;
	if (pos.z <= -60)
	{
		pos.z = 95.0f;
	}
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Draw()
{
	MV1DrawModel(PuddleHandle);
}