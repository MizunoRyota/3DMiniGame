#pragma once

class Car
{
public:
	Car();
	~Car();
	void Init();
	void CarTitle();	//�^�C�g�����̕\��
	void Update();		//�Q�[�����̍X�V
	void GameDraw();	//�Ԃ̕\��
	const VECTOR& GetPos() const { return pos; }//�|�W�V�����̈ʒu�Ԃ�
private:
	VECTOR pos;			//�|�W�V����
	int CarHandle;		//�Ԃ̃n���h��
	bool isActive;		//�\������Ă��邩�ǂ���
	int dir;			//�Ԃ̕���
	// �ÓI�萔.
	static const float Speed;
	static const float Scale;
};