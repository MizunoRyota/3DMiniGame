#pragma once
class BGM
{
public:
	BGM();
	~BGM();
	//�Q�[��BGM
	void PlayGameTitle();
	void StopGameTitle();
	void PlayGameSound();
	void StopGameSound();
	void PlayGameEnd();
	void StopGameEnd();
	void PlayGameOver();
	void StopGameOver();
	//���ʉ�
	void PlayCrushTar();
	void StopCrushTar();
	void PlayCrushNewsPaper();
	void StopCrushNewsPaper();
	void PlayCoinSound();
	void StopCoinSound();
	void PlayJumpSound();
	void StopJumpSound();
private:
	//�Q�[��BGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//���ʉ�
	int Tar;
	int NewsPaper;
	int Coin;
	int Jump;
};

