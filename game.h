#pragma once
class GameState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	GameState();
	~GameState();
	void GameInitialize();
	void GameTitle();
	void GameReady();
	void GameUpdate();
	void ScoreDraw();
	void HighScoreDraw();
	void GameOver();

private:
	int Controller;		//�R���g���[���[�̉摜
	int Score;			//�X�R�A
	int HighScore;		//�n�C�X�R�A
	int SpeedMeter;		//���݂̃X�s�[�h
};
