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
	VECTOR pos;				//
	int CoinHandle;			//
	float Rotation;			//
	float Hight;			//
	bool isActive;			//
	// 静的定数.
	static const float Scale;	//	
	static const float CoinNum;	//

};
