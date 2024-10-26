#include"DxLib.h"
#include"Bgm.h"

BGM::BGM()
{
    //ゲームサウンド
    Game=LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 35 / 100, Game);
    Title = LoadSoundMem("Data/Sound/bgm/Title.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, Title);    
    GameEnd = LoadSoundMem("Data/Sound/bgm/Crush.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, GameEnd);
    GameOver = LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, GameOver);
    //効果音
    CountDown1 = LoadSoundMem("Data/Sound/bgm/Countdown1.mp3");
    ChangeVolumeSoundMem(255 * 80 / 100, CountDown1);
    CountDown2 = LoadSoundMem("Data/Sound/bgm/CountDown2.mp3");
    ChangeVolumeSoundMem(255 * 80 / 100, CountDown2);
}

BGM::~BGM()
{
    // 音をすべて削除します
    InitSoundMem();
}

void BGM::PlayGameSound()
{
    PlaySoundMem(Game, DX_PLAYTYPE_LOOP, false);            //ゲーム中
}
void BGM::StopGameSound()
{
    StopSoundMem(Game);
}
void BGM::PlayGameTitle()
{
    PlaySoundMem(Title, DX_PLAYTYPE_LOOP, false);           //タイトル
}
void BGM::StopGameTitle()
{
    StopSoundMem(Title);
}

void BGM::PlayGameEnd()
{
    PlaySoundMem(GameEnd, DX_PLAYTYPE_BACK, true);         //ゲーム終わり
}
void BGM::StopGameEnd()
{
    StopSoundMem(GameEnd);
}
void BGM::PlayGameOver()
{
    PlaySoundMem(GameOver, DX_PLAYTYPE_LOOP, false);        //ゲームオーバー
}
void BGM::StopGameOver()
{
    StopSoundMem(GameOver);
}
void BGM::PlayCountDown1()
{
    PlaySoundMem(CountDown1, DX_PLAYTYPE_BACK, true);        //CountDown1
}
void BGM::StopCountDown1()
{
    StopSoundMem(CountDown1);
}
void BGM::PlayCountDown2()
{
    PlaySoundMem(CountDown2, DX_PLAYTYPE_BACK, true);        //CountDown2
}
    void BGM::StopCountDown2()
{
    StopSoundMem(CountDown2);
}