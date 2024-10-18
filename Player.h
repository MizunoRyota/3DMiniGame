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
	void MeterMove();				 //���G���[�^�[�̍X�V
	void ChangeInvicible();			//���G��Ԃɂɂ���
	void DrawInvicibleMeter(int x, int y, int width, int height, int max, int val, int color);//���G�Q�[�W�̍X�V
	void DrawInvicible();			 //���G�̕\��
	void DrawSpeedDown();	//�X�s�[�h�_�E���摜�̕\��
	void Draw();			// �`��.
	void Jump();			//�W�����v
	// ���f���n���h���̎擾.
	const VECTOR& GetPos() const { return Pos; }
	const bool GetInvicible() const { return Invicible; }
	void Set(bool flag) { SpeedDownJudge = flag; }
private:
	//�v���C���[���g�Ɋւ��郁���o�ϐ�
	VECTOR	Velocity;		// �ړ���.
	VECTOR	Pos;			// �|�W�V����.
	VECTOR	Dir;			// ��]����
	float Rotation;			//�v���C���[����]������ϐ�
	int ChangeSpeedTime;	//���Ԍv���p�̕ϐ�
	int InvicibleGraph;		//���G�̉摜
	int InvicibleChargeGraph;//�`���[�W���̉摜
	int InvicibleCharge;	//���G�܂ł̃`���[�W����
	bool Invicible;			//���G���ǂ����̔���
	bool CanInvicible;      //���G�ɂȂ�邩�̔���
	float mVal;				//���[�^�[
	float mValInc;			//���[�^�[�̑�����l
	static const int mMaxval = 150;//���[�^�[�̍ő�l
	//�Q�[���Ɋւ���ϐ�
	bool EndJudge;				//�Q�[���I�[�o�[���o���I��������ǂ����̔���
	int SpeedDownHandle;		//�X�s�[�h�_�E�����̉摜
	int BettoriHnadle;			//�ׂ��Ƃ���ʉ��̉摜
	int	BettoriFrame;			//�ׂ��Ƃ�g�̉摜

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
