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
	// �ÓI�萔.
	static const float Speed;
	static const float Scale;
};