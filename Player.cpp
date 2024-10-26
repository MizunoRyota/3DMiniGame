#include"DxLib.h"
#include"Player.h"
#include"HitChecker.h"
#include"Bgm.h"
// 静的定数
// 速度（1=1m、60fps固定として、時速10km）
// 10000m ÷ 時間 ÷ 分 ÷ 秒 ÷ フレーム
const float Player::Speed = static_cast<float>(10000.0 / 42.0 / 42.0 / 42.0);
const float Player::DownSpeed = static_cast<float>(10000.0 / 60.0 / 60.0 / 60.0);

const float Player::Scale = 0.006f;		// スケール
const float Player::Gravity = 0.75f;     // 重力加速度
const float Player::JumpSpeed = 0.2f;   // ジャンプの初速度

BGM* bgm = new BGM();

Player::Player()
{
	// ３Ｄモデルの読み込み
	PlayerHandle = MV1LoadModel("Data/3Dmodel/Player/Player.mv1");
	//画像の読み込み
	SpeedDownHandle = LoadGraph("Data/Texture/game/SpeedDown.png");
	BettoriFrame = LoadGraph("Data/Texture/game/TarGraph.png");
	BettoriHnadle = LoadGraph("Data/Texture/game/Bettori.png");
	InvicibleGraph= LoadGraph("Data/Texture/game/CanInvicible.png");
	InvicibleChargeGraph=LoadGraph("Data/Texture/game/Invicible.png");

	Tar = LoadSoundMem("Data/Sound/Game/水ぶくぶく2.mp3");
	ChangeVolumeSoundMem(255 * 70 / 100, Tar);
	// 再生時間の初期化
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
	//３ＤモデルのY軸の回転値を９０度にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f,-90.0f * DX_PI_F / 180.0f, 0.0f));
	//３Dモデルのポジション設定
	MV1SetPosition(PlayerHandle, Pos);
}

Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(PlayerHandle);
}

void Player::PlayerInitialize()
{
	//モーションの変更
	ChangeMotion(4);
	// 再生時間の初期化
	PlayTime = 0.0f;
	//プレイヤーの初期化
	Pos = VGet(0.5, 0.5f, -7.0);
	Velocity = VGet(0, 0, 0);
	Dir = VGet(0, 0, 0);
	Rotation = 0; 
	mVal = 0;
	SpeedDownJudge = false;
	Invicible = false;
	CanInvicible = false;
	// ３ＤモデルのY軸の回転値を９０度にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f,300.0f * DX_PI_F / 180.0f, 0.0f));
	MV1GetRotationXYZ( PlayerHandle);
	// ３Dモデルのポジション設定
	MV1SetPosition(PlayerHandle, Pos);
}

void  Player::PlayerTitle()
{

	// 再生時間を進める
	PlayTime += 0.5f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (PlayTime >= TotalTime)
	{
		PlayTime = 0.0f;
	}

	// ３ＤモデルのY軸の回転値を９０度にセットする	
	// // ３ＤモデルのY軸の回転値を正面にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 300.0f * DX_PI_F / 180.0f, 0.0f));

	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(PlayerHandle, Pos);

	//3dモデルのアニメーションのセット
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);

}

void Player::ChangeMotion(int motionNum)
{
	MV1DetachAnim(PlayerHandle, AttachIndex);

	// 再生時間をセットする
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);

	this->PlayAnim = motionNum;
	// ３Ｄモデルの０番目のアニメーションをアタッチする
	AttachIndex = MV1AttachAnim(PlayerHandle, this->PlayAnim, -1, FALSE);
	// アタッチしたアニメーションの総再生時間を取得する
	TotalTime = MV1GetAttachAnimTotalTime(PlayerHandle, AttachIndex);
}

void Player::PlayerUpdate()
{

	// ３ＤモデルのY軸の回転値を正面にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(0.0f, 180.0f * DX_PI_F / 180.0f, 0.0f));

	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// キーボード入力のチェック
	if (CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_SPACE))
	{

		Jump();  // スペースキーが押されたらジャンプを開始
	}

	// ジャンプ中の処理
	if (isJumping)
	{
		// 現在のジャンプ速度をポジションに反映
		Pos.y += jumpVelocity;

		// 重力の影響を受ける
		jumpVelocity -= Gravity * 0.016f; // フレームレートに依存した減少

		// 地面に着地した場合
		if (Pos.y <= 0.50f)
		{
			//モーションの変更
			ChangeMotion(1);
			Pos.y = 0.50f;     // 地面にセット
			isJumping = false; // ジャンプ状態をリセット
			jumpVelocity = 0;  // ジャンプ速度をリセット
		}
	}
	//無敵の切り替え
	ChangeInvicible();

	if (Pos.y <= 0.5f)
	{
		ChangeMotion(1);
	}

	// 再生時間を進める
	PlayTime += 0.4f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (PlayTime >= TotalTime)
	{
		PlayTime = 0.0f;
	}

	// 単純に方向転換
	Dir = VGet(0, 0, 0);

	if (Key & PAD_INPUT_RIGHT)
	{
		Dir = VAdd(Dir, VGet(1, 0, 0));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		Dir = VAdd(Dir, VGet(-1, 0, 0));
	}

	// ゼロ除算避け
	if (VSquareSize(Dir) > 0)
	{
		// 正規化
		Dir = VNorm(Dir);
	}

	ChangeSpeedFlag();

	// ポジションを更新.
	if (SpeedDownJudge==true)
	{
		Velocity = VScale(Dir, DownSpeed);
	}
	else
	{
		Velocity = VScale(Dir, Speed);
	}

	Pos = VAdd(Pos, Velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
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

	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(PlayerHandle, Pos);
	//3dモデルのアニメーションのセット
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);
}

void Player::Jump()
{
	//モーションの変更
	ChangeMotion(3);
	// プレイヤーが地面にいる時だけジャンプを開始
	if (!isJumping)
	{
		isJumping = true;
		jumpVelocity = JumpSpeed;  // ジャンプ初速度を設定
	}
}

bool Player::PlayerEnd()
{

	//モーションの変更
	ChangeMotion(0);

	// 再生時間を進める
	PlayTime += 0.1f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す

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

	// ３ＤモデルのY軸の回転値を正面にセットする
	MV1SetRotationXYZ(PlayerHandle, VGet(-90.0f * DX_PI_F / 180.0f, 180.0f * DX_PI_F / 180.0f, Rotation));
	// 3Dモデルのスケール決定
	MV1SetScale(PlayerHandle, VGet(Scale, Scale, Scale));
	// ３Dモデルのポジション設定
	MV1SetPosition(PlayerHandle, Pos);
	//3dモデルのアニメーションのセット
	MV1SetAttachAnimTime(PlayerHandle, AttachIndex, PlayTime);

	return EndJudge;
}

void Player::PlayerGameOver()
{
	//プレイヤーが落ちていく
	Pos.y -= 0.005;
	// ３Dモデルのポジション設定
	MV1SetPosition(PlayerHandle, Pos);
}
void Player::PlayCrushTar()
{
	PlaySoundMem(Tar, DX_PLAYTYPE_BACK, true);            //べっとり音
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
		// 初回の呼び出し時に開始時刻を設定
		if (ChangeSpeedTime == 0)
		{
			PlayCrushTar();
			ChangeSpeedTime = GetNowCount();  // ミリ秒単位で現在時刻を取得
		}

		// 経過時間が3000ミリ秒(3秒)以上経過したらフラグを切り替える
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
		//val増加
		mVal += mValInc;
	}

	//valが上限、下限を超えた時の処理
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
	//スペースを入力した時に無敵状態になる
	if (mVal==mMaxval&&CanInvicible==true&& CheckHitKey(KEY_INPUT_SPACE))
	{
		Invicible = true;
		CanInvicible = false;
	}
}

// ゲージを描画する
// x,y ゲージ描画左上座標　width, height ゲージ幅,高さ, ゲージ最大値, ゲージ値, ゲージ内カラー
void Player::DrawInvicibleMeter(int x, int y, int width, int height, int max, int val, int color)
{
	int meterlen;
	int left = x - 2;
	int right = x + width + 2;
	int top = y - 2;
	int bottom = y + height + 2;

	meterlen = (int)((float)width * ((float)val / (float)max));


	//体力ゲージ背景部分
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(left, top, right, bottom, 0xFF880000, TRUE);

	//体力ゲージ部分
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	DrawBox(x, y, x + meterlen, y + height, color, TRUE);

	//体力ゲージの枠を描画

	//上下横線
	DrawLine(left, top, right, top, 0xFFFFFFFF);
	DrawLine(left, bottom, right, bottom, 0xFFFFFFFF);

	//左右縦線
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
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(PlayerHandle);
	DrawSpeedDown();
}