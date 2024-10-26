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
    GameOver = LoadSoundMem("Data/Sound/bgm/GameOver.mp3");
    ChangeVolumeSoundMem(255 * 20 / 100, GameOver);

}

BGM::~BGM()
{
    // �������ׂč폜���܂�
    InitSoundMem();
}

void BGM::PlayGameSound()
{
    PlaySoundMem(Game, DX_PLAYTYPE_LOOP, true);            //�Q�[����
}
void BGM::StopGameSound()
{
    StopSoundMem(Game);
}
void BGM::PlayGameTitle()
{
    PlaySoundMem(Title, DX_PLAYTYPE_LOOP, true);           //�^�C�g��
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
    PlaySoundMem(GameOver, DX_PLAYTYPE_LOOP, true);        //�Q�[���I�[�o�[
}
void BGM::StopGameOver()
{
    StopSoundMem(GameOver);
}


void BGM::PlayJumpSound()
{
    PlaySoundMem(Jump, DX_PLAYTYPE_BACK, true);            //�W�����v
}
void BGM::StopJumpSound()
{
    StopSoundMem(Jump);
}