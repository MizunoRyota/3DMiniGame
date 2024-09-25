#pragma once

class Player 
{
public:
	Player();
	~Player();
	void PlayerInitialize();//������
	void PlayerTitle();		//�Q�[���^�C�g��
	void PlayerUpdate();	//�Q�[����
	void ChangeSpeed();		//�X�s�[�h�̐؂�ւ�
	bool PlayerEnd();		//�Q�[���I�[�o�[�O�i�K	
	void PlayerGameOver();	//�Q�[���I�[�o�[
	void ChangeMotion(int motionNum);//���[�V�����ύX
	void ChangeSpeedFlag();			 //���������X�s�[�h�����ɖ߂��֐�
	void Draw();			// �`��.
	void Jump();			//�W�����v
	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return Pos; }
	void Set(bool flag) { SpeedDownJudge = flag; }
	//const bool GetEnd() const { return EndJudge; }
	 
private:
	//�v���C���[���g�Ɋւ��郁���o�ϐ�
	VECTOR	Velocity;		// �ړ���.
	VECTOR	Pos;			// �|�W�V����.
	VECTOR	Dir;			// ��]����
	float Rotation;			//�v���C���[����]������ϐ�
	int ChangeSpeedTime;	// ���Ԍv���p�̕ϐ�

	//�Q�[���Ɋւ���ϐ�
	bool EndJudge;//�Q�[���I�[�o�[���o���I��������ǂ����̔���]

	//�A�j���[�V�����Ɋւ��郁���o�ϐ�
	int PlayerHandle;			// ���f���n���h��.
	float TotalTime, PlayTime;	//�A�j���[�V�����̎��Ԃ̍��v
	int PlayAnim;				//���݂̃A�j���[�V�����n���h��
	int AttachIndex;			//�A�j���[�V������t�^�����ϐ�
	float AnimTime;				//�A�j���[�V������i�߂�ϐ�
	bool SpeedDownJudge;		//�X�s�[�h�_�E����ԂɂȂ��Ă��邩�̔���
	// �W�����v�Ɋւ��郁���o�ϐ�
	bool isJumping;       // �v���C���[���W�����v���Ă��邩�ǂ����������t���O
	bool isRunnig;		  // �v���C���[�������Ă��邩�ǂ����������t���O
	float jumpVelocity;   // ���݂̃W�����v���x
	float jumpHeight;     // �ő�W�����v����

	// �ÓI�萔.
	static const float Speed;		//�X�s�[�h(nomal)
	static const float DownSpeed;	//�X�s�[�h�ቺ���
	static const float Scale;		//�傫��
	static const float Gravity;     // �d�͒萔
	static const float JumpSpeed;   // �W�����v�̏����x
};
