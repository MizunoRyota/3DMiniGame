#include<DxLib.h>
#include"Pallet.h"
#include"Box.h"
#include"game.h"
GameState::GameState()
{
	Controller = LoadGraph("data/texture/title/setumei.png");
	TitleHandle = LoadGraph("data/texture/title/TitleLogo.png");
	PaintHandle[0] = LoadGraph("data/texture/GameOver/GreenPaint.png");
	PaintHandle[1] = LoadGraph("data/texture/GameOver/RedPaint.png");
	PaintHandle[2] = LoadGraph("data/texture/GameOver/SkybluePaint.png");
	PaintHandle[3] = LoadGraph("data/texture/GameOver/YellowPaint.png");
	ObstacleSpeed = 0.5;
	ObstaclePattern = 0;
	HighScore = 0;
	Score = 0;
}

GameState::~GameState()
{
}

void GameState::GameInitialize()
{
	if (HighScore <= Score)
	{
		HighScore = Score;
	}
	Score = 0;
	ObstacleSpeed = 0.5;
}

void GameState::GameTitle()
{
	SetFontSize(95);
	DrawGraph(100, 150, TitleHandle,true);
	DrawFormatString(150, 750, Pallet::AliceBlue.GetHandle(), "START SPACE KEY");
}

void GameState::GameReady()
{
	// ��F�����x50%�̔��F�̎l�p�`��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 200, 1600, 800, Pallet::Black.GetHandle(), TRUE);
	DrawBox(0, 210, 1600, 220, Pallet::Aqua.GetHandle(), TRUE);
	DrawBox(0, 780, 1600, 790, Pallet::Aqua.GetHandle(), TRUE);

	// �`�惂�[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(150, 400, Controller, true);
	SetFontSize(50);
	DrawFormatString(600, 270, Pallet::AliceBlue.GetHandle(), "�@�@�`���[�g���A��\n\n  �����ňړ����ŃW�����v");
	DrawFormatString(600, 450, Pallet::AliceBlue.GetHandle(), "�@�@�݂����܂�ɂ�����Ɠ����ɂ����Ȃ邼");
	DrawFormatString(600, 500, Pallet::AliceBlue.GetHandle(), "�@�@�V�����ɓ�����Ǝ��E���Ղ��邼");
	DrawFormatString(600, 670, Pallet::AliceBlue.GetHandle(), "START SPACE KEY");

}

void GameState::GameUpdate()
{
	ObstacleSpeedUpdate();
	ObstacleConfiguration();
	Score++;
}

void GameState::ObstacleSpeedUpdate()
{
	if (Score>=1000)
	{
		ObstacleSpeed = 0.7f;
	}
	else if (Score>=2000)
	{
		ObstacleSpeed = 0.9f;
	}
	else if (Score>=3000)
	{
		ObstacleSpeed = 1.1f;
	}
	else if (Score>=4000)
	{
		ObstacleSpeed = 1.3f;
	}
	else if (Score>=5000)
	{
		ObstacleSpeed = 1.5f;
	}
	else if (Score >= 6000)
	{
		ObstacleSpeed = 1.7f;
	}
	else if (Score >= 7000)
	{
		ObstacleSpeed = 1.9f;
	}
}

void GameState::ObstacleConfiguration()
{
	if (IsObstacle=true)
	{
		ObstaclePattern = rand() % 4;
	}
}

void GameState::ScoreUp()
{
	Score = Score + 100;
}

void GameState::ScoreDraw()
{
	// ��F�����x50%�̔��F�̎l�p�`��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 0, 1600, 100, Pallet::Black.GetHandle(), TRUE);

	// �`�惂�[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetFontSize(60);
	DrawFormatString(600, 20, Pallet::LemonYellow.GetHandle(), "SCORE::%d", Score);
}

void GameState::HighScoreDraw()
{
	SetFontSize(40);

	DrawFormatString(1050, 600, Pallet::AliceBlue.GetHandle(), "HighScore %d", HighScore);
}

void GameState::GameOver()
{
	SetFontSize(60);
	// ��F�����x50%�̔��F�̎l�p�`��`�悷��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 200, 1600, 800, Pallet::Black.GetHandle(), TRUE);
	DrawBox(0, 210, 1600, 220, Pallet::Aqua.GetHandle(), TRUE);
	DrawBox(0, 780, 1600, 790, Pallet::Aqua.GetHandle(), TRUE);

	// �`�惂�[�h�����ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(50);
	DrawGraph(100, 200, PaintHandle[0], true);
	DrawGraph(1000, 300, PaintHandle[1], true);
	DrawGraph(1200, 550, PaintHandle[2], true);
	DrawGraph(300, 400, PaintHandle[3], true);

	DrawFormatString(600, 340, Pallet::AliceBlue.GetHandle(), "GAME OVER");
	DrawFormatString(580, 500, Pallet::AliceBlue.GetHandle(), "YOUR SCORE %d", Score);
	DrawFormatString(600, 670, Pallet::AliceBlue.GetHandle(), "TITLE SPACE KEY");

}