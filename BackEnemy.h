#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

private:
	int EnemyHandle;	// モデルハンドル.
	float TotalTime, PlayTime;
	int AttachIndex;
	float AnimTime;
	VECTOR	Velocity;		// 移動力.
	VECTOR	Pos;			// ポジション.
};

