#include"DxLib.h"
#include"Car.h"

const float Car::Scale = 0.037f;		// スケール

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
	pos = VGet(2.0f, 0.5f, -40.0f);
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

void Car::Update(int PlacePattern, float ObstacleSpeed)
{
	//移動
	pos.z -= ObstacleSpeed;
	//障害物のパターン決定
	if (pos.z <= -20)
	{
		pos.z = 50.0f;
		if (ObstacleSpeed<0.8)
		{
			if (PlacePattern == 0|| PlacePattern == 1|| PlacePattern == 2)
			{
				pos.x = 2.0;
			}
			else if (PlacePattern == 3 || PlacePattern == 4 || PlacePattern == 5)
			{
				pos.x = -2.0;
			}
			else if (PlacePattern == 6 )
			{
				pos.x = 0;
			}
			else if (PlacePattern == 7)
			{
				pos.x = 0;
			}

		}
		else if(ObstacleSpeed >= 0.8)
		{
			if (PlacePattern == 0)
			{
				pos.x = 0;
			}
			else if (PlacePattern == 1)
			{
				pos.x = -2.0;
			}
			else if (PlacePattern == 2)
			{
				pos.x = 2.0;
			}
			else if (PlacePattern == 3 || PlacePattern == 4 )
			{
				pos.x = 2.0;
			}
			else if (PlacePattern == 5 || PlacePattern == 6)
			{
				pos.x = 2.0;
			}
			else if (PlacePattern == 7)
			{
				pos.x = -2.0;
			}
		}

	}
	// ３Dモデルのポジション設定
	MV1SetPosition(CarHandle, pos);
}

void Car::GameDraw()
{
	MV1DrawModel(CarHandle);
}
