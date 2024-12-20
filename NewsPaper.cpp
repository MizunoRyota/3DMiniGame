#include"DxLib.h"
#include"NewsPaper.h"
#include"Pallet.h"
const float NewsPaper::Scale = 0.03f;		// スケール
#define PI    3.1415926535897932384626433832795f
NewsPaper::NewsPaper()
{
	NewsPaperHandle = MV1LoadModel("Data/3Dmodel/Obstacle/NewsPaper/Paper.mv1");
    NewsPaperGraph = LoadGraph("Data/Texture/game/Sinnbun.png");

    Paper = LoadSoundMem("Data/Sound/game/Newspaper.mp3");
    ChangeVolumeSoundMem(255 * 100 / 100, Paper);
    bool flag = false;      // フラグの初期値
    int interval = 800000;  // 切り替え間隔（ミリ秒）
    int lastTime = 0;       // 最後にフラグを切り替えた時間
	Pos = VGet(0, 3, 0);
    ShadowRad = 0.6f;
    RightDir = false;
    LeftDir = true;
    CrushTime = 0;
    Rotation = 0;
    // 3Dモデルのスケール決定
    MV1SetScale(NewsPaperHandle, VGet(Scale, Scale, Scale));
    // ３Dモデルのポジション設定
    MV1SetPosition(NewsPaperHandle, Pos);
}

NewsPaper::~NewsPaper()
{
	MV1DeleteModel(NewsPaperHandle);
}

void NewsPaper::Initialize()
{
    // ３Dモデルのポジション設定
    Pos = VGet(0.0f, 1.5f, 80.0f);
    MV1SetRotationXYZ(NewsPaperHandle, VGet(0.0f,0.0f,0.0f ));
    MV1SetPosition(NewsPaperHandle, Pos);
}

void NewsPaper::UpdateShadow()
{
    Toppos = VGet(Pos.x, -1, Pos.z);
    Bottompos = VGet(Pos.x, Pos.y-1.15f, Pos.z);
}
void NewsPaper::PlayCrushNewsPaper()
{
    PlaySoundMem(Paper, DX_PLAYTYPE_BACK, true);            //紙にあたる

}


void NewsPaper::Update()
{
    LateralMove();
    UpdateShadow();
    if (CrushJudge==true)
    {
        CrashPaper();
    }
    else
    {
        Pos.z -= 0.5f;
        MV1SetRotationXYZ(NewsPaperHandle, VGet(90.0f * DX_PI_F / 180.0f, 0.0f, Rotation));
    }
    Rotation += 0.1f;
    if (Pos.z <= -100)
    {
        Pos.z = 80;
    }
    int currentTime = GetNowCount();
    if (Pos.x > 3)
    {
        Pos.x -= 0.3;
        LeftDir = true;
        RightDir = false;
    }
    else if (Pos.x < -3)
    {
        Pos.x -= -0.3;
        LeftDir = false;
        RightDir = true;
    }
    // ３Dモデルのポジション設定
    MV1SetPosition(NewsPaperHandle, Pos);
}
void NewsPaper::CrashPaper()
{
    if (CrushJudge == true)
    {

        Pos = VGet(0, 1, -30);

        // 初回の呼び出し時に開始時刻を設定
        if (CrushTime == 0)
        {
            PlayCrushNewsPaper();
            CrushTime = GetNowCount();  // ミリ秒単位で現在時刻を取得
        }
        // 経過時間が3000ミリ秒(3秒)以上経過したらフラグを切り替える
        if (GetNowCount() - CrushTime >= 1000)
        {
            CrushJudge = false;
            CrushTime = 0;
        }
    }
    // ３Dモデルのポジション設定
    MV1SetPosition(NewsPaperHandle, Pos);
}

void NewsPaper::ChangeCrush()
{
    CrushJudge = true;
}

void NewsPaper::LateralMove ()
{
    //左の上限に入ると反対に移動
    if (LeftDir==true)
    {
        Pos.x -= 0.05;
    }

    //右の上限に入ると反対に移動
    else if (RightDir==true)
    {
        Pos.x += 0.05f;
    }    
    // ３Dモデルのポジション設定
    MV1SetPosition(NewsPaperHandle, Pos);
}

void NewsPaper::CrushInvicible()
{
    Pos.y += 0.05;
}

void NewsPaper::Draw()
{
    if (CrushJudge==true)
    {
        // 読みこんだグラフィックを回転描画
        DrawRotaGraph(800, 220, 1.2f, PI / 3, NewsPaperGraph, TRUE);
    }
    MV1DrawModel(NewsPaperHandle);
    DrawCone3D(Toppos, Bottompos, ShadowRad, 8, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), TRUE);
}