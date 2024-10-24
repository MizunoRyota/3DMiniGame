#include "DxLib.h"
#include <ctime>
#include<vector>
#include"Pallet.h"
#include"Bgm.h"
#include"game.h"
#include"HitChecker.h"
#include"Camera.h"
#include"SkyDome.h"
#include"Stage.h"
#include"Bus.h"
#include"Car.h"
#include"Coin.h"
#include"Puddle.h"
#include"NewsPaper.h"
#include"Player.h"
enum STATE
{
	STATE_INIT,
	STATE_TITLE,		// �^�C�g��.
	STATE_READY,        //����
	STATE_COUNTDOWN,	//�Q�[�����n�܂�܂ł̃J�E���g
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
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	//// �t�H���g�̕ύX
	ChangeFont("���m�xPOP v2", DX_CHARSET_DEFAULT);
	// �C���X�^���X����
	GameState* game = new GameState();
	BGM* bgm = new BGM();
	Camera* camera = new Camera();
	Skydome* skydome = new Skydome();
	HitChecker* hitcheck = new HitChecker;
	Stage* stage = new Stage();
	Player* player = new Player();
	Coin* coin = new Coin();
	Bus* bus = new Bus();
	Car* car = new Car();
	Puddle* puddle = new Puddle();
	NewsPaper* newspaper = new NewsPaper();
	// �G�X�P�[�v�L�[��������邩�E�C���h�E��������܂Ń��[�v
	LONGLONG frameTime = 0;

	bool DeadJudge = false;			//�Q�[���I�[�o�[�̔���
	bool EndJudge = false;			//�Q�[���I�[�o�[�ɑJ�ڂł��邩�ǂ����̔���
	bool debugPauseFlag = false;	//�|�[�Y����Ƃ��̕ϐ�
	int gameStatus = STATE_INIT;	//���݂̃Q�[�����̏��
	bool getcoin = false;
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
				car->Init();
				bus->Init();
				puddle->Init();
				player->PlayerInitialize();
				camera->Init();
				newspaper->Initialize();
				game->GameInitialize();
				//�Q�[����ԕω�
				gameStatus = STATE_TITLE;
			}

			//�^�C�g�����
			if (gameStatus == STATE_TITLE)
			{
				bgm->PlayGameTitle();
				skydome->SkydomeTitle();
				car->CarTitle();
				camera->GameTitle(player->GetPos());
				player->PlayerTitle();

				ClearDrawScreen();
				//�`��
				game->GameTitle();
				skydome->SkydomeDraw();
				stage->GameDraw();
				car->GameDraw();
				player->Draw();
				game->HighScoreDraw();

				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					WaitTimer(200);
					ClearDrawScreen();
					car->Init();
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
				player->Draw();
				bus->GameDraw();
				car->GameDraw();
				game->GameReady();
				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE)&&game->GetReadyPhase3())
				{
					ClearDrawScreen();
					gameStatus = STATE_COUNTDOWN;
				}
			}
			//�Q�[�����n�܂�܂ł̃J�E���g�_�E��
			if (gameStatus == STATE_COUNTDOWN)
			{
				skydome->SkydomeDraw();
				stage->GameDraw();
				player->Draw();
				bus->GameDraw();
				car->GameDraw();
				// ������\��
				for (int i = 1; i <= 4; i++)
				{

					//�`��
					ClearDrawScreen();

					skydome->SkydomeDraw();
					stage->GameDraw();
					player->Draw();
					bus->GameDraw();
					car->GameDraw();
					if (i < 4)
					{
						SetFontSize(300);
						DrawFormatString(680, 400, Pallet::AliceBlue.GetHandle(), "%d", 4 - i);
					}
					else if (i==4)
					{
						SetFontSize(300);
						DrawFormatString(600, 400, Pallet::AliceBlue.GetHandle(), "GO");
					}
					// ����ʂ̓��e��\��ʂɔ��f������
					ScreenFlip();
						WaitTimer(700); // 1�b�ҋ@
				}
				gameStatus = STATE_GAME;
			}
			//�Q�[����
			if (gameStatus == STATE_GAME)
			{
				bgm->StopGameTitle();
				bgm->PlayGameSound();
				//�Q�[���V�[���̐���
				game->GameUpdate();

				// �v���C���[����
				player->PlayerUpdate();
				player->MeterMove();

				// �J�����̐���
				camera->Update(player->GetPos());
				// �X�J�C�h�[������
				skydome->SkydomeUpdate();

				//�X�e�[�W����
				stage->Update();

				//��Q������
				car->Update(game->GetObstaclePattern(), game->GetObstacleSpeed());
				bus->Update(game->GetObstaclePattern(), game->GetObstacleSpeed());
				puddle->Update(game->GetObstacleSpeed(), game->GetObstaclePattern());
				newspaper->Update();

				////�R�C������
				if (hitcheck->CoinCheck(player->GetPos(), coin->GetPos()))
				{
						game->ScoreUp();//�X�R�A�㏸
						coin->CoinMove();//
				}
				else
				{

					game->CrushCoin();
					coin->Update(car->GetPos());
				}

				hitcheck->BusCheck(player->GetPos(), bus->GetPos(),player->GetInvicible());//�o�X�Ƃ̐ڐG�m�F
				hitcheck->BusCheck(player->GetPos(), bus->GetPos2(), player->GetInvicible());//�o�X�Ƃ̐ڐG�m�F
				if(hitcheck->NewsPaperCheck(player->GetPos(), newspaper->GetPos(), player->GetInvicible() == true))
				{
					newspaper->CrushInvicible();
				}
				if (hitcheck->NewsPaperCheck(player->GetPos(), newspaper->GetPos(), player->GetInvicible() == false))
				{
					newspaper->ChangeCrush();
				}
				DeadJudge = hitcheck->GetDead();//�Q�[���I�[�o�[�̔���
				if (hitcheck->CarCheck(player->GetPos(), car->GetPos(), player->GetInvicible()))//���ʎ����ԂƂ̔���
				{
					DeadJudge = hitcheck->DeadJudge();
				}
				hitcheck->PuddleCheck(player->GetPos(), puddle->GetPos(), player, player->GetInvicible());

				// ��ʂ�����������
				ClearDrawScreen();

				// �`��
				skydome->SkydomeDraw();
				stage->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				puddle->Draw();
				coin->Draw();
				newspaper->Draw();
				player->Draw();
				//player->DrawInvicible();
				game->Draw();

				//hitcheck->circleDraw();

				if (DeadJudge == true)
				{
					bgm->StopGameSound();
					bgm->PlayGameEnd();
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
				bus->GameDraw();
				car->GameDraw();
				player->Draw();
				if (EndJudge == false)
				{
					gameStatus = STATE_GAMEOVER;
				}
			}

			//�Q�[�����U���g
			if (gameStatus == STATE_GAMEOVER)
			{
				player->PlayerGameOver();
				// ��ʂ�����������
				ClearDrawScreen();
				//�`��
				skydome->SkydomeDraw();
				stage->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				player->Draw();
				game->GameOver();
				// �Q�[����ԕω�
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					WaitTimer(80);
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