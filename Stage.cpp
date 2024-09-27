#include"DxLib.h"
#include"Stage.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Stage::Speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Stage::Scale = 0.04f;		// スケール

Stage::Stage()
{
	StageHandle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 20.0f);
	MV1SetRotationXYZ(StageHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(StageHandle, pos);
}

Stage::~Stage()
{
	// モデルのアンロード.
	MV1DeleteModel(StageHandle);
}

void Stage::Init()
{
	StageHandle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 20.0f);
	MV1SetRotationXYZ(StageHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	MV1SetScale(StageHandle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
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