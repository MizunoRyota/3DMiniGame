#pragma once
class Coin
{
public:
	Coin();
	~Coin();
	void Init();
	void Update(const VECTOR& carpos);
	void CoinInitalize();
	void Draw();
	void CoinMove();
	const VECTOR& GetPos() const { return pos; }//ポジションの位置返す
private:
	VECTOR pos;				//ポジション
	int CoinHandle;			//3Dmodel
	float Rotation;			//回転変数
	float Hight;			//高さ
	bool isActive;			//動いているか
	// 静的定数.
	static const float Scale;	
	static const float CoinNum;	

};
