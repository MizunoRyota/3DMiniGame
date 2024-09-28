#include "DxLib.h"
#include <ctime>
#include<vector>
#include"Pallet.h"
#include"game.h"
#include"HitChecker.h"
#include"Camera.h"
#include"SkyDome.h"
#include"Stage.h"
#include"Stage2.h"
#include"Bus.h"
#include"Car.h"
#include"Coin.h"
#include"Puddle.h"
#include"Player.h"
enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// �^�C�g��.
	STATE_READY,        //����
	STATE_GAME,			// �Q�[����.
	STATE_END,			//����Ă�����
	STATE_GAMEOVER,		// �Q�[���I�[�o�[.
};
/// <summary>
/// ���C���֐�
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	srand(static_cast<unsigned int>(time(NULL)));  // �����_���V�[�h��ݒ�

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return -1;	// �G���[���N�����璼���ɏI��
	}

	// ��ʃ��[�h�̃Z�b�g
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// ����ʂ�`��Ώۂɂ���
	SetUseZBufferFlag(TRUE);		// �y�o�b�t�@���g�p����
	SetWriteZBufferFlag(TRUE);		// �y�o�b�t�@�ւ̏������݂��s��
	SetUseBackCulling(TRUE);		// �o�b�N�J�����O���s��

	// 1�b�Ԃɏ�������t���[������ݒ�(60FPS)
		const int TARGET_FPS = 60;
	const int FRAME_TIME = 1000 / TARGET_FPS;  // 1�t���[��������̗��z�I�Ȏ��� (�~���b)

	// ********** �t�H���g�̃��[�h **********
	LPCSTR font_path = "Data/Font/Mimi_font-Regular.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//// �t�H���g�̕ύX
	ChangeFont("Mimi_font", DX_CHARSET_DEFAULT);
	// �C���X�^���X����
	GameState* game = new GameState(); 
	Camera* camera = new Camera();
	Skydome* skydome = new Skydome();
	HitChecker* hitcheck = new HitChecker;
	Stage* stage = new Stage();
	Stage2* stage2 = new Stage2();
	Player* player = new Player();
	Coin* coin = new Coin();
	Bus* bus = new Bus();
	Car* car = new Car();
	Puddle* puddle = new Puddle();
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;

	bool DeadJudge = false;			//�Q�[���I�[�o�[�̔���
	bool EndJudge = false;
	bool debugPauseFlag = false;	//�|�[�Y����Ƃ��̕ϐ�
	int gameStatus = STATE_INIT;	//���݂̃Q�[�����̏��

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// �t���[���J�n���̎��Ԃ��擾
		int startTime = GetNowCount();
		// �ڂ��񂨂�����
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// �ڂ��񂨂�����
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//�S�Ă̏�����
			if (gameStatus == STATE_INIT)
			{
				DeadJudge = false;
				EndJudge = true;
				hitcheck->Init();
				stage->Init();
				stage2->Init();
				car->Init();
				bus->Init();
				puddle->Init();
				player->PlayerInitialize();
				camera->Init();
				//�Q�[����ԕω�
				gameStatus = STATE_TITLE;
			}

			//�^�C�g�����
			if (gameStatus == STATE_TITLE)
			{
				skydome->SkydomeTitle();
				car->CarTitle();
				camera->GameTitle(player->GetPos());
				player->PlayerTitle();
				ClearDrawScreen();

				game->GameTitle();
				skydome->SkydomeDraw();
				stage->GameDraw();
				stage2->GameDraw();
				car->GameDraw();
				player->Draw();
				game->HighScoreDraw();

				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					WaitTimer(200);
					ClearDrawScreen();
					gameStatus = STATE_READY;
				}

			}
			//�`���[�g���A�����
			if (gameStatus == STATE_READY)
			{
				car->Init();
				bus->Init();
				skydome->SkydomeUpdate();
				camera->ReadyUpdate(player->GetPos());
				player->PlayerUpdate();
				ClearDrawScreen();
				//�`��
				skydome->SkydomeDraw();
				stage->GameDraw();
				stage2->GameDraw();
				player->Draw();
				game->GameReady();

				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					gameStatus = STATE_GAME;
				}
			}
			//�Q�[����
			if (gameStatus == STATE_GAME)
			{
				//�Q�[���V�[���̐���
				game->GameUpdate();

				// �v���C���[����
				player->PlayerUpdate();
				// �J�����̐���
				camera->Update(player->GetPos());
				// �X�J�C�h�[������
				skydome->SkydomeUpdate();

				//�X�e�[�W����
				stage->Update();
				stage2->Update();

				//��Q������
				bus->Update(game->GetObstaclePattern());
				car->Update(game->GetObstaclePattern());
				puddle->Update();
				//�R�C������
				coin->Update(bus->GetPos(),car->GetPos());

				hitcheck->BusCheck(player->GetPos(), bus->GetPos());//�o�X�g�̐ڐG�m�F
				DeadJudge = hitcheck->GetDead();//�Q�[���I�[�o�[�̔���
				if (hitcheck->CarCheck(player->GetPos(), car->GetPos()))//���ʎ����ԂƂ̔���
				{
					DeadJudge = hitcheck->DeadJudge();
				}
				hitcheck->PuddleCheck(player->GetPos(), puddle->GetPos(),player);

				// ��ʂ�����������
				ClearDrawScreen();

				// �`��
				skydome->SkydomeDraw();
				stage->GameDraw();
				stage2->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				puddle->Draw();
				coin->Draw();
				player->Draw();
				game->ScoreDraw();

				hitcheck->circleDraw();

				if (DeadJudge==true)
				{
					gameStatus = STATE_END;
				}
			}
			//�Q�[���I�[�o�[���o
			if (gameStatus == STATE_END)
			{

				camera->GameEnd(player->GetPos());
				EndJudge = player->PlayerEnd();
				// ��ʂ�����������
				ClearDrawScreen();
				skydome->SkydomeDraw();
				stage->GameDraw();
				stage2->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				player->Draw();
				if (EndJudge==false)
				{
					gameStatus = STATE_GAMEOVER;
				}
			}

			//�Q�[�����U���g
			if (gameStatus == STATE_GAMEOVER)
			{
				// ��ʂ�����������
				ClearDrawScreen();

				//�`��

				skydome->SkydomeDraw();
				stage->GameDraw();
				stage2->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				player->Draw();
				game->GameOver();
				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					gameStatus = STATE_INIT;
				}
			}
		}
		// ����ʂ̓��e��\��ʂɔ��f������
		ScreenFlip();

		// �t���[���I�����̎��Ԃ��擾
		int endTime = GetNowCount();

		// �t���[���������Ԃ��v�Z
		int elapsedTime = endTime - startTime;

		// �����������I������ꍇ�A�c�莞�ԑҋ@����
		if (elapsedTime < FRAME_TIME)
		{
			// �c�莞�ԑҋ@
			WaitTimer(FRAME_TIME - elapsedTime);
		}
	}

	// ��n��
	// �c�w���C�u�����̌�n��
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}