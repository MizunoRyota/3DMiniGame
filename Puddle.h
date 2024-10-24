#pragma once


//みずたまり
class Puddle
{
public:
	Puddle();
	~Puddle();
	void Init();								//初期化
	void Update(float ObstacleSpeed, bool ObstaclePattern);			//更新
	void Draw();								//描画
	const VECTOR& GetPos() const { return pos; }//ポジションの位置返す

private:
	VECTOR pos;					//ポジション
	int PuddleHandle;			//3Dmodelのハンドル
	static const float Scale;	
};
