#pragma once
class BGM
{
public:
	BGM();
	~BGM();
	//ゲームBGM
	void PlayGameTitle();
	void StopGameTitle();
	void PlayGameSound();
	void StopGameSound();
	void PlayGameEnd();
	void StopGameEnd();
	void PlayGameOver();
	void StopGameOver();
	//効果音
	void PlayCrushTar();
	void StopCrushTar();
	void PlayCrushNewsPaper();
	void StopCrushNewsPaper();
	void PlayCoinSound();
	void StopCoinSound();
	void PlayJumpSound();
	void StopJumpSound();
private:
	//ゲームBGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//効果音
	int Tar;
	int NewsPaper;
	int Coin;
	int Jump;
};

