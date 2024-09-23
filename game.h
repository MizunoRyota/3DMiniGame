#pragma once
class GameState
{
public:
	//コンストラクタ・デストラクタ
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
	int Controller;		//コントローラーの画像
	int Score;			//スコア
	int HighScore;		//ハイスコア
	int SpeedMeter;		//現在のスピード
};
