#pragma once
class GameState
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	GameState();
	~GameState();
	void GameInitialize();					//������
	void GameTitle();						//�^�C�g���\��
	void GameReady();						//�`���[�g���A���\��
	void GameUpdate();						//�Q�[�����̍X�V
	void ObstacleSpeedUpdate();				//��Q���̃X�s�[�h�X�V
	void ObstacleConfiguration();			//��Q���p�^�[���̔z�u
	void ScoreDraw();						//�X�R�A�̕\��
	void HighScoreDraw();					//�n�C�X�R�A�̕\��
	void GameOver();						//�Q�[���I�[�o�[�̕\��
	const int& GetObstaclePattern() const { return ObstaclePattern; }	//��Q���p�^�[���n��
	const float& GetObstacleSpeed() const { return ObstacleSpeed; }	//��Q���X�s�[�h�n��
private:
	int Controller;		//�R���g���[���[�̉摜
	int PaintHandle[4]; //�y�C���g�̉摜
	int Score;			//�X�R�A
	int HighScore;		//�n�C�X�R�A
	int SpeedMeter;		//���݂̃X�s�[�h
	int ObstaclePattern;//��Q���̔z�u�p�^�[��
	float ObstacleSpeed;//
	bool IsObstacle;	//��Q�������邩�ǂ����̔���
};
