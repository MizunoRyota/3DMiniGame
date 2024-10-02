#pragma once
#include"Player.h"
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    void BusCheck(const VECTOR& player, const VECTOR& obs);
    bool CarCheck(const VECTOR& player, const VECTOR& obs);
    bool CoinCheck(const VECTOR& player, const VECTOR& obs);
    bool NewsPaperCheck(const VECTOR& player, const VECTOR& obs);
    void PuddleCheck(const VECTOR& playerpos, const VECTOR& obs,Player*player);
    bool DeadJudge();
    void circleDraw();
    const bool & GetDead() const { return deadgudge; }
    const bool& GetSpeed() const { return SpeedDownjudge; }
private:
    VECTOR PlayerCircle;        //�v���C���[�̓����蔻��̃|�W�V����
    VECTOR BusDistancepos[3];   //�o�X�̓����蔻�肻�ꂼ��̃|�W�V����
    VECTOR BusCircle[3];        //�o�X�̓����蔻��̃|�W�V����
    VECTOR Cardistance;         //���ʎ����Ԃƃv���C���[�Ƃ̋����̌��Z�̌��ʂ�ێ�����
    VECTOR CarCircle;           //���ʎ����Ԃ̓����蔻��̃|�W�V����
    VECTOR Puddledistance[3];   //�����܂�ƃv���C���[�̋����̌��Z�̌��ʂ�ێ�����
    VECTOR PuddleCircle[3];     //�����܂�̃|�W�V����
    //�R�C��
    VECTOR CoinCircle;          //�R�C���̓����蔻��̃|�W�V����
    VECTOR Coindistance;
    float CoinDistance;
    float CoinLength;
    float CoinRadius;    
    //�V����
    VECTOR NewsPaperCircle;          //�V�����̓����蔻��̃|�W�V����
    VECTOR NewsPaperdistance;
    float NewsPaperDistance;
    float NewsPaperLength;
    float NewsPaperRadius;
    float Busdistance[3];       //�o�X�ƃv���C���[�Ƃ̋����̌��Z��ێ�����
    const int BusNum = 3;       //�o�X�̓����蔻��̐�
    const int PuddleNum = 3;    //�݂����܂�̓����蔻��̐�
    bool deadgudge;             //�v���C���[���ڐG�������̔���
    bool SpeedDownjudge;        //�v���C���[�̃X�s�[�h�_�E������
    float CarLength;            //���ʎ����Ԃƃv���C���[�Ƃ̔��a���m�̍��v
    float Length;               //�o�X�ƃv���C���[�Ƃ̔��a���m�̍��v
    float PuddleLength;         //�݂����܂�ƃv���C���[�Ƃ̔��a���m�̍��v
    float BusRadius;            //�o�X�̓����蔻��̔��a
    float PlayerRadius;         //�v���C���[�̓����蔻��̔��a
    float PuddleRadius;         //�݂����܂�̂����锻��̔��a
    float CarRadius;            //���ʎ����Ԃ̓����蔻��̔��a
    float CarDistance;          //���ʎ����Ԃƃv���C���[�̋���
    float PuddleDistance[3];    //�݂����܂�ƃv���C���[�̋���
};