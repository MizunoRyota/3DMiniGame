#include"DxLib.h"
#include"NewsPaper.h"
const float NewsPaper::Scale = 0.02f;		// �X�P�[��
#define PI    3.1415926535897932384626433832795f
NewsPaper::NewsPaper()
{
	NewsPaperHandle = MV1LoadModel("Data/3Dmodel/Obstacle/NewsPaper/NewsPaper.mv1");
    NewsPaperGraph = LoadGraph("Data/Texture/game/NewsPaper.png");
    bool flag = false;      // �t���O�̏����l
    int interval = 800000;  // �؂�ւ��Ԋu�i�~���b�j
    int lastTime = 0;       // �Ō�Ƀt���O��؂�ւ�������
	Pos = VGet(0, 3, 0);
    RightDir = false;
    LeftDir = true;
    CrushTime = 0;
    Rotation = 0;
    // 3D���f���̃X�P�[������
    MV1SetScale(NewsPaperHandle, VGet(Scale, Scale, Scale));
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(NewsPaperHandle, Pos);
}

NewsPaper::~NewsPaper()
{
	MV1DeleteModel(NewsPaperHandle);
}

void NewsPaper::Initialize()
{
    Pos = VGet(0.0f, 1.0f, 80.0f);
    MV1SetRotationXYZ(NewsPaperHandle, VGet(0.0f,0.0f,0.0f ));
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(NewsPaperHandle, Pos);
}

void NewsPaper::Update()
{
    LateralMove();
    if (CrushJudge==true)
    {
        CrashPaper();
    }
    else
    {
        Pos.z -= 0.5f;
        MV1SetRotationXYZ(NewsPaperHandle, VGet(90.0f * DX_PI_F / 180.0f, 0.0f, Rotation));
    }
    Rotation += 0.1f;
    if (Pos.z <= -100)
    {
        Pos.z = 80;
    }
    int currentTime = GetNowCount();
    if (Pos.x > 3)
    {
        Pos.x -= 0.3;
        LeftDir = true;
        RightDir = false;
    }
    else if (Pos.x < -3)
    {
        Pos.x -= -0.3;
        LeftDir = false;
        RightDir = true;
    }
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(NewsPaperHandle, Pos);
}
void NewsPaper::CrashPaper()
{
    if (CrushJudge == true)
    {

        Pos = VGet(0, 1, -30);

        // ����̌Ăяo�����ɊJ�n������ݒ�
        if (CrushTime == 0)
        {
            CrushTime = GetNowCount();  // �~���b�P�ʂŌ��ݎ������擾
        }
        // �o�ߎ��Ԃ�3000�~���b(3�b)�ȏ�o�߂�����t���O��؂�ւ���
        if (GetNowCount() - CrushTime >= 2000)
        {
            CrushJudge = false;
            CrushTime = 0;
        }
    }
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(NewsPaperHandle, Pos);
}

void NewsPaper::ChangeCrush()
{
    CrushJudge = true;
}
void NewsPaper::LateralMove ()
{
    if (LeftDir==true)
    {
        Pos.x -= 0.05;
    }

    else if (RightDir==true)
    {
        Pos.x += 0.05f;
    }    
    // �RD���f���̃|�W�V�����ݒ�
    MV1SetPosition(NewsPaperHandle, Pos);
}

void NewsPaper::Draw()
{
    if (CrushJudge==true)
    {
        // �ǂ݂��񂾃O���t�B�b�N����]�`��
        DrawRotaGraph(800, 220, 1.2f, PI / 3, NewsPaperGraph, TRUE);
    }
    MV1DrawModel(NewsPaperHandle);
}