#pragma once

class Player;

/// <summary>
/// カメラ
/// </summary>
class Camera
{
public:
	Camera();			// コンストラクタ.
	~Camera();			// デストラクタ.
	void Init();		//初期化
	void GameTitle(const VECTOR& mappos);//ゲームタイトル
	void ReadyUpdate(const VECTOR& playerpos);//チュートリアル画面
	void Update(const VECTOR playerpos);	// 更新.
	void GameEnd(const VECTOR planepos);//ゲームオーバー画面準備

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }

private:
	float zoom;				//z軸のカメラポジション
	float Hight;			//y軸のカメラポジション
	VECTOR	pos;			// ポジション.
	VECTOR targtpos;		//　カメラが注視するポジション
};