#pragma once
class NewsPaper
{
public:
	NewsPaper();
	~NewsPaper();
	void Initialize();
	void LateralMove();
	void Update();
	void CrashPaper();
	void ChangeCrush();
	void Draw();
	const VECTOR& GetPos() const { return Pos; }//ポジションの位置返す

private:
	VECTOR Pos;				//ポジション
	int NewsPaperHandle;	//３Dモデルハンドル
	int NewsPaperGraph;		//新聞紙の画像
	float Rotation;			//回転変数
	float CrushTime;		//ぶつかる時間
	bool flag ;				// フラグの初期値
	bool RightDir;			//右動き	
	bool LeftDir;			//左動き
	bool CrushJudge;		//当たったか判定
	int interval;			// 切り替え間隔（ミリ秒）
	int lastTime;			// 最後にフラグを切り替えた時間
	static const float Scale;

};
