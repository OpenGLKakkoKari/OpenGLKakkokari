/******************************************************************************

@file   Joystick.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Joystick.h"

using namespace Framework::Input;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Joystick::Joystick() : 
repeatTerm(10), id_(CHANNEL_0)
{
    Init();
}
Joystick::Joystick(Channel id) : 
repeatTerm(10), id_(id)
{
    Init();
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Joystick::~Joystick()
{
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void Joystick::Init()
{
    for (int i = 0; i < BUTTON_MAX; i++)
    {
        press[i] = false;
        trigger[i] = false;
        release[i] = false;
        repeat[i] = false;
    }
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Joystick::Update()
{
    JOYINFOEX newInfo;
    if (JOYERR_NOERROR != joyGetPosEx(0, &newInfo))
        return;

// 
// ���݂̃{�^���̏����擾
// 

    BYTE newState[BUTTON_MAX];

    // �\���L�[�ȊO
    for (int i = 0; i < BUTTON_EXCEPT_AXIS_MAX; i++)
    {
        int mask = 0x00000000 | 0x00000001 << i;
        newState[i] = static_cast<BYTE>((newInfo.dwButtons & mask) >> i);
    }

    // �\���L�[
    newState[BUTTON_UP]     = (newInfo.dwYpos > THRESHOLD_MAX) ? (0x01) : (0x00);
    newState[BUTTON_DOWN]   = (newInfo.dwYpos < THRESHOLD_MIN) ? (0x01) : (0x00);
    newState[BUTTON_LEFT]   = (newInfo.dwXpos > THRESHOLD_MAX) ? (0x01) : (0x00);
    newState[BUTTON_RIGHT]  = (newInfo.dwXpos < THRESHOLD_MIN) ? (0x01) : (0x00);
    
// 
// �v���X�A�g���K�[�A���s�[�g
// 

    for (int i = 0; i < BUTTON_MAX; i++)
    {
        // �g���K�[�A�����[�X
        trigger[i] = (~press[i]) & (newState[i]);
        release[i] = (press[i])  & (~newState[i]);

        // ���s�[�g
        if (newState[i] & 0x01)
        {
            repeatCnt[i]--;
            if (repeatCnt[i] <= 0)
            {
                repeat[i] = newState[i];
                repeatCnt[i] = repeatTerm;
            }
            else
            {
                repeat[i] = ~newState[i];
            }
        }
        else
        {
            repeat[i] = newState[i];
            repeatCnt[i] = 0;
        }
    }

    // �v���X
    memcpy(press, newState, BUTTON_MAX);

}

/******************************* ���������܂� ********************************/
