#pragma once
class Bus
{
public:
	Bus();
	~Bus();
	void Init();
	void Update(int PlacePattern,float ObstacleSpeed);		//ゲーム中の更新
	void BlowAway();										//ぶっ飛び処理
	void GameDraw();										//バスの描画
	const VECTOR& GetPos() const { return pos[0]; }			//一つ目のバスのポジションを返す
	const VECTOR& GetPos2() const { return pos[1]; }		//二つ目のバスのポジションを返す
	const bool& GetisActive()const { return isActive; }		//表示されているか返す

private:
	VECTOR pos[2];		//ポジション
	bool isActive;		//表示しているか
	int BusHandle[2];	//バスのハンドル
	float Rotation;		//回転変数
	// 静的定数.
	static const float Scale;
};