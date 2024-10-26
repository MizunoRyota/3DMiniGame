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
	void MoveArrow();						//���X�V
	void GameUpdate();						//�Q�[�����̍X�V
	void SpeedUpDraw();						//
	void CountDown();						//
	void CrushCoin();						//
	void PlayDecideSound();
	void StopDecideSound();
	void PlayCoinSound();
	void StopCoinSound();
	void ObstacleSpeedUpdate();				//��Q���̃X�s�[�h�X�V
	void ObstacleConfiguration();			//��Q���p�^�[���̔z�u
	void ChangeScoreColor();				//�X�R�A�̐F�̍X�V
	void ScoreDraw();						//�X�R�A�̕\��
	void ScoreUp();							//�X�R�A���Z
	void HighScoreDraw();					//�n�C�X�R�A�̕\��
	void GameOver();						//�Q�[���I�[�o�[�̕\��
	void Draw();							//
	const int& GetObstaclePattern() const { return ObstaclePattern; }	//��Q���p�^�[���n��
	const float& GetObstacleSpeed() const { return ObstacleSpeed; }	//��Q���X�s�[�h�n��
	const bool& GetReadyPhase3() const { return ReadyPhase3; }		//
private:
	int Controller;							//�R���g���[���[�̉摜
	int PaintHandle[4];						//�y�C���g�̉摜
	int TitleHandle;						//�^�C�g���̉摜
	int SpaceHandle;						//�X�y�[�X�L�[�̉摜
	int RedSpaceHandle;						//�Ԃ��X�y�[�X�L�[�̉摜
	int LeftArrowHandle;					//���̉摜
	int RightArrowHandle;					//���̉摜
	int PuddleTutorialHandle;				//�����܂�摜
	int NewsPaperTutorialHandle;			//�V�����摜
	bool IsCoin;							//
	int CrushNewsPaperHandle;				//�V�����ɏՓ˂������̉摜�n���h��
	int ScoreColorR;						//	�X�R�A�̐FR
	int ScoreColorG;						//	�X�R�A�̐FG
	int ScoreColorB;						//�@�X�R�A�̐FB
	int ColorChangeSpeed;					//	�X�R�A�̐F���ω����鑬�x
	int Coin;
	int Score;								//�X�R�A
	int HighScore;							//�n�C�X�R�A
	int SpeedMeter;							//���݂̃X�s�[�h
	int ObstaclePattern;					//��Q���̔z�u�p�^�[��
	float ObstacleSpeed;					//��Q�����x
	bool IsObstacle;						//��Q�������邩�ǂ����̔���
	//�`���[�g���A��
	bool ReadyPhase1;						//�`���[�g���A�����1�i�K
	bool ReadyPhase2;						//�`���[�g���A�����2�i�K
	bool ReadyPhase3;						//�`���[�g���A�����3�i�K
	bool ArrowMove;						
	int ArrowHandle;						//���摜�n���h��
	float ArrowPosX;						//����X���W�̈ʒu
	float ArrowSpeed;						//���̃X�s�[�h
	int Decide;								//���艹

};
