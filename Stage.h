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
	VECTOR pos[3];
	int StageHandle[3];
	// �ÓI�萔.
	static const float Speed;
	static const float Scale;
	static const int StageNum3;
};