#include<DxLib.h>
#include"Pallet.h"
#include"game.h"
#include"Box.h"
GameState::GameState()
{
	Controller = LoadGraph("data/texture/title/setumei.png");
	PaintHandle[0] = LoadGraph("data/texture/GameOver/GreenPaint.png");
	PaintHandle[1] = LoadGraph("data/texture/GameOver/RedPaint.png");
	PaintHandle[2] = LoadGraph("data/texture/GameOver/SkybluePaint.png");
	PaintHandle[3] = LoadGraph("data/texture/GameOver/YellowPaint.png");

	HighScore = 0;
	Score = 0;
}

GameState::~GameState()
{

}

void GameState::GameInitialize()
{
	Score = 0;
}

void GameState::GameTitle()
{
	SetFontSize(95);
    DrawFormatString(370, 160, Pallet::AliceBlue.GetHandle(), "City Sprint", true);
	DrawFormatString(200, 670, Pallet::AliceBlue.GetHandle(), "START SPACE KEY");
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
	DrawFormatString(600, 270, Pallet::AliceBlue.GetHandle(), "�@�@�`���[�g���A��\n\n�����ѕ�:�����ňړ����ŃW�����v");
	DrawFormatString(600, 670, Pallet::AliceBlue.GetHandle(), "START SPACE KEY");

}

void GameState::GameUpdate()
{
	Score++;
}

void GameState::ScoreDraw()
{
	SetFontSize(60);
	DrawFormatString(1100, 70, Pallet::AliceBlue.GetHandle(), "SCORE::%d", Score);
}

void GameState::HighScoreDraw()
{
	SetFontSize(40);
	if (HighScore<=Score)
	{
		HighScore = Score;
	}
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
	DrawGraph(150, 200, PaintHandle[0], true);
	DrawGraph(1000, 300, PaintHandle[1], true);
	DrawGraph(1100, 550, PaintHandle[2], true);
	DrawGraph(300, 600, PaintHandle[3], true);

	DrawFormatString(600, 340, Pallet::AliceBlue.GetHandle(), "GAME OVER");
	DrawFormatString(600, 500, Pallet::AliceBlue.GetHandle(), "HIGH SCORE %d", HighScore);
	DrawFormatString(580, 560, Pallet::AliceBlue.GetHandle(), "YOUR SCORE %d", Score);

}