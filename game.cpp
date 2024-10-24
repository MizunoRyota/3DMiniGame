#include<DxLib.h>
#include"Pallet.h"
#include"Box.h"
#include"game.h"
GameState::GameState()
{
	Controller = LoadGraph("data/texture/title/setumei.png");
	TitleHandle = LoadGraph("data/texture/title/TitleLogo.png");
	PuddleTutorialHandle= LoadGraph("data/texture/game/PuddleTutorial2.png");
	LeftArrowHandle = LoadGraph("data/texture/title/leftButton.png");
	RightArrowHandle = LoadGraph("data/texture/title/RightButton.png");
	SpaceHandle = LoadGraph("data/texture/title/SPACE.png");
	RedSpaceHandle = LoadGraph("data/texture/title/RedSPACE.png");
	NewsPaperTutorialHandle= LoadGraph("data/texture/game/新聞紙.png");
	ArrowHandle = LoadGraph("data/texture/title/Arrow.png");
	PaintHandle[0] = LoadGraph("data/texture/GameOver/GreenPaint.png");
	PaintHandle[1] = LoadGraph("data/texture/GameOver/RedPaint.png");
	PaintHandle[2] = LoadGraph("data/texture/GameOver/SkybluePaint.png");
	PaintHandle[3] = LoadGraph("data/texture/GameOver/YellowPaint.png");
	ArrowPosX = 630;
	ArrowSpeed = 0.5f;
	ColorChangeSpeed = 1;
	IsCoin = false;
	ArrowMove = false;
	ReadyPhase1 = true;
	ReadyPhase2 = false;
	ReadyPhase3 = false;
	ObstacleSpeed = 0.3;
	ObstaclePattern = 0;
	HighScore = 0;
	Score = 0;
}

GameState::~GameState()
{
	//処理なし
}

void GameState::GameInitialize()
{
	ReadyPhase1 = true;		//チュートリアル画面１
	ReadyPhase2 = false;	//チュートリアル画面２
	ReadyPhase3 = false;	//チュートリアル画面３
	//ハイスコアの設定
	if (HighScore <= Score)
	{
		HighScore = Score;
	}
	//スコアを初期化
	Score = 0;
	//障害物のスピードの初期化
	ObstacleSpeed = 0.5;
}

void GameState::GameTitle()
{
	SetFontSize(95);
	DrawGraph(100, 150, TitleHandle,true);
	DrawFormatString(150, 750, Pallet::AliceBlue.GetHandle(), "PRESS SPACE KEY");
}

void GameState::MoveArrow()
{
	if (ArrowMove==false)
	{
		ArrowPosX += ArrowSpeed;
	}
	else
	{
		ArrowPosX -= ArrowSpeed;
	}
	if (ArrowPosX>=640)
	{
		ArrowSpeed = 1.0f;
	}
	else
	{
		ArrowSpeed = 0.5f;
	}
	if (ArrowPosX>=650)
	{
		ArrowMove = true;
	}
	else if(ArrowPosX <= 630)
	{
		ArrowMove = false;
	}
}

void GameState::GameReady()
{
	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 100, 1600, 800, Pallet::Black.GetHandle(), TRUE);
	DrawBox(0, 110, 1600, 120, Pallet::Aqua.GetHandle(), TRUE);
	DrawBox(0, 780, 1600, 790, Pallet::Aqua.GetHandle(), TRUE);
	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//矢印の更新
	MoveArrow();
	//チュートリアル画面１
	if (ReadyPhase1 == true)
	{
		SetFontSize(50);
		DrawFormatString(600, 150, Pallet::AliceBlue.GetHandle(), "チュートリアル");
		DrawFormatString(700, 300, Pallet::AliceBlue.GetHandle(), "・・・左移動");
		DrawFormatString(700, 450, Pallet::AliceBlue.GetHandle(), "・・・右移動");
		DrawFormatString(700, 580, Pallet::AliceBlue.GetHandle(), "・・・ジャンプ");
				
		DrawGraph(ArrowPosX, 700, ArrowHandle, true);
		DrawGraph(700, 670, SpaceHandle, true);
		DrawGraph(480, 550, RedSpaceHandle, true);
		DrawGraph(500, 250, LeftArrowHandle, true);
		DrawGraph(500, 400, RightArrowHandle, true);
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			WaitTimer(80);
			ReadyPhase1 = false;
			ReadyPhase2 = true;
		}
	}
	//チュートリアル画面２
	else if (ReadyPhase2 == true)
	{
		DrawFormatString(600, 400, Pallet::AliceBlue.GetHandle(), "  地面のタールにあたると\n  動きにくくなるぞ");
		DrawGraph(ArrowPosX, 700, ArrowHandle, true);
		DrawGraph(700, 670, SpaceHandle, true);
		DrawGraph(100, 350, PuddleTutorialHandle, true);
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			WaitTimer(80);
			ReadyPhase2 = false;
			ReadyPhase3 = true;
		}
	}
	//チュートリアル画面３
	else if (ReadyPhase3 == true)
	{
		DrawFormatString(600, 400, Pallet::AliceBlue.GetHandle(), "新聞紙に当たると視界が遮られるぞ");
		DrawGraph(ArrowPosX, 700, ArrowHandle, true);
		DrawGraph(700, 670, SpaceHandle, true);
		DrawGraph(50, 300, NewsPaperTutorialHandle, true);
	}
}

void GameState::CountDown()
{
	// 数字を表示
	for (int i = 1; i <= 4; i++)
	{
		if (i < 4)
		{
			SetFontSize(100);
			DrawFormatString(100, 200,Pallet::AliceBlue.GetHandle(), "%d", 4 - i);
			WaitTimer(500); // 1秒待機
		}
		else if (true)
		{
			DrawFormatString(100, 200, Pallet::AliceBlue.GetHandle(), "GO");
			WaitTimer(500); // 1秒待機
		}
	}
}

void GameState::GameUpdate()
{
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		Score=5000;
	}
	//障害物のスピード更新
	ObstacleSpeedUpdate();
	//障害物のパターン設定
	ObstacleConfiguration();
	Score++;
}

void GameState::ObstacleSpeedUpdate()
{
	if (Score>=1000&& Score <= 2000)
	{
		ObstacleSpeed = 0.6f;
	} 
	else if (Score>=2000&&Score <= 3000)
	{
		ObstacleSpeed = 0.65f;
	}
	else if (Score>=3000 && Score <= 4000)
	{
		ObstacleSpeed = 0.7f;
	}
	else if (Score>=4000 && Score <= 5000)
	{
		ObstacleSpeed = 0.75f;
	}
	else if (Score>=5000 && Score <= 6000)
	{
		ObstacleSpeed = 0.8f;
	}
}

void GameState::ObstacleConfiguration()
{
	//障害物のパターン設定
	if (IsObstacle=true)
	{
		ObstaclePattern = rand() % 8;
	}
}

void GameState::SpeedUpDraw()
{
	if (Score >= 3000 && Score <= 3500)
	{
		SetFontSize(80);
		DrawFormatString(100, 300, Pallet::AliceBlue.GetHandle(), "SPEED UP!");
	}
	if (Score >= 5000 && Score <= 5500)
	{
		SetFontSize(80);
		DrawFormatString(100, 300, Pallet::AliceBlue.GetHandle(), "SPEED UP!");
	}
}

void GameState::CrushCoin()
{
	IsCoin = false;
}

void GameState::ScoreUp()
{
	if (!IsCoin)
	{
		Score = Score + 200;
		IsCoin = true;
	}
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

void GameState::ChangeScoreColor()
{
	// 色を変化させるロジック
	ScoreColorR += ColorChangeSpeed;
	ScoreColorG += 2;
	ScoreColorB += 3;

	if (ScoreColorR > 255) {
		ScoreColorR = 0; // 赤が255を超えたら0にリセット
		if (ScoreColorG > 255) {
			ScoreColorG = 0; // 緑が255を超えたら0にリセット
			if (ScoreColorB > 255) {
				ScoreColorB = 0; // 青が255を超えたら0にリセット
			}
		}
	}
}

void GameState::Draw()
{
	ScoreDraw();
	SpeedUpDraw();
}

void GameState::GameOver()
{

	//矢印の更新
	MoveArrow();

	// 例：透明度50%の白色の四角形を描画する
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawBox(0, 200, 1600, 800, Pallet::Black.GetHandle(), TRUE);
	DrawBox(0, 210, 1600, 220, Pallet::Aqua.GetHandle(), TRUE);
	DrawBox(0, 780, 1600, 790, Pallet::Aqua.GetHandle(), TRUE);

	// 描画モードを元に戻す
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	ChangeScoreColor();

	// 色を取得
	int Color = GetColor(ScoreColorR, ScoreColorG, ScoreColorB);
	DrawGraph(100, 200, PaintHandle[0], true);	//緑
	DrawGraph(1100, 200, PaintHandle[1], true);	//赤
	DrawGraph(1300, 550, PaintHandle[2], true);	//青
	DrawGraph(200, 600, PaintHandle[3], true);	//黄
	SetFontSize(70);
	DrawFormatString(600, 340, Pallet::AliceBlue.GetHandle(), "GAME OVER");
	SetFontSize(50);
	DrawFormatString(500, 520, Pallet::AliceBlue.GetHandle(), "YOUR SCORE");
	SetFontSize(75);
	DrawFormatString(800, 500, Color, " %d", Score);

	DrawGraph(ArrowPosX, 700, ArrowHandle, true);
	DrawGraph(700, 670, SpaceHandle, true);
}