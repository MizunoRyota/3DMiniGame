#include"DxLib.h"
#include"Bus.h"

const float Bus::Scale = 0.008f;	// �X�P�[��
const int BusNum = 2;				//�o�X�̐�
Bus::Bus()
{
	BusHandle[0] = MV1LoadModel("Data/3Dmodel/Obstacle/Bus.mv1");
	BusHandle[1] = MV1DuplicateModel(BusHandle[0]);
	for (int i = 0; i < BusNum; i++)
	{
		pos[i] = VGet(0, 0, 0);
		MV1SetScale(BusHandle[i], VGet(Scale, Scale, Scale));
		MV1SetPosition(BusHandle[i], pos[i]);
	}
}

Bus::~Bus()
{
	// ���f���̃A�����[�h.
	for (int i = 0; i < BusNum; i++)
	{
		MV1DeleteModel(BusHandle[i]);
	}
}

void Bus::Init()
{
	for (int i = 0; i < BusNum; i++)
	{
		pos[i] = VGet(0.0f, 1.2f, -40.0f);
		MV1SetRotationXYZ(BusHandle[i], VGet(0.0f, 4.7f, 0.0f));
		// 3D���f���̃X�P�[������
		MV1SetScale(BusHandle[i], VGet(Scale, Scale, Scale));
		// �RD���f���̃|�W�V�����ݒ�
		MV1SetPosition(BusHandle[i], pos[i]);
	}
}

void Bus::BlowAway()
{
	//��]�l�̍X�V
	Rotation += 0.1;
	//��Q���̉�]
	for (int i = 0; i < BusNum; i++)
	{
		MV1SetRotationXYZ(BusHandle[i], VGet(0.0f, Rotation, Rotation));
	}

}

void Bus::Update(int PlacePattern,float ObstacleSpeed)
{
	//�ړ�
	pos[0].z-=ObstacleSpeed;
	pos[1].z -= ObstacleSpeed;
	//��Q���p�^�[���̍X�V
	if (pos[0].z<=-20&&pos[1].z<=-20)
	{
		pos[0].z = 50.0f;
		pos[1].z = 50.0f;

		if ( PlacePattern==0)
		{
			pos[0].x = -2.0;
			pos[1].x = 2.0;
		}
		else if( PlacePattern==1)
		{
			pos[0].x = 2.0;
			pos[1].x = 0;
		}
		else if(PlacePattern == 2)
		{
			pos[0].x = -2.0;
			pos[1].x = 0;
		}
		else
		{
			pos[0].x = 0;
			pos[1].x = 0;
		}
	}
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(BusHandle[0], pos[0]);
	MV1SetPosition(BusHandle[1], pos[1]);
}

void Bus::GameDraw()
{
	//�`��
	MV1DrawModel(BusHandle[0]);
	MV1DrawModel(BusHandle[1]);
}
