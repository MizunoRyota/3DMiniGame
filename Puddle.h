#pragma once


//みずたまり
class Puddle
{
public:
	Puddle();
	~Puddle();
	void Init();
	void Update();
	void Draw();
	const VECTOR& GetPos() const { return pos; }//ポジションの位置返す

private:
	VECTOR pos;
	int PuddleHandle;
	static const float Scale;
};
