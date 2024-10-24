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
	STATE_TITLE,		// タイトル.
	STATE_READY,        //準備
	STATE_COUNTDOWN,	//ゲームが始まるまでのカウント
	STATE_GAME,			// ゲーム中.
	STATE_END,			//やられている状態
	STATE_GAMEOVER,		// ゲームオーバー.
};
/// <summary>
/// メイン関数
/// </summary>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	srand(static_cast<unsigned int>(time(NULL)));  // ランダムシードを設定

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	ChangeWindowMode(TRUE);
	SetGraphMode(1600, 900, 16);

	SetDrawScreen(DX_SCREEN_BACK);	// 裏画面を描画対象にする
	SetUseZBufferFlag(TRUE);		// Ｚバッファを使用する
	SetWriteZBufferFlag(TRUE);		// Ｚバッファへの書き込みを行う
	SetUseBackCulling(TRUE);		// バックカリングを行う

	// 1秒間に処理するフレーム数を設定(60FPS)
	const int TARGET_FPS = 60;
	const int FRAME_TIME = 1000 / TARGET_FPS;  // 1フレームあたりの理想的な時間 (ミリ秒)

	// ********** フォントのロード **********
	LPCSTR font_path = "Data/Font/LightNovelPOPv2.otf"; // 読み込むフォントファイルのパス
	//// フォントの変更
	ChangeFont("ラノベPOP v2", DX_CHARSET_DEFAULT);
	// インスタンス生成
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
	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;

	bool DeadJudge = false;			//ゲームオーバーの判定
	bool EndJudge = false;			//ゲームオーバーに遷移できるかどうかの判定
	bool debugPauseFlag = false;	//ポーズするときの変数
	int gameStatus = STATE_INIT;	//現在のゲーム中の状態
	bool getcoin = false;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// フレーム開始時の時間を取得
		int startTime = GetNowCount();
		// ぼたんおしたら
		if (CheckHitKey(KEY_INPUT_P))
		{
			debugPauseFlag = true;
		}
		while (debugPauseFlag)
		{
			WaitTimer(2);
			// ぼたんおしたら
			if (CheckHitKey(KEY_INPUT_O))
			{
				debugPauseFlag = false;
			}
		}

		if (debugPauseFlag == false)
		{
			//全ての初期化
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
				//ゲーム状態変化
				gameStatus = STATE_TITLE;
			}

			//タイトル画面
			if (gameStatus == STATE_TITLE)
			{
				bgm->PlayGameTitle();
				skydome->SkydomeTitle();
				car->CarTitle();
				camera->GameTitle(player->GetPos());
				player->PlayerTitle();

				ClearDrawScreen();
				//描画
				game->GameTitle();
				skydome->SkydomeDraw();
				stage->GameDraw();
				car->GameDraw();
				player->Draw();
				game->HighScoreDraw();

				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					WaitTimer(200);
					ClearDrawScreen();
					car->Init();
					gameStatus = STATE_READY;
				}
			}
			//チュートリアル画面
			if (gameStatus == STATE_READY)
			{
				car->Init();
				bus->Init();
				skydome->SkydomeUpdate();
				camera->ReadyUpdate(player->GetPos());
				player->PlayerUpdate();
				ClearDrawScreen();
				//描画
				skydome->SkydomeDraw();
				stage->GameDraw();
				player->Draw();
				bus->GameDraw();
				car->GameDraw();
				game->GameReady();
				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE)&&game->GetReadyPhase3())
				{
					ClearDrawScreen();
					gameStatus = STATE_COUNTDOWN;
				}
			}
			//ゲームが始まるまでのカウントダウン
			if (gameStatus == STATE_COUNTDOWN)
			{
				skydome->SkydomeDraw();
				stage->GameDraw();
				player->Draw();
				bus->GameDraw();
				car->GameDraw();
				// 数字を表示
				for (int i = 1; i <= 4; i++)
				{

					//描画
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
					// 裏画面の内容を表画面に反映させる
					ScreenFlip();
						WaitTimer(700); // 1秒待機
				}
				gameStatus = STATE_GAME;
			}
			//ゲーム中
			if (gameStatus == STATE_GAME)
			{
				bgm->StopGameTitle();
				bgm->PlayGameSound();
				//ゲームシーンの制御
				game->GameUpdate();

				// プレイヤー制御
				player->PlayerUpdate();
				player->MeterMove();

				// カメラの制御
				camera->Update(player->GetPos());
				// スカイドーム制御
				skydome->SkydomeUpdate();

				//ステージ制御
				stage->Update();

				//障害物制御
				car->Update(game->GetObstaclePattern(), game->GetObstacleSpeed());
				bus->Update(game->GetObstaclePattern(), game->GetObstacleSpeed());
				puddle->Update(game->GetObstacleSpeed(), game->GetObstaclePattern());
				newspaper->Update();

				////コイン制御
				if (hitcheck->CoinCheck(player->GetPos(), coin->GetPos()))
				{
						game->ScoreUp();//スコア上昇
						coin->CoinMove();//
				}
				else
				{

					game->CrushCoin();
					coin->Update(car->GetPos());
				}

				hitcheck->BusCheck(player->GetPos(), bus->GetPos(),player->GetInvicible());//バスとの接触確認
				hitcheck->BusCheck(player->GetPos(), bus->GetPos2(), player->GetInvicible());//バスとの接触確認
				if(hitcheck->NewsPaperCheck(player->GetPos(), newspaper->GetPos(), player->GetInvicible() == true))
				{
					newspaper->CrushInvicible();
				}
				if (hitcheck->NewsPaperCheck(player->GetPos(), newspaper->GetPos(), player->GetInvicible() == false))
				{
					newspaper->ChangeCrush();
				}
				DeadJudge = hitcheck->GetDead();//ゲームオーバーの判定
				if (hitcheck->CarCheck(player->GetPos(), car->GetPos(), player->GetInvicible()))//普通自動車との判定
				{
					DeadJudge = hitcheck->DeadJudge();
				}
				hitcheck->PuddleCheck(player->GetPos(), puddle->GetPos(), player, player->GetInvicible());

				// 画面を初期化する
				ClearDrawScreen();

				// 描画
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
			//ゲームオーバー演出
			if (gameStatus == STATE_END)
			{
				camera->GameEnd(player->GetPos());
				EndJudge = player->PlayerEnd();
				// 画面を初期化する
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

			//ゲームリザルト
			if (gameStatus == STATE_GAMEOVER)
			{
				player->PlayerGameOver();
				// 画面を初期化する
				ClearDrawScreen();
				//描画
				skydome->SkydomeDraw();
				stage->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				player->Draw();
				game->GameOver();
				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					WaitTimer(80);
					gameStatus = STATE_INIT;
				}
			}
		}
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		// フレーム終了時の時間を取得
		int endTime = GetNowCount();

		// フレーム処理時間を計算
		int elapsedTime = endTime - startTime;

		// 処理が早く終わった場合、残り時間待機する
		if (elapsedTime < FRAME_TIME)
		{
			// 残り時間待機
			WaitTimer(FRAME_TIME - elapsedTime);
		}
	}

	// 後始末
	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}