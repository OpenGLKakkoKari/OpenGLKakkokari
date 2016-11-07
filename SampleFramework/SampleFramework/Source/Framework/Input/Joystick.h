#pragma once
/******************************************************************************
/*!
@file   Joystick.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <windows.h>
#include <mmsystem.h>


/*  ���C�u���������N
******************************************************************************/


#pragma comment(lib, "winmm.lib")


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace Input
    {
        class Joystick
        {
        public:
            enum Channel
            {
                CHANNEL_0 = 0,
                CHANNEL_1,
                CHANNEL_2,
                CHANNEL_3,
            };

            // �\���L�[��ONOFF�̂������l
            enum
            {
                THRESHOLD_MIN = 0x6000,
                THRESHOLD_MAX = 0x8000
            };

            enum Button
            {
                BUTTON_0,
                BUTTON_1,
                BUTTON_2,
                BUTTON_3,
                BUTTON_4,
                BUTTON_5,
                BUTTON_6,
                BUTTON_7,
                BUTTON_8,
                BUTTON_9,
                BUTTON_10,
                BUTTON_11,
                BUTTON_12,
                BUTTON_13,
                BUTTON_14,
                BUTTON_15,

                BUTTON_EXCEPT_AXIS_MAX,

                BUTTON_UP = BUTTON_EXCEPT_AXIS_MAX,
                BUTTON_DOWN,
                BUTTON_LEFT,
                BUTTON_RIGHT,

                BUTTON_MAX,
            };

            Joystick();
            Joystick(Channel id);
            virtual ~Joystick();

            void Update();

            bool Press(int Key){ return press[Key]; }
            bool Trigger(int Key){ return trigger[Key]; }
            bool Release(int Key){ return release[Key]; }
            bool Repeat(int Key){ return repeat[Key]; }

            void SetRepeatTerm(int termFrame){ repeatTerm = termFrame; }
            static unsigned int GetConnectionNum() { return joyGetNumDevs(); }

        private:
            void Init();

            bool        press[BUTTON_MAX];
            bool        trigger[BUTTON_MAX];
            bool        release[BUTTON_MAX];
            bool        repeat[BUTTON_MAX];

            int         repeatCnt[BUTTON_MAX];
            int         repeatTerm;

            JOYINFOEX   info;
            Channel     id_;    // �W���C�X�e�B�b�N��ID
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/
