#pragma once
class Bus
{
public:
	Bus();
	~Bus();
	void Init();
	void Update(int PlacePattern,float ObstacleSpeed);		//�Q�[�����̍X�V
	void BlowAway();										//�Ԃ���я���
	void GameDraw();										//�o�X�̕`��
	const VECTOR& GetPos() const { return pos[0]; }			//��ڂ̃o�X�̃|�W�V������Ԃ�
	const VECTOR& GetPos2() const { return pos[1]; }		//��ڂ̃o�X�̃|�W�V������Ԃ�
	const bool& GetisActive()const { return isActive; }		//�\������Ă��邩�Ԃ�

private:
	VECTOR pos[2];		//�|�W�V����
	bool isActive;		//�\�����Ă��邩
	int BusHandle[2];	//�o�X�̃n���h��
	float Rotation;		//��]�ϐ�
	// �ÓI�萔.
	static const float Scale;
};