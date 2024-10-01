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
private:
	VECTOR pos;
	int CoinHandle;
	float Rotation;
	float Hight;
	bool isActive;
	// ê√ìIíËêî.
	static const float Scale;
	static const float CoinNum;

};
