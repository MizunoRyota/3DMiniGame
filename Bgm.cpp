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
    GameOver = LoadSoundMem("Data/Sound/bgm/GameOver.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, GameOver);

}

BGM::~BGM()
{
    // 音をすべて削除します
    InitSoundMem();
}

void BGM::PlayGameSound()
{
    PlaySoundMem(Game, DX_PLAYTYPE_LOOP, true);            //ゲーム中
}
void BGM::StopGameSound()
{
    StopSoundMem(Game);
}
void BGM::PlayGameTitle()
{
    PlaySoundMem(Title, DX_PLAYTYPE_LOOP, true);           //タイトル
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
    PlaySoundMem(GameOver, DX_PLAYTYPE_LOOP, true);        //ゲームオーバー
}
void BGM::StopGameOver()
{
    StopSoundMem(GameOver);
}


void BGM::PlayJumpSound()
{
    PlaySoundMem(Jump, DX_PLAYTYPE_BACK, true);            //ジャンプ
}
void BGM::StopJumpSound()
{
    StopSoundMem(Jump);
}