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
	void ChangeScoreColor();				//�X�R�A�̐F�̍X�V
	void ScoreDraw();						//�X�R�A�̕\��
	void ScoreUp();							//�X�R�A���Z
	void HighScoreDraw();					//�n�C�X�R�A�̕\��
	void GameOver();						//�Q�[���I�[�o�[�̕\��
	const int& GetObstaclePattern() const { return ObstaclePattern; }	//��Q���p�^�[���n��
	const float& GetObstacleSpeed() const { return ObstacleSpeed; }	//��Q���X�s�[�h�n��
private:
	int Controller;							//�R���g���[���[�̉摜
	int PaintHandle[4];						//�y�C���g�̉摜
	int TitleHandle;						//�^�C�g���̉摜
	int KeyBordHandle;						//�L�[�{�[�h�̉摜
	int PuddleTutorialHandle;				//�����܂�摜
	int NewsPaperTutorialHandle;			//�V�����摜
	int CrushNewsPaperHandle;				//�V�����ɏՓ˂������̉摜�n���h��
	int ScoreColorR;						//	�X�R�A�̐FR
	int ScoreColorG;						//	�X�R�A�̐FG
	int ScoreColorB;						//�@�X�R�A�̐FB
	int ColorChangeSpeed;					//	�X�R�A�̐F���ω����鑬�x
	int Score;								//�X�R�A
	int HighScore;							//�n�C�X�R�A
	int SpeedMeter;							//���݂̃X�s�[�h
	int ObstaclePattern;					//��Q���̔z�u�p�^�[��
	float ObstacleSpeed;					//��Q�����x
	bool IsObstacle;						//��Q�������邩�ǂ����̔���
	bool ReadyPhase1;						//�`���[�g���A�����1�i�K
	bool ReadyPhase2;						//�`���[�g���A�����2�i�K
	bool ReadyPhase3;						//�`���[�g���A�����3�i�K
};
