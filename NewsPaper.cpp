#include"DxLib.h"
#include"NewsPaper.h"
NewsPaper::NewsPaper()
{
	NewsPaperHandle = MV1LoadModel("Data/3Dmodel/Obstacle/NewsPaper/NewsPaper.mv1");
    bool flag = false; // �t���O�̏����l
    int interval = 1000; // �؂�ւ��Ԋu�i�~���b�j
    int lastTime = 0; // �Ō�Ƀt���O��؂�ւ�������
	Pos = VGet(0, 0, 0);
}

NewsPaper::~NewsPaper()
{
	MV1DeleteModel(NewsPaperHandle);
}

void NewsPaper::Initialize()
{

}

void NewsPaper::Update()
{
    int currentTime = GetNowCount();
    // ��莞�Ԍo�߂������m�F
    if (currentTime - lastTime >= interval) {
        flag = !flag; // �t���O��؂�ւ�
        lastTime = currentTime; // �Ō�̎������X�V
    }
    // �t���O�̏�Ԃ�\���i�R���\�[���o�́j
    if (flag) {
        printf("Flag is TRUE\n");
    }
    else {
        printf("Flag is FALSE\n");
    }
}

void NewsPaper::Draw()
{
    if (flag) {
        printf("Flag is TRUE\n");
    }
    else {
        printf("Flag is FALSE\n");
    }

}