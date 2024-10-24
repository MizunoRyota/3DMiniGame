#include"DxLib.h"
#include"Pallet.h"
#include"HitChecker.h"
#include"Player.h"

Player player;

HitChecker::HitChecker()
{
    Length = PlayerRadius + BusRadius;
    CarLength = PlayerRadius + CarRadius;
    BusRadius = 1.5f;
    PlayerRadius = 0.5f;
    PuddleRadius = 0.9f;
    CarRadius = 1.3f;
    NewsPaperRadius = 1.5f;
    CoinRadius = 1.0;
    deadgudge = false;
    SpeedDownjudge = false;
}
HitChecker::~HitChecker()
{}
/// <summary>
/// ������
/// </summary>
void HitChecker::Init()
{
    deadgudge = false;
    SpeedDownjudge = false;
}

/// <summary>
/// �o�X�̓����蔻��
/// </summary>
/// <param name="player"></param>
/// <param name="obs"></param>
void HitChecker::BusCheck(const VECTOR& player, const VECTOR& obs, bool Invicible)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    PlayerCircle = VGet(player.x, player.y + 0.6f, player.z);
    BusCircle[1] = VGet(obs.x, obs.y, obs.z);//���S
    BusCircle[0] = VGet(obs.x, obs.y, obs.z-3.0f);//��
    BusCircle[2] = VGet(obs.x, obs.y, obs.z+3.0f);//��O
    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v�̌v�Z
    Length = PlayerRadius + BusRadius;

    for (int i = 0; i < BusNum; i++)
    {
        //�v���C���[�̃|�W�V��������o�X�̃|�W�V���������Z
        BusDistancepos[i] = VSub(player, BusCircle[i]);
        //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
        Busdistance[i] = VSquareSize( BusDistancepos[i]);
        if (Busdistance[i] <= (Length))
        {
            //�Q�[���I�[�o�[�t���O�̕ύX
            DeadJudge();
        }
    }
}

/// <summary>
/// �݂����܂�`�F�b�N
/// </summary>
/// <param name="playerpos"></param>
/// <param name="obs"></param>
/// <param name="player"></param>
void HitChecker::PuddleCheck(const VECTOR& playerpos, const VECTOR& obs, Player* player, bool Invicible)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    PuddleCircle[1] = VGet(obs.x , obs.y, obs.z);         //���S
    PuddleCircle[0] = VGet(obs.x + 2, obs.y, obs.z);      //��
    PuddleCircle[2] = VGet(obs.x + -2, obs.y, obs.z);     //��O 

    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    PuddleLength = PlayerRadius + CarRadius;

    for (int i = 0; i < PuddleNum; i++)
    {
        //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
        Puddledistance[i] = VSub(playerpos, PuddleCircle[i]);

        PuddleDistance[i] = VSquareSize(Puddledistance[i]);

        if (PuddleDistance[i] <= (PuddleLength))
        {
            SpeedDownjudge = true;
            player->Set(SpeedDownjudge);
        }
    }
}

/// <summary>
/// ���ʎ����Ԕ���
/// </summary>
/// <param name="player"></param>
/// <param name="obs"></param>
/// <returns></returns>
bool HitChecker::CarCheck(const VECTOR& player, const VECTOR& obs, bool Invicible)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    CarCircle = VGet(obs.x, obs.y+0.6, obs.z);

    //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
    Cardistance = VSub(player, obs);

    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    CarLength = PlayerRadius + CarRadius;
    //���K��
    CarDistance = VSquareSize(Cardistance);

    return CarDistance <= (CarLength);
}

bool HitChecker::CoinCheck(const VECTOR& player, const VECTOR& obs)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    CoinCircle = VGet(obs.x, obs.y + 0.6, obs.z);

    //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
    Coindistance = VSub(player, obs);

    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    CoinLength = PlayerRadius + CoinRadius;
    //���K��
    CoinDistance = VSquareSize(Coindistance);

    return CoinDistance <= (CoinLength);
}

bool HitChecker::NewsPaperCheck(const VECTOR& player, const VECTOR& obs, bool Invicible)
{
    //�I�u�W�F�N�g�̈ʒu�l��
    NewsPaperCircle = VGet(obs.x, obs.y + 0.6, obs.z);

    //�v���C���[�ƃI�u�W�F�N�g�̋����̍��v���l��
    NewsPaperdistance = VSub(player, obs);

    //�I�u�W�F�N�g�ƃv���C���[�̔��a�̍��v
    NewsPaperLength = PlayerRadius + NewsPaperRadius;
    //���K��
    NewsPaperDistance = VSquareSize(NewsPaperdistance);

        return NewsPaperDistance <= (NewsPaperLength);
}

bool HitChecker::DeadJudge()
{
    //�Q�[���I�[�o�[����
    deadgudge = true;

    return deadgudge;
}

void HitChecker::circleDraw()
{
    for (int i = 0; i < 3; i++)
    {
        if (Busdistance[i] <= (Length))
        {
            DrawSphere3D(BusCircle[i], BusRadius, 16, Pallet::AliceBlue.GetHandle(), Pallet::AliceBlue.GetHandle(), false);
        }
        else
        {
        DrawSphere3D(BusCircle[i], BusRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
        }
    }

    DrawSphere3D(CarCircle, CarRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(PlayerCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(CoinCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    DrawSphere3D(NewsPaperCircle, PlayerRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);

    for (size_t i = 0; i < 3; i++)
    {
        DrawSphere3D(PuddleCircle[i], PuddleRadius, 16, Pallet::Black.GetHandle(), Pallet::Black.GetHandle(), false);
    }
}