#pragma once


//�݂����܂�
class Puddle
{
public:
	Puddle();
	~Puddle();
	void Init();
	void Update();
	void Draw();
	const VECTOR& GetPos() const { return pos; }//�|�W�V�����̈ʒu�Ԃ�

private:
	VECTOR pos;
	int PuddleHandle;
	static const float Scale;
};
