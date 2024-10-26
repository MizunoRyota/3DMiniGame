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
	void PlayCountDown1();
	void StopCountDown1();	
	void PlayCountDown2();
	void StopCountDown2();


private:
	//ÉQÅ[ÉÄBGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//å¯â âπ
	int CountDown1;
	int CountDown2;
};

