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

	void PlayCrushNewsPaper();
	void StopCrushNewsPaper();

	void PlayJumpSound();
	void StopJumpSound();
private:
	//ÉQÅ[ÉÄBGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//å¯â âπ
	int Jump;
};

