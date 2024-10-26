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
	void MoveArrow();						//矢印更新
	void GameUpdate();						//ゲーム中の更新
	void SpeedUpDraw();						//
	void CountDown();						//
	void CrushCoin();						//
	void PlayDecideSound();
	void StopDecideSound();
	void PlayCoinSound();
	void StopCoinSound();
	void ObstacleSpeedUpdate();				//障害物のスピード更新
	void ObstacleConfiguration();			//障害物パターンの配置
	void ChangeScoreColor();				//スコアの色の更新
	void ScoreDraw();						//スコアの表示
	void ScoreUp();							//スコア加算
	void HighScoreDraw();					//ハイスコアの表示
	void GameOver();						//ゲームオーバーの表示
	void Draw();							//
	const int& GetObstaclePattern() const { return ObstaclePattern; }	//障害物パターン渡し
	const float& GetObstacleSpeed() const { return ObstacleSpeed; }	//障害物スピード渡し
	const bool& GetReadyPhase3() const { return ReadyPhase3; }		//
private:
	int Controller;							//コントローラーの画像
	int PaintHandle[4];						//ペイントの画像
	int TitleHandle;						//タイトルの画像
	int SpaceHandle;						//スペースキーの画像
	int RedSpaceHandle;						//赤いスペースキーの画像
	int LeftArrowHandle;					//←の画像
	int RightArrowHandle;					//→の画像
	int PuddleTutorialHandle;				//水たまり画像
	int NewsPaperTutorialHandle;			//新聞紙画像
	bool IsCoin;							//
	int CrushNewsPaperHandle;				//新聞紙に衝突した時の画像ハンドル
	int ScoreColorR;						//	スコアの色R
	int ScoreColorG;						//	スコアの色G
	int ScoreColorB;						//　スコアの色B
	int ColorChangeSpeed;					//	スコアの色が変化する速度
	int Coin;
	int Score;								//スコア
	int HighScore;							//ハイスコア
	int SpeedMeter;							//現在のスピード
	int ObstaclePattern;					//障害物の配置パターン
	float ObstacleSpeed;					//障害物速度
	bool IsObstacle;						//障害物があるかどうかの判定
	//チュートリアル
	bool ReadyPhase1;						//チュートリアル画面1段階
	bool ReadyPhase2;						//チュートリアル画面2段階
	bool ReadyPhase3;						//チュートリアル画面3段階
	bool ArrowMove;						
	int ArrowHandle;						//矢印画像ハンドル
	float ArrowPosX;						//矢印のX座標の位置
	float ArrowSpeed;						//矢印のスピード
	int Decide;								//決定音

};
