#include"DxLib.h"
#include"Stage2.h"

// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Stage2::Speed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);
const float Stage2::Scale = 0.04f;		// スケール

Stage2::Stage2()
{
	Stage2Handle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 0.0f);
	MV1SetRotationXYZ(Stage2Handle, VGet(0.0f, 180.0f * DX_PI_F, 0.0f));
	// 3Dモデルのスケール決定
	MV1SetScale(Stage2Handle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(Stage2Handle, pos);
}

Stage2::~Stage2()
{
	// モデルのアンロード.
	MV1DeleteModel(Stage2Handle);
}

void Stage2::Init()
{
	Stage2Handle = MV1LoadModel("Data/3Dmodel/Stage/Stage.mv1");
	pos = VGet(0.0f, 0.0f, 110.0f);
	MV1SetRotationXYZ(Stage2Handle, VGet(0.0f, 180.0f * DX_PI_F, 0.0f));
	// 3Dモデルのスケール決定
	MV1SetScale(Stage2Handle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(Stage2Handle, pos);
}

void Stage2::Update()
{
	pos.z -= 0.2;
	if (pos.z <= -70)
	{
		pos.z = 110;
	}
	MV1SetPosition(Stage2Handle, pos);
}

void Stage2::GameDraw()
{
	MV1DrawModel(Stage2Handle);
}