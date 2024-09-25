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
	void Draw();			// 描画.
	void Jump();			//ジャンプ
	// モデルハンドルの取得.
	const VECTOR& GetPos() const { return Pos; }
	void Set(bool flag) { SpeedDownJudge = flag; }
	//const bool GetEnd() const { return EndJudge; }
	 
private:
	//プレイヤー自身に関するメンバ変数
	VECTOR	Velocity;		// 移動力.
	VECTOR	Pos;			// ポジション.
	VECTOR	Dir;			// 回転方向
	float Rotation;			//プレイヤーを回転させる変数
	int ChangeSpeedTime;	// 時間計測用の変数

	//ゲームに関する変数
	bool EndJudge;//ゲームオーバー演出が終わったかどうかの判定]

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
