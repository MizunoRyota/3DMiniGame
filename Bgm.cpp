#include"DxLib.h"
#include"Bgm.h"

BGM::BGM()
{
    //ゲームサウンド
    Game=LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, Game);
    Title = LoadSoundMem("Data/Sound/bgm/Title.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, Title);    
    GameEnd = LoadSoundMem("Data/Sound/bgm/Crush.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, GameEnd);
    GameOver = LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, Game);
    //効果音
    GameEnd = LoadSoundMem("Data/Sound/bgm/CrushTar.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, Coin);    
    GameEnd = LoadSoundMem("Data/Sound/bgm/Crush.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, Coin);
    GameEnd = LoadSoundMem("Data/Sound/bgm/Crush.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, Coin);
    GameOver = LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, Jump);
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
    PlaySoundMem(GameEnd, DX_PLAYTYPE_BACK, false);         //ゲーム終わり
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
void BGM::PlayCoinSound()
{
    PlaySoundMem(Coin, DX_PLAYTYPE_BACK, false);            //コインゲット
}
void BGM::StopGameEnd()
{
    StopSoundMem(Coin);
}
void BGM::PlayJumpSound()
{
    PlaySoundMem(Jump, DX_PLAYTYPE_BACK, false);            //ジャンプ
}
void BGM::StopJumpSound()
{
    StopSoundMem(Jump);
}