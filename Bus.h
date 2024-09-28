#pragma once
class Bus
{
public:
	Bus();
	~Bus();
	void Init();
	void Update(int PlacePattern);			//ゲーム中の更新
	void GameDraw();		//バスの描画
	const VECTOR& GetPos() const { return pos; }			//ポジションを返す
	const bool& GetisActive()const { return isActive; }		//表示されているか返す
private:
	VECTOR pos;			//ポジション
	bool isActive;		//表示しているか
	int BusHandle;		//バスのハンドル
	// 静的定数.
	static const float Scale;
};