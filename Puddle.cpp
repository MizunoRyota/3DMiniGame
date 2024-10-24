#include"DxLib.h"
#include"Puddle.h"

const float Puddle::Scale = 0.05f;		// スケール

Puddle::Puddle()
{
	PuddleHandle = MV1LoadModel("Data/3Dmodel/Obstacle/puddle/Tar.mv1");
	MV1SetScale(PuddleHandle, VGet(Scale, 0.01, Scale));
	pos = VGet(0.0f,0.0f,0.0f);
	// ３Dモデルのポジション設定
	MV1SetPosition(PuddleHandle, pos);
}

Puddle::~Puddle()
{
	// モデルのアンロード.
	MV1DeleteModel(PuddleHandle);
}

void Puddle::Init()
{
	// ３Dモデルのポジション設定
	pos = VGet(0.5f, 0.50f, 80.0f);
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Update( float ObstacleSpeed,bool ObstaclePattern)
{
	//ポジションの更新
	pos.z -= ObstacleSpeed;
	//ポジションの初期化
	if (pos.z <= -60)
	{
		pos.z = 90.0f;
	}
	// ３Dモデルのポジション設定
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Draw()
{
	MV1DrawModel(PuddleHandle);
}