#include"DxLib.h"
#include"NewsPaper.h"
NewsPaper::NewsPaper()
{
	NewsPaperHandle = MV1LoadModel("Data/3Dmodel/Obstacle/NewsPaper/NewsPaper.mv1");
    bool flag = false; // フラグの初期値
    int interval = 1000; // 切り替え間隔（ミリ秒）
    int lastTime = 0; // 最後にフラグを切り替えた時間
	Pos = VGet(0, 0, 0);
}

NewsPaper::~NewsPaper()
{
	MV1DeleteModel(NewsPaperHandle);
}

void NewsPaper::Initialize()
{

}

void NewsPaper::Update()
{
    int currentTime = GetNowCount();
    // 一定時間経過したか確認
    if (currentTime - lastTime >= interval) {
        flag = !flag; // フラグを切り替え
        lastTime = currentTime; // 最後の時刻を更新
    }
    // フラグの状態を表示（コンソール出力）
    if (flag) {
        printf("Flag is TRUE\n");
    }
    else {
        printf("Flag is FALSE\n");
    }
}

void NewsPaper::Draw()
{
    if (flag) {
        printf("Flag is TRUE\n");
    }
    else {
        printf("Flag is FALSE\n");
    }

}