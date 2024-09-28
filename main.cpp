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
	STATE_TITLE,		// タイトル.
	STATE_READY,        //準備
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
	LPCSTR font_path = "Data/Font/Mimi_font-Regular.otf"; // 読み込むフォントファイルのパス
	//// フォントの変更
	ChangeFont("Mimi_font", DX_CHARSET_DEFAULT);
	// インスタンス生成
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
	// エスケープキーが押されるかウインドウが閉じられるまでループ
	LONGLONG frameTime = 0;

	bool DeadJudge = false;			//ゲームオーバーの判定
	bool EndJudge = false;
	bool debugPauseFlag = false;	//ポーズするときの変数
	int gameStatus = STATE_INIT;	//現在のゲーム中の状態

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
				stage2->Init();
				car->Init();
				bus->Init();
				puddle->Init();
				player->PlayerInitialize();
				camera->Init();
				//ゲーム状態変化
				gameStatus = STATE_TITLE;
			}

			//タイトル画面
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

				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					WaitTimer(200);
					ClearDrawScreen();
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
				stage2->GameDraw();
				player->Draw();
				game->GameReady();

				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
					gameStatus = STATE_GAME;
				}
			}
			//ゲーム中
			if (gameStatus == STATE_GAME)
			{
				//ゲームシーンの制御
				game->GameUpdate();

				// プレイヤー制御
				player->PlayerUpdate();
				// カメラの制御
				camera->Update(player->GetPos());
				// スカイドーム制御
				skydome->SkydomeUpdate();

				//ステージ制御
				stage->Update();
				stage2->Update();

				//障害物制御
				bus->Update(game->GetObstaclePattern());
				car->Update(game->GetObstaclePattern());
				puddle->Update();
				//コイン制御
				coin->Update(bus->GetPos(),car->GetPos());

				hitcheck->BusCheck(player->GetPos(), bus->GetPos());//バストの接触確認
				DeadJudge = hitcheck->GetDead();//ゲームオーバーの判定
				if (hitcheck->CarCheck(player->GetPos(), car->GetPos()))//普通自動車との判定
				{
					DeadJudge = hitcheck->DeadJudge();
				}
				hitcheck->PuddleCheck(player->GetPos(), puddle->GetPos(),player);

				// 画面を初期化する
				ClearDrawScreen();

				// 描画
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
			//ゲームオーバー演出
			if (gameStatus == STATE_END)
			{

				camera->GameEnd(player->GetPos());
				EndJudge = player->PlayerEnd();
				// 画面を初期化する
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

			//ゲームリザルト
			if (gameStatus == STATE_GAMEOVER)
			{
				// 画面を初期化する
				ClearDrawScreen();

				//描画

				skydome->SkydomeDraw();
				stage->GameDraw();
				stage2->GameDraw();
				bus->GameDraw();
				car->GameDraw();
				player->Draw();
				game->GameOver();
				// ゲーム状態変化
				if (CheckHitKey(KEY_INPUT_SPACE))
				{
					ClearDrawScreen();
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