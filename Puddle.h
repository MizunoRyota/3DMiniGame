#pragma once


//�݂����܂�
class Puddle
{
public:
	Puddle();
	~Puddle();
	void Init();								//������
	void Update(float ObstacleSpeed, bool ObstaclePattern);			//�X�V
	void Draw();								//�`��
	const VECTOR& GetPos() const { return pos; }//�|�W�V�����̈ʒu�Ԃ�

private:
	VECTOR pos;					//�|�W�V����
	int PuddleHandle;			//3Dmodel�̃n���h��
	static const float Scale;	
};
