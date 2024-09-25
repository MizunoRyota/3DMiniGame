#pragma once
class Bus
{
public:
	Bus();
	~Bus();
	void Init();
	void Update();			//�Q�[�����̍X�V
	void GameDraw();		//�o�X�̕`��
	const VECTOR& GetPos() const { return pos; }			//�|�W�V������Ԃ�
	const bool& GetisActive()const { return isActive; }		//�\������Ă��邩�Ԃ�
private:
	VECTOR pos;			//�|�W�V����
	bool isActive;		//�\�����Ă��邩
	int BusHandle;		//�o�X�̃n���h��
	int dir;			//�|�W�V�����̏ꏊ
	// �ÓI�萔.
	static const float Speed;
	static const float Scale;
};