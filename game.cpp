#include<DxLib.h>
#include"Pallet.h"
#include"game.h"
#include"Box.h"
GameState::GameState()
{
	Controller = LoadGraph("data/texture/title/setumei.png");
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
    DrawFormatString(370, 160, Pallet::AliceBlue.GetHandle(), "TITLE", true);
	DrawFormatString(200, 670, Pallet::AliceBlue.GetHandle(), "START SPACE KEY");
}

void GameState::GameReady()
{
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 200, 1600, 800, Pallet::Black.GetHandle(), TRUE);
	DrawBox(0, 210, 1600, 220, Pallet::Aqua.GetHandle(), TRUE);
	DrawBox(0, 780, 1600, 790, Pallet::Aqua.GetHandle(), TRUE);

	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(150, 400, Controller, true);
	SetFontSize(50);
	DrawFormatString(600, 270, Pallet::AliceBlue.GetHandle(), "　　チュートリアル\n\n操作方法:←→で移動↑でジャンプ");
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

	DrawFormatString(600, 340, Pallet::AliceBlue.GetHandle(), "HighScore %d", HighScore);

	DrawFormatString(600, 500, Pallet::AliceBlue.GetHandle(), "SCORE::%d", Score);

}