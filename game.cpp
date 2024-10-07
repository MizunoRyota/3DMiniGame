﻿#include<DxLib.h>
#include"Pallet.h"
#include"Box.h"
#include"game.h"
GameState::GameState()
{
	Controller = LoadGraph("data/texture/title/setumei.png");
	TitleHandle = LoadGraph("data/texture/title/TitleLogo.png");
	PuddleTutorialHandle= LoadGraph("data/texture/game/PuddleTutorial2.png");
	NewsPaperTutorialHandle= LoadGraph("data/texture/game/GreenPaint.png");
	PaintHandle[0] = LoadGraph("data/texture/GameOver/GreenPaint.png");
	PaintHandle[1] = LoadGraph("data/texture/GameOver/RedPaint.png");
	PaintHandle[2] = LoadGraph("data/texture/GameOver/SkybluePaint.png");
	PaintHandle[3] = LoadGraph("data/texture/GameOver/YellowPaint.png");
	ObstacleSpeed = 0.3;
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
	DrawFormatString(150, 750, Pallet::AliceBlue.GetHandle(), "PRESS SPACE KEY");
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
	//DrawGraph(150, 400, Controller, true);
	//DrawGraph(150, 400, PuddleTutorialHandle, true);

	SetFontSize(50);
	DrawFormatString(600, 270, Pallet::AliceBlue.GetHandle(), "　　チュートリアル\n\n  ←→で移動↑でジャンプ");
	DrawFormatString(500, 450, Pallet::AliceBlue.GetHandle(), "　　みずたまりにあたると動きにくくなるぞ");
	DrawFormatString(500, 500, Pallet::AliceBlue.GetHandle(), "　　新聞紙に当Rたると視界が遮られるぞ");
	DrawFormatString(600, 670, Pallet::AliceBlue.GetHandle(), "PRESS SPACE KEY");
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
		ObstacleSpeed = 0.4f;
	} 
	else if (Score>=2000)
	{
		ObstacleSpeed = 0.5f;
	}
	else if (Score>=3000)
	{
		ObstacleSpeed = 0.6f;
	}
	else if (Score>=4000)
	{
		ObstacleSpeed = 0.7f;
	}
	else if (Score>=5000)
	{
		ObstacleSpeed = 0.8f;
	}
	else if (Score >= 6000)
	{
		ObstacleSpeed = 0.9f;
	}
	else if (Score >= 7000)
	{
		ObstacleSpeed = 1.0f;
	}
	else if (Score>=8000)
	{
		ObstacleSpeed = 1.1f;
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

	DrawFormatString(800, 20, Pallet::LemonYellow.GetHandle(), "SCORE UP", Score);
	Score = Score + 100;
}

void GameState::ScoreDraw()
{
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 0, 1600, 100, Pallet::Black.GetHandle(), TRUE);

	// 描画モードを元に戻す
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
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 200, 1600, 800, Pallet::Black.GetHandle(), TRUE);
	DrawBox(0, 210, 1600, 220, Pallet::Aqua.GetHandle(), TRUE);
	DrawBox(0, 780, 1600, 790, Pallet::Aqua.GetHandle(), TRUE);

	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetFontSize(50);
	DrawGraph(100, 200, PaintHandle[0], true);	//緑
	DrawGraph(1100, 200, PaintHandle[1], true);	//赤
	DrawGraph(1300, 550, PaintHandle[2], true);	//青
	DrawGraph(200, 600, PaintHandle[3], true);	//黄
	SetFontSize(70);
	DrawFormatString(600, 340, Pallet::AliceBlue.GetHandle(), "GAME OVER");
	DrawFormatString(580, 500, Pallet::AliceBlue.GetHandle(), "YOUR SCORE %d", Score);
	DrawFormatString(600, 670, Pallet::AliceBlue.GetHandle(), "PRESS SPACE KEY");
}