#include"DxLib.h"
#include"Player.h"
#include"HitChecker.h"
#include"Bgm.h"
// �ÓI�萔
// ���x�i1=1m�A60fps�Œ�Ƃ��āA����10km�j
// 10000m �� ���� �� �� �� �b �� �t���[��
const float Player::Speed = static_cast<float>(10000.0 / 42.0 / 42.0 / 42.0);
const float Player::DownSpeed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);

const float Player::Scale = 0.006f;		// �X�P�[��
const float Player::Gravity = 0.75f;     // �d�͉����x
const float Player::JumpSpeed = 0.2f;   // �W�����v�̏����x

BGM* bgm = new BGM();

Player::Player()
{
	// �R�c���f���̓ǂݍ���
	PlayerHandle = MV1LoadModel("Data/3Dmodel/Player/Player.mv1");
	//�摜�̓ǂݍ���
	SpeedDownHandle = LoadGraph("Data/Texture/game/SpeedDown.png");
	BettoriFrame = LoadGraph("Data/Texture/game/TarGraph.png");
	BettoriHnadle = LoadGraph("Data/Texture/game/Bettori.png");
	InvicibleGraph= LoadGraph("Data/Texture/game/CanInvicible.png");
	InvicibleChargeGraph=LoadGraph("Data/Texture/game/Invicible.png");

	Tar = LoadSoundMem("Data/Sound/Game/���Ԃ��Ԃ�2.mp3");
	ChangeVolumeSoundMem(255 * 70 / 100, Tar);
	// �Đ����Ԃ̏�����
	PlayTime = 0.0f;
	EndJudge = true;
	Invicible = false;
	SpeedDownJudge = false;
	CanInvicible = false;
	Velocity = VGet(0, 0, 0);
	Pos = VGet(0, 0.5f, 0);
	Dir = VGet(0, 0, 1);
	ChangeSpeedTime = 0;
	mVal = 0;
	mValInc = 0.075;
	//�R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f,-90.0f * DX_PI_F / 180.0f, 0.0f));
	//�RD���f���̃|�W�V�����ݒ�
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
	Rotation = 0; 
	mVal = 0;
	SpeedDownJudge = false;
	Invicible = false;
	CanInvicible = false;
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

	// �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����	
	// // �R�c���f����Y���̉�]�l�𐳖ʂɃZ�b�g����
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
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_SPACE))
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
	//���G�̐؂�ւ�
	ChangeInvicible();

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

	if (Pos.x>2.5)
	{
		Pos.x = 2.5;
	}
	else if (Pos.x<-2.5)
	{
		Pos.x = -2.5;
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
void Player::PlayCrushTar()
{
	PlaySoundMem(Tar, DX_PLAYTYPE_BACK, true);            //�ׂ��Ƃ艹
}
void Player::StopCrushTar()
{
	StopSoundMem(Tar);
}
void Player::ChangeSpeedFlag()
{
	if (SpeedDownJudge==true)
	{
		DrawSpeedDown();
		// ����̌Ăяo�����ɊJ�n������ݒ�
		if (ChangeSpeedTime == 0)
		{
			PlayCrushTar();
			ChangeSpeedTime = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
		}

		// �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
		if (GetNowCount() - ChangeSpeedTime >= 1300)
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
		DrawGraph(400, 400, BettoriHnadle, true);
		DrawGraph(900, 150, BettoriHnadle, true);
		DrawGraph(100, 100, BettoriHnadle, true);
		DrawGraph(0, 475, BettoriFrame, true);
	}
}

void Player::MeterMove()
{
	//mVal = mMaxval;
	if (CanInvicible == false)
	{
		//val����
		mVal += mValInc;
	}

	//val������A�����𒴂������̏���
	if (mVal > mMaxval)
	{
		mVal = mMaxval;
		CanInvicible = true;
		//mValInc *= -1;
	}

	if (mVal < 0)
	{
		mVal = 0;
		mValInc *= -1;
	}
}

void Player::ChangeInvicible()
{
	//�X�y�[�X����͂������ɖ��G��ԂɂȂ�
	if (mVal==mMaxval&&CanInvicible==true&& CheckHitKey(KEY_INPUT_SPACE))
	{
		Invicible = true;
		CanInvicible = false;
	}
}

// �Q�[�W��`�悷��
// x,y �Q�[�W�`�捶����W�@width, height �Q�[�W��,����, �Q�[�W�ő�l, �Q�[�W�l, �Q�[�W���J���[
void Player::DrawInvicibleMeter(int x, int y, int width, int height, int max, int val, int color)
{
	int meterlen;
	int left = x - 2;
	int right = x + width + 2;
	int top = y - 2;
	int bottom = y + height + 2;

	meterlen = (int)((float)width * ((float)val / (float)max));


	//�̗̓Q�[�W�w�i����
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(left, top, right, bottom, 0xFF880000, TRUE);

	//�̗̓Q�[�W����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(x, y, x + meterlen, y + height, color, TRUE);

	//�̗̓Q�[�W�̘g��`��

	//�㉺����
	DrawLine(left, top, right, top, 0xFFFFFFFF);
	DrawLine(left, bottom, right, bottom, 0xFFFFFFFF);

	//���E�c��
	DrawLine(left, top, left, bottom, 0xFFFFFFFF);
	DrawLine(right, top, right, bottom, 0xFFFFFFFF);
}

void Player::DrawInvicible()
{
	DrawInvicibleMeter(650, 800, 300, 16, 150, mVal, 0xFF00AA00);
	//DrawGraph(600, 700, InvicibleGraph, true);
	DrawGraph(620, 700, InvicibleChargeGraph, true);
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