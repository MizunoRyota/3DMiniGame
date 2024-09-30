#pragma once
class Coin
{
public:
	Coin();
	~Coin();
	void Init();
	void Update(const VECTOR& buspos, const VECTOR& carpos);
	void CoinInitalize();
	void Draw();
private:
	VECTOR pos[10];
	int CoinHandle[11];
	float Rotation;
	bool isActive;
	int dir;
	// ê√ìIíËêî.
	static const float Scale;
	static const float CoinNum;

};
