#include"DxLib.h"
#include"Car.h"

const float Car::Speed = static_cast<float>(10000.0 / 30.0 / 30.0 / 30.0);
const float Car::Scale = 0.037f;		// スケール]

Car::Car()
{
	CarHandle = MV1LoadModel("Data/3Dmodel/Obstacle/Car/Car.mv1");
	pos = VGet(1.5f, 0.5f, 40.0f);
	MV1SetRotationXYZ(CarHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	MV1SetScale(CarHandle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(CarHandle, pos);
}

Car::~Car()
{
	// モデルのアンロード.
	MV1DeleteModel(CarHandle);
}

void Car::Init()
{
	pos = VGet(1.5f, 0.5f, 40.0f);
	MV1SetRotationXYZ(CarHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	MV1SetScale(CarHandle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(CarHandle, pos);
}

void Car::CarTitle()
{
	pos = VGet(2.3f, 0.5f, -7.0f);
	// ３Dモデルのポジション設定
	MV1SetPosition(CarHandle, pos);
}

void Car::Update()
{
	pos.z -= 0.5f;
	if (pos.z <= -20)
	{
		pos.z = 50.0f;
		dir = rand() % 3;
		if (dir == 0)
		{
			pos.x = -1.8;
		}
		else if (dir == 1)
		{
			pos.x = 1.8;
		}
		else
		{
			pos.x = 0;
		}
	}
	// ３Dモデルのポジション設定
	MV1SetPosition(CarHandle, pos);
}

void Car::GameDraw()
{
	MV1DrawModel(CarHandle);
}
