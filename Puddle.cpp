#include"DxLib.h"
#include"Puddle.h"

const float Puddle::Scale = 0.05f;		// �X�P�[��

Puddle::Puddle()
{
	PuddleHandle = MV1LoadModel("Data/3Dmodel/Obstacle/puddle/Tar.mv1");
	MV1SetScale(PuddleHandle, VGet(Scale, 0.01, Scale));
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
	// �RD���f���̃|�W�V�����ݒ�
	pos = VGet(0.5f, 0.50f, 80.0f);
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Update( float ObstacleSpeed,bool ObstaclePattern)
{
	//�|�W�V�����̍X�V
	pos.z -= ObstacleSpeed;
	//�|�W�V�����̏�����
	if (pos.z <= -60)
	{
		pos.z = 90.0f;
	}
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Draw()
{
	MV1DrawModel(PuddleHandle);
}