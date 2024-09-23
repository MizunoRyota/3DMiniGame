#pragma once

class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    void BusCheck(const VECTOR& player, const VECTOR& obs);
    bool CarCheck(const VECTOR& player, const VECTOR& obs);
    void PuddleCheck(const VECTOR& player, const VECTOR& obs);
    bool DeadJudge();
    void circleDraw();
    const bool & GetDead() const { return deadgudge; }
    const bool& GetSpeed() const { return SpeedDownjudge; }

private:
    VECTOR PlayerCircle;        //�v���C���[�̓����蔻��̃|�W�V����
    VECTOR Distancepos[3];      //�o�X�̓����蔻�肻�ꂼ��̃|�W�V����
    VECTOR ObstacleCircle[3];   //�o�X�ƃv���C���[�Ƃ̋����̌��Z��ێ�����
    VECTOR Cardistance;         //���ʎ����Ԃƃv���C���[�Ƃ̋����̌��Z�̕ێ�����
    VECTOR CarCircle;           //���ʎ����Ԃ̓����蔻��̃|�W�V����
    VECTOR Puddledistance[2];   //
    VECTOR PuddleCircle[2];     //
    float Distance[3];          //
    const int BusNum = 3;       //�o�X�̓����蔻��̐�
    const int PuddleNum = 2;    //�݂����܂�̓����蔻��̐�
    bool deadgudge;             //�v���C���[���ڐG�������̔���
    bool SpeedDownjudge;        //�v���C���[�̃X�s�[�h�_�E������
    float CarLength;            //���ʎ����Ԃƃv���C���[�Ƃ̔��a���m�̍��v
    float Length;               //�o�X�ƃv���C���[�Ƃ̔��a���m�̍��v
    float PuddleLength;         //
    float ObstacleRadius;       //�o�X�̓����蔻��̔��a
    float PlayerRadius;         //�v���C���[�̓����蔻��̔��a
    float PuddleRadius;         //�݂����܂�̂����锻��̔��a
    float CarRadius;            //���ʎ����Ԃ̓����蔻��̔��a
    float CarDistance;          //���ʎ����Ԃƃv���C���[�̋���
    float PuddleDistance[2];       //�݂����܂�ƃv���C���[�̋���
};