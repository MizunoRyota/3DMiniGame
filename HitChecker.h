#pragma once
#include"Player.h"
class HitChecker
{
public:
    HitChecker();
    ~HitChecker();
    void Init();
    void BusCheck(const VECTOR& player, const VECTOR& obs,bool Invicible);              //�o�X�ƃv���C���[�̓����蔻��
    bool CarCheck(const VECTOR& player, const VECTOR& obs, bool Invicible);             //
    bool CoinCheck(const VECTOR& player, const VECTOR& obs);                            //
    bool NewsPaperCheck(const VECTOR& player, const VECTOR& obs, bool Invicible);       //
    void PuddleCheck(const VECTOR& playerpos, const VECTOR& obs,Player*player, bool Invicible);//
    bool DeadJudge();                                            //�Q�[���I�[�o�[�̂Ȃ�������Ԃ�
    void circleDraw();                                           //�����蔻��̋��`��
    const bool & GetDead() const { return deadgudge; }           //�Q�[���I�[�o�[�̔����Ԃ�
    const bool& GetSpeed() const { return SpeedDownjudge; }      //�X�s�[�h�_�E���̔����Ԃ�
private:
    //�v���C���[
    VECTOR PlayerCircle;        //�v���C���[�̓����蔻��̃|�W�V����
    float PlayerRadius;         //�v���C���[�̓����蔻��̔��a
    bool deadgudge;             //�v���C���[���ڐG�������̔���
    bool SpeedDownjudge;        //�v���C���[�̃X�s�[�h�_�E������
    //�o�X
    VECTOR BusCircle[3];        //�o�X�̓����蔻��̃|�W�V����
    VECTOR BusDistancepos[3];   //�o�X�̓����蔻�肻�ꂼ��̃|�W�V����
    float Busdistance[3];       //�o�X�ƃv���C���[�Ƃ̋����̌��Z��ێ�����
    float BusRadius;            //�o�X�̓����蔻��̔��a
    const int BusNum = 3;       //�o�X�̓����蔻��̐�
    float Length;               //�o�X�ƃv���C���[�Ƃ̔��a���m�̍��v
    //��
    VECTOR CarCircle;           //���ʎ����Ԃ̓����蔻��̃|�W�V����
    VECTOR Cardistance;         //���ʎ����Ԃƃv���C���[�Ƃ̋����̌��Z�̌��ʂ�ێ�����
    float CarLength;            //���ʎ����Ԃƃv���C���[�Ƃ̔��a���m�̍��v
    float CarRadius;            //���ʎ����Ԃ̓����蔻��̔��a
    float CarDistance;          //���ʎ����Ԃƃv���C���[�̋���
    //�R�C��
    VECTOR CoinCircle;          //�R�C���̓����蔻��̃|�W�V����
    VECTOR Coindistance;        //�R�C���ƃv���C���[�Ƃ̋����̌��Z�̌��ʂ�ێ�����
    float CoinDistance;         //�R�C���ƃv���C���[�Ƃ̋���
    float CoinLength;           //�R�C���ƃv���C���[�Ƃ̔��a���m�̍��v
    float CoinRadius;           //�R�C���̓����蔻��̔��a
    //�V����
    VECTOR NewsPaperCircle;     //�V�����̓����蔻��̃|�W�V����
    VECTOR NewsPaperdistance;   //�V�����ƃv���C���[�Ƃ̋����̌��Z�̌��ʂ�ێ�����
    float NewsPaperDistance;    //�V�����ƃv���C���[�Ƃ̋���
    float NewsPaperLength;      //�V�����ƃv���C���[�̓����蔻��̍��v
    float NewsPaperRadius;      //�V�����̓����蔻��̔��a
    //�݂����܂�
    VECTOR PuddleCircle[3];     //�����܂�̃|�W�V����
    VECTOR Puddledistance[3];   //�����܂�ƃv���C���[�̋����̌��Z�̌��ʂ�ێ�����
    const int PuddleNum = 3;    //�݂����܂�̓����蔻��̐�
    float PuddleLength;         //�݂����܂�ƃv���C���[�Ƃ̔��a���m�̍��v
    float PuddleRadius;         //�݂����܂�̂����锻��̔��a
    float PuddleDistance[3];    //�݂����܂�ƃv���C���[�̋���
};