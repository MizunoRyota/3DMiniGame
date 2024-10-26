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
	void PlayCountDown1();
	void StopCountDown1();	
	void PlayCountDown2();
	void StopCountDown2();


private:
	//�Q�[��BGM
	int Title;
	int Game;
	int GameEnd;
	int GameOver;
	//���ʉ�
	int CountDown1;
	int CountDown2;
};

