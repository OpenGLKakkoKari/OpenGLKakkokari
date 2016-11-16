/******************************************************************************

@file   Joystick.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Joystick.h"

using namespace Framework::Input;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
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
@brief  デストラクタ
******************************************************************************/

Joystick::~Joystick()
{
}

/******************************************************************************
@brief  初期化処理
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
@brief  更新処理
******************************************************************************/

void Joystick::Update()
{
    JOYINFOEX newInfo;
    if (JOYERR_NOERROR != joyGetPosEx(0, &newInfo))
        return;

// 
// 現在のボタンの情報を取得
// 

    BYTE newState[BUTTON_MAX];

    // 十字キー以外
    for (int i = 0; i < BUTTON_EXCEPT_AXIS_MAX; i++)
    {
        int mask = 0x00000000 | 0x00000001 << i;
        newState[i] = static_cast<BYTE>((newInfo.dwButtons & mask) >> i);
    }

    // 十字キー
    newState[BUTTON_UP]     = (newInfo.dwYpos > THRESHOLD_MAX) ? (0x01) : (0x00);
    newState[BUTTON_DOWN]   = (newInfo.dwYpos < THRESHOLD_MIN) ? (0x01) : (0x00);
    newState[BUTTON_LEFT]   = (newInfo.dwXpos > THRESHOLD_MAX) ? (0x01) : (0x00);
    newState[BUTTON_RIGHT]  = (newInfo.dwXpos < THRESHOLD_MIN) ? (0x01) : (0x00);
    
// 
// プレス、トリガー、リピート
// 

    for (int i = 0; i < BUTTON_MAX; i++)
    {
        // トリガー、リリース
        trigger[i] = (~press[i]) & (newState[i]);
        release[i] = (press[i])  & (~newState[i]);

        // リピート
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

    // プレス
    memcpy(press, newState, BUTTON_MAX);

}

/******************************* 実装ここまで ********************************/
