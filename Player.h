#pragma once

class Player 
{
public:
	Player();
	~Player();
	void PlayerInitialize();//初期化
	void PlayerTitle();		//ゲームタイトル
	void PlayerUpdate();	//ゲーム中
	void ChangeSpeed();		//スピードの切り替え
	bool PlayerEnd();		//ゲームオーバー前段階	
	void PlayerGameOver();	//ゲームオーバー
	void ChangeMotion(int motionNum);//モーション変更
	void ChangeSpeedFlag();			 //下がったスピードを元に戻す関数
	void MeterMove();				 //無敵メーターの更新
	void ChangeInvicible();			//無敵状態ににする
	void DrawInvicibleMeter(int x, int y, int width, int height, int max, int val, int color);//無敵ゲージの更新
	void DrawInvicible();			 //無敵の表示
	void DrawSpeedDown();	//スピードダウン画像の表示
	void Draw();			// 描画.
	void Jump();			//ジャンプ
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return Pos; }
	const bool GetInvicible() const { return Invicible; }
	void Set(bool flag) { SpeedDownJudge = flag; }
private:
	//プレイヤー自身に関するメンバ変数
	VECTOR	Velocity;		// 移動力.
	VECTOR	Pos;			// ポジション.
	VECTOR	Dir;			// 回転方向
	float Rotation;			//プレイヤーを回転させる変数
	int ChangeSpeedTime;	//時間計測用の変数
	int InvicibleGraph;		//無敵の画像
	int InvicibleChargeGraph;//チャージ中の画像
	int InvicibleCharge;	//無敵までのチャージ時間
	bool Invicible;			//無敵かどうかの判定
	bool CanInvicible;      //無敵になれるかの判定
	float mVal;				//メーター
	float mValInc;			//メーターの増える値
	static const int mMaxval = 150;//メーターの最大値
	//ゲームに関する変数
	bool EndJudge;				//ゲームオーバー演出が終わったかどうかの判定
	int SpeedDownHandle;		//スピードダウン中の画像
	int BettoriHnadle;			//べっとり効果音の画像
	int	BettoriFrame;			//べっとり枠の画像

	//アニメーションに関するメンバ変数
	int PlayerHandle;			// モデルハンドル.
	float TotalTime, PlayTime;	//アニメーションの時間の合計
	int PlayAnim;				//現在のアニメーションハンドル
	int AttachIndex;			//アニメーションを付与される変数
	float AnimTime;				//アニメーションを進める変数
	bool SpeedDownJudge;		//スピードダウン状態になっているかの判定

	// ジャンプに関するメンバ変数
	bool isJumping;       // プレイヤーがジャンプしているかどうかを示すフラグ
	bool isRunnig;		  // プレイヤーが走っているかどうかを示すフラグ
	float jumpVelocity;   // 現在のジャンプ速度
	float jumpHeight;     // 最大ジャンプ高さ

	// 静的定数.
	static const float Speed;		//スピード(nomal)
	static const float DownSpeed;	//スピード低下状態
	static const float Scale;		//大きさ
	static const float Gravity;     // 重力定数
	static const float JumpSpeed;   // ジャンプの初速度
};
