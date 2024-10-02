#include"DxLib.h"
#include"Player.h"
#include"HitChecker.h"
// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Player::Speed = static_cast<float>(10000.0 / 45.0 / 45.0 / 45.0);
const float Player::DownSpeed = static_cast<float>(10000.0 / 80.0 / 80.0 / 80.0);

const float Player::Scale = 0.006f;		// �X�P�[��
const float Player::Gravity = 0.60f;     // �d�͉����x
const float Player::JumpSpeed = 0.18f;   // �W�����v�̏����x

Player::Player()
{
	// �R�c���f���̓ǂݍ���
	PlayerHandle = MV1LoadModel("Data/3Dmodel/Player/Player.mv1");
	//�摜�̓ǂݍ���
	SpeedDownHandle = LoadGraph("Data/Texture/game/SpeedDown.png");
	BettoriHnadle = LoadGraph("Data/Texture/game/Bettori.png");
	 
	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	EndJudge = true;
	SpeedDownJudge = false;
	Pos = VGet(0, 0.5f, 0);
	Velocity = VGet(0, 0, 0);
	Dir = VGet(0, 0, 1);
	ChangeSpeedTime = 0;
	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f,-90.0f * DX_PI_F / 180.0f, 0.0f));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PlayerHandle, Pos);
}

Player::~Player()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(PlayerHandle);
}

void Player::PlayerInitialize()
{
	//���[�V�����̕ύX
	ChangeMotion(4);
	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	//�v���C���[�̏�����
	Pos = VGet(0.5, 0.5f, -7.0);
	Velocity = VGet(0, 0, 0);
	Dir = VGet(0, 0, 0);
	Rotation=0;
	SpeedDownJudge = false;
	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f,300.0f * DX_PI_F / 180.0f, 0.0f));
	MV1GetRotationXYZ( PlayerHandle);
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PlayerHandle, Pos);
}

void  Player::PlayerTitle()
{

	// �Đ����Ԃ�i�߂�
	PlayTime += 0.5f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (PlayTime >= TotalTime)
	{
		PlayTime = 0.0f;
	}

	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����	// �R�c���f����Y���̉�]�l�𐳖ʂɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 300.0f * DX_PI_F / 180.0f, 0.0f));

	// 3D���f���̃X�P�[������
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PlayerHandle, Pos);

	//3d���f���̃A�j���[�V�����̃Z�b�g
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);

}

void Player::ChangeMotion(int motionNum)
{
	MV1DetachAnim(PlayerHandle, AttachIndex);

	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);

	this->PlayAnim = motionNum;
	// �R�c���f���̂O�Ԗڂ̃A�j���[�V�������A�^�b�`����
	AttachIndex = MV1AttachAnim(PlayerHandle, this->PlayAnim, -1, FALSE);
	// �A�^�b�`�����A�j���[�V�����̑��Đ����Ԃ��擾����
	TotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, AttachIndex);
}

void Player::PlayerUpdate()
{

	// �R�c���f����Y���̉�]�l�𐳖ʂɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));

	// �L�[���͎擾
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// �L�[�{�[�h���͂̃`�F�b�N
	if (CheckHitKey(KEY_INPUT_UP))
	{
		Jump();  // �X�y�[�X�L�[�������ꂽ��W�����v���J�n
	}

	// �W�����v���̏���
	if (isJumping)
	{
		// ���݂̃W�����v���x���|�W�V�����ɔ��f
		Pos.y += jumpVelocity;

		// �d�͂̉e�����󂯂�
		jumpVelocity -= Gravity * 0.016f; // �t���[�����[�g�Ɉˑ���������

		// �n�ʂɒ��n�����ꍇ
		if (Pos.y <= 0.50f)
		{
			//���[�V�����̕ύX
			ChangeMotion(1);
			Pos.y = 0.50f;     // �n�ʂɃZ�b�g
			isJumping = false; // �W�����v��Ԃ����Z�b�g
			jumpVelocity = 0;  // �W�����v���x�����Z�b�g
		}
	}

	if (Pos.y <= 0.5f)
	{
		ChangeMotion(1);
	}

	// �Đ����Ԃ�i�߂�
	PlayTime += 0.4f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (PlayTime >= TotalTime)
	{
		PlayTime = 0.0f;
	}

	// �P���ɕ����]��
	Dir = VGet(0, 0, 0);

	if (Key & PAD_INPUT_RIGHT)
	{
		Dir = VAdd(Dir, VGet(1, 0, 0));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		Dir = VAdd(Dir, VGet(-1, 0, 0));
	}

	// �[�����Z����
	if (VSquareSize(Dir) > 0)
	{
		// ���K��
		Dir = VNorm(Dir);
	}

	ChangeSpeedFlag();

	// �|�W�V�������X�V.
	if (SpeedDownJudge==true)
	{
		Velocity = VScale(Dir, DownSpeed);
	}
	else
	{
		Velocity = VScale(Dir, Speed);
	}

	Pos = VAdd(Pos, Velocity);

	// �͂������I������x���V�e�B�̕����Ƀf�B���N�V�����𒲐�.
	if (VSize(Velocity) != 0)
	{
		Dir = VNorm(Velocity);
	}

	if (Pos.x>3)
	{
		Pos.x -= 0.3;
	}
	else if (Pos.x<-3)
	{
		Pos.x -= -0.3;
	}

	// 3D���f���̃X�P�[������
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PlayerHandle, Pos);

	//3d���f���̃A�j���[�V�����̃Z�b�g
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);
}

void Player::Jump()
{
	//���[�V�����̕ύX
	ChangeMotion(3);
	// �v���C���[���n�ʂɂ��鎞�����W�����v���J�n
	if (!isJumping)
	{
		isJumping = true;
		jumpVelocity = JumpSpeed;  // �W�����v�����x��ݒ�
	}
}

bool Player::PlayerEnd()
{

	//���[�V�����̕ύX
	ChangeMotion(0);

	// �Đ����Ԃ�i�߂�
	PlayTime += 0.1f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	//if (PlayTime >= TotalTime)
	//{
	//	PlayTime = 0.0f;
	//}
	if (Pos.z>=-22)
	{
		Pos.z -= 0.1f;
		Pos.y += 0.017f;
		Rotation += 0.25f;
		EndJudge = true;
	}
	else
	{
		EndJudge = false;
	}

	// �R�c���f����Y���̉�]�l�𐳖ʂɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(-90.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, Rotation));
	// 3D���f���̃X�P�[������
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PlayerHandle, Pos);
	//3d���f���̃A�j���[�V�����̃Z�b�g
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);

	return EndJudge;

}

void Player::PlayerGameOver()
{
	//�v���C���[�������Ă���
	Pos.y -= 0.005;
	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(PlayerHandle, Pos);
}

void Player::ChangeSpeedFlag()
{
	if (SpeedDownJudge==true)
	{
		DrawSpeedDown();
		// ����̌Ăяo�����ɊJ�n������ݒ�
		if (ChangeSpeedTime == 0)
		{
			ChangeSpeedTime = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
		}

		// �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
		if (GetNowCount() - ChangeSpeedTime >= 2500)
		{
			SpeedDownJudge = false;
			ChangeSpeedTime = 0;
		}
	}
}

void Player::ChangeSpeed()
{
	SpeedDownJudge = true;
}

void Player::DrawSpeedDown()
{
	if (SpeedDownJudge == true)
	{
		DrawGraph(600, 600, BettoriHnadle, true);
		DrawGraph(900, 100, BettoriHnadle, true);
		DrawGraph(100, 50, BettoriHnadle, true);
	}
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw()
{
	// �R�c���f���̕`��
	MV1DrawModel(PlayerHandle);
	DrawSpeedDown();
}