#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();

private:
	int EnemyHandle;	// ���f���n���h��.
	float TotalTime, PlayTime;
	int AttachIndex;
	float AnimTime;
	VECTOR	Velocity;		// �ړ���.
	VECTOR	Pos;			// �|�W�V����.
};

