#include"DxLib.h"
#include"Bus.h"

const float Bus::Speed = static_cast<float>(10000.0 / 30.0 / 30.0 / 30.0);
const float Bus::Scale = 0.008f;		// �X�P�[��

Bus::Bus()
{
	BusHandle = MV1LoadModel("Data/3Dmodel/Obstacle/Bus.mv1");
	pos = VGet(1.5f, 1.4f, 40.0f);
	MV1SetRotationXYZ(BusHandle, VGet(0.0f, 4.7f, 0.0f));
	// 3D���f���̃X�P�[������
	MV1SetScale(BusHandle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(BusHandle, pos);
}

Bus::~Bus()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(BusHandle);
}

void Bus::Init()
{
	pos = VGet(1.5f, 1.4f, 40.0f);
	MV1SetRotationXYZ(BusHandle, VGet(0.0f, 4.7f, 0.0f));
	// 3D���f���̃X�P�[������
	MV1SetScale(BusHandle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(BusHandle, pos);
}

void Bus::Update()
{
	isActive = true;
	pos.z-=0.5f;
	if (pos.z<=-20)
	{
		pos.z = 70.0f;
		dir = rand() % 3;
		if (dir==0)
		{
			pos.x = -1.8;
		}
		else if(dir==1)
		{
			pos.x = 1.8;
		}
		else
		{
			pos.x = 0;
		}
	}
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(BusHandle, pos);
}

void Bus::GameDraw()
{
	MV1DrawModel(BusHandle);
}
