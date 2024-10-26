#include"DxLib.h"
#include"Bgm.h"

BGM::BGM()
{
    //�Q�[���T�E���h
    Game=LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 35 / 100, Game);
    Title = LoadSoundMem("Data/Sound/bgm/Title.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, Title);    
    GameEnd = LoadSoundMem("Data/Sound/bgm/Crush.mp3");
    ChangeVolumeSoundMem(255 * 40 / 100, GameEnd);
    GameOver = LoadSoundMem("Data/Sound/bgm/Game.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, GameOver);
    //���ʉ�
    CountDown1 = LoadSoundMem("Data/Sound/bgm/Countdown1.mp3");
    ChangeVolumeSoundMem(255 * 80 / 100, CountDown1);
    CountDown2 = LoadSoundMem("Data/Sound/bgm/CountDown2.mp3");
    ChangeVolumeSoundMem(255 * 80 / 100, CountDown2);
}

BGM::~BGM()
{
    // �������ׂč폜���܂�
    InitSoundMem();
}

void BGM::PlayGameSound()
{
    PlaySoundMem(Game, DX_PLAYTYPE_LOOP, false);            //�Q�[����
}
void BGM::StopGameSound()
{
    StopSoundMem(Game);
}
void BGM::PlayGameTitle()
{
    PlaySoundMem(Title, DX_PLAYTYPE_LOOP, false);           //�^�C�g��
}
void BGM::StopGameTitle()
{
    StopSoundMem(Title);
}

void BGM::PlayGameEnd()
{
    PlaySoundMem(GameEnd, DX_PLAYTYPE_BACK, true);         //�Q�[���I���
}
void BGM::StopGameEnd()
{
    StopSoundMem(GameEnd);
}
void BGM::PlayGameOver()
{
    PlaySoundMem(GameOver, DX_PLAYTYPE_LOOP, false);        //�Q�[���I�[�o�[
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