#include"DxLib.h"
#include"Stage.h"

// 静的定数
const float Stage::Scale = 0.04f;		// スケール
const int Stage::StageNum3 = 3;
Stage::Stage()
{
	StageHandle[0] = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos[0] = VGet(0.0f, 0.0f, 20.0f);
	MV1SetRotationXYZ(StageHandle[0], VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	for (int i = 1; i < StageNum3; i++)
	{
		StageHandle[i] = MV1DuplicateModel(StageHandle[0]);
		pos[i] = VGet(1, 0.5, i + 20);
		MV1SetScale(StageHandle[i], VGet(Scale, Scale, Scale));
		MV1SetPosition(StageHandle[i], pos[i]);
	}
}

Stage::~Stage()
{
	// モデルのアンロード.
	for (int i = 0; i < StageNum3; i++)
	{
		MV1DeleteModel(StageHandle[i]);
	}
}

void Stage::Init()
{
	pos[0] = VGet(0.0f, 0.0f, 0.0f);
	pos[1] = VGet(0.0f, 0.0f, 90.0f);
	pos[2] = VGet(0.0f, 0.0f, -90.0f);
	MV1SetRotationXYZ(StageHandle[1], VGet(0.0f, 180.0f * DX_PI_F, 0.0f));
	// 3Dモデルのスケール決定
	for (int i = 0; i < StageNum3; i++)
	{
		MV1SetScale(StageHandle[i], VGet(Scale, Scale, Scale));
		// ３Dモデルのポジション設定
		MV1SetPosition(StageHandle[i], pos[i]);
	}
}

void Stage::Update()
{
	for (int i = 0; i < StageNum3; i++)
	{
		pos[i].z -= 0.2;
		if (pos[i].z <= -90)
		{
			pos[i].z = 90;
		}
		MV1SetPosition(StageHandle[i], pos[i]);
	}
}

void Stage::GameDraw()
{
	for (int i = 0; i < StageNum3; i++)
	{
		MV1DrawModel(StageHandle[i]);
	}

}