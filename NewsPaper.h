#pragma once
class NewsPaper
{
public:
	NewsPaper();
	~NewsPaper();
	void Initialize();
	void Update();
	void Draw();
private:
	VECTOR Pos;				//�|�W�V����
	int NewsPaperHandle;	//�RD���f���n���h��
	bool flag ;				// �t���O�̏����l
	int interval;			// �؂�ւ��Ԋu�i�~���b�j
	int lastTime;			// �Ō�Ƀt���O��؂�ւ�������
};
