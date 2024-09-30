#include"DxLib.h"
#include"Puddle.h"

const float Puddle::Scale = 0.001f;		// スケール

Puddle::Puddle()
{
	PuddleHandle = MV1LoadModel("Data/3Dmodel/Obstacle/puddle/puddle.mv1");
	MV1SetScale(PuddleHandle, VGet(0.002f, Scale, Scale));
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
	pos = VGet(0.0f, 0.50f, 40.0f);
	// ３Dモデルのポジション設定
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Update()
{
	pos.z -= 0.5f;
	if (pos.z <= -60)
	{
		pos.z = 95.0f;
	}
	// ３Dモデルのポジション設定
	MV1SetPosition(PuddleHandle, pos);
}

void Puddle::Draw()
{
	MV1DrawModel(PuddleHandle);
}