#pragma once

class Player;

/// <summary>
/// �J����
/// </summary>
class Camera
{
public:
	Camera();			// �R���X�g���N�^.
	~Camera();			// �f�X�g���N�^.
	void Init();		//������
	void GameTitle(const VECTOR& mappos);//�Q�[���^�C�g��
	void ReadyUpdate(const VECTOR& playerpos);//�`���[�g���A�����
	void Update(const VECTOR playerpos);	// �X�V.
	void GameEnd(const VECTOR planepos);//�Q�[���I�[�o�[��ʏ���

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }

private:
	float zoom;				//z���̃J�����|�W�V����
	float Hight;			//y���̃J�����|�W�V����
	VECTOR	pos;			// �|�W�V����.
	VECTOR targtpos;		//�@�J��������������|�W�V����
};