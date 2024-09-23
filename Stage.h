#pragma once
class Stage
{
public:
	Stage();
	~Stage();
	void Init();
	void Update();
	void GameDraw();
private:
	VECTOR pos;
	int StageHandle;
	// Ã“I’è”.
	static const float Speed;
	static const float Scale;
};