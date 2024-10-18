#pragma once
class Coin
{
public:
	Coin();
	~Coin();
	void Init();
	void Update(const VECTOR& carpos);
	void CoinInitalize();
	void Draw();
	void CoinMove();
	const VECTOR& GetPos() const { return pos; }//�|�W�V�����̈ʒu�Ԃ�
private:
	VECTOR pos;				//�|�W�V����
	int CoinHandle;			//3Dmodel
	float Rotation;			//��]�ϐ�
	float Hight;			//����
	bool isActive;			//�����Ă��邩
	// �ÓI�萔.
	static const float Scale;	
	static const float CoinNum;	

};
