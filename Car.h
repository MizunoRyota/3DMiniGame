#pragma once

class Car
{
public:
	Car();
	~Car();
	void Init();
	void CarTitle();	//タイトル時の表示
	void Update(int PlacePattern);		//ゲーム中の更新
	void GameDraw();	//車の表示
	const VECTOR& GetPos() const { return pos; }//ポジションの位置返す
private:
	VECTOR pos;			//ポジション
	int CarHandle;		//車のハンドル
	bool isActive;		//表示されているかどうか
	// 静的定数.
	static const float Scale;
};