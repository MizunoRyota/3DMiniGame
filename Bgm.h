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
	void PlayCountDown1();
	void StopCountDown1();	
	void PlayCountDown2();
	void StopCountDown2();


private:
	//ゲームBGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//効果音
	int CountDown1;
	int CountDown2;
};

