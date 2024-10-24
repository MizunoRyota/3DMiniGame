#pragma once
class BGM
{
public:
	BGM();
	~BGM();
	//ÉQÅ[ÉÄBGM
	void PlayGameTitle();
	void StopGameTitle();
	void PlayGameSound();
	void StopGameSound();
	void PlayGameEnd();
	void StopGameEnd();
	void PlayGameOver();
	void StopGameOver();
	//å¯â âπ
	void PlayCrushTar();
	void StopCrushTar();
	void PlayCrushNewsPaper();
	void StopCrushNewsPaper();
	void PlayCoinSound();
	void StopCoinSound();
	void PlayJumpSound();
	void StopJumpSound();
private:
	//ÉQÅ[ÉÄBGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//å¯â âπ
	int Tar;
	int NewsPaper;
	int Coin;
	int Jump;
};

