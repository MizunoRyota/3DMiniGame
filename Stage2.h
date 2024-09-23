#pragma once
class Stage2
{
public:
	Stage2();
	~Stage2();
	void Init();
	void Update();
	void GameDraw();
private:
	VECTOR pos;
	int Stage2Handle;
	// Ã“I’è”.
	static const float Speed;
	static const float Scale;
};
