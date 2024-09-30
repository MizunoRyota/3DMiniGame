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
	void SerchObstaclePos();				//��Q���̃|�W�V�����𒲂ׂ�
	void ObstacleConfiguration();			//��Q���p�^�[���̔z�u
	void ScoreDraw();						//�X�R�A�̕\��
	void HighScoreDraw();					//�n�C�X�R�A�̕\��
	void GameOver();						//�Q�[���I�[�o�[�̕\��
	const int& GetObstaclePattern() const { return ObstaclePattern; }	//��Q���p�^�[���n��

private:
	int Controller;		//�R���g���[���[�̉摜
	int PaintHandle[4]; //�y�C���g�̉摜
	int Score;			//�X�R�A
	int HighScore;		//�n�C�X�R�A
	int SpeedMeter;		//���݂̃X�s�[�h
	int ObstaclePattern;//��Q���̔z�u�p�^�[��
	bool IsObstacle;	//��Q�������邩�ǂ����̔���
};
