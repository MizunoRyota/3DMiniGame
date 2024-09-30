#pragma once
class NewsPaper
{
public:
	NewsPaper();
	~NewsPaper();
	void Initialize();
	void Update();
	void Draw();
private:
	VECTOR Pos;				//ポジション
	int NewsPaperHandle;	//３Dモデルハンドル
	bool flag ;				// フラグの初期値
	int interval;			// 切り替え間隔（ミリ秒）
	int lastTime;			// 最後にフラグを切り替えた時間
};
