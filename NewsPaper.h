#pragma once
class NewsPaper
{
public:
	NewsPaper();
	~NewsPaper();
	void Initialize();
	void LateralMove();
	void Update();
	void CrashPaper();
	void ChangeCrush();
	void Draw();
	const VECTOR& GetPos() const { return Pos; }//�|�W�V�����̈ʒu�Ԃ�

private:
	VECTOR Pos;				//�|�W�V����
	int NewsPaperHandle;	//�RD���f���n���h��
	int NewsPaperGraph;		//�V�����̉摜
	float Rotation;			//��]�ϐ�
	float CrushTime;		//�Ԃ��鎞��
	bool flag ;				// �t���O�̏����l
	bool RightDir;			//�E����	
	bool LeftDir;			//������
	bool CrushJudge;		//��������������
	int interval;			// �؂�ւ��Ԋu�i�~���b�j
	int lastTime;			// �Ō�Ƀt���O��؂�ւ�������
	static const float Scale;

};
