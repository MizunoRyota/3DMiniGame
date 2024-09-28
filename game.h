#pragma once
class GameState
{
public:
	//コンストラクタ・デストラクタ
	GameState();
	~GameState();
	void GameInitialize();					//初期化
	void GameTitle();						//タイトル表示
	void GameReady();						//チュートリアル表示
	void GameUpdate();						//ゲーム中の更新
	void SerchObstaclePos();				//障害物のポジションを調べる
	void ObstacleConfiguration();			//障害物パターンの配置
	void ScoreDraw();						//スコアの表示
	void HighScoreDraw();					//ハイスコアの表示
	void GameOver();						//ゲームオーバーの表示
	const int& GetObstaclePattern() const { return ObstaclePattern; }	//障害物パターン渡し

private:
	int Controller;		//コントローラーの画像
	int PaintHandle[4]; //ペイントの画像
	int Score;			//スコア
	int HighScore;		//ハイスコア
	int SpeedMeter;		//現在のスピード
	int ObstaclePattern;//障害物の配置パターン
	bool IsObstacle;	//障害物があるかどうかの判定

};
