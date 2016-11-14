#pragma once
/******************************************************************************
/*!
@file   Motion.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Math\Quaternion.h"
#include "..\Math\Matrix.h"


/*  �\���̒�`
******************************************************************************/


namespace Framework
{
    class Motion
    {
    public:
        enum
        {
            NEUTRAL = 0,    // �j���[�g����
            WALKING,        // ����
            JUMPING,        // �W�����v
            LANDING,        // ���n
            MELEE,          // �i��
            SHOOTING,       // �ˌ�
            SKILL,          // �X�L��
            STUNNED,        // �C��
            STANDING,       // �N���オ��

            MOTION_MAX,
        };

        struct MotionDataHeader
        {
            bool        loop;           // ���[�v���邩�ǂ���
            int         keyframeNum;    // �L�[�t���[����
            int         frameMax;       // �ő�t���[��
        };
        struct Key
        {
            Quaternion  rot;            // ��]
            Vector3     scale;          // �g��
            Vector3     trans;          // �ړ�
        };
        struct KeyFrame
        {
            int     interval;       // �L�[�ԃC���^�[�o��
            Key*    keyList;        // �L�[���
        };

        Motion();
        ~Motion();

        void SetFrame(int frame) { this->frame = frame; }
        void NextFrame(int addFrameCnt);

        int         frame;          // �t���[��
        bool        loop;           // ���[�v���邩�ǂ���
        int         keyframeNum;    // ���݂̃L�[�t���[��
        int         frameMax;       // �L�[�t���[����
        KeyFrame*   keyframeList;   // �L�[�t���[�����X�g

    };
}


/******************************* �w�b�_�����܂� ******************************/
