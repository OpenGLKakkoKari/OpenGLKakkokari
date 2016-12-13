/*****************************************************************************/
/*!
@file   Player1Controller.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Player1Controller.h"
#include "../../Framework/Manager.h"


using namespace Framework;
using namespace Framework::Input;
using namespace Game;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Player1Controller::Player1Controller()
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Player1Controller::~Player1Controller()
{
}

/******************************************************************************
@brief  上を押したかどうか
******************************************************************************/

bool Player1Controller::IsUp()
{
    return (Manager::GetKeyboard()->Press('W') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_UP)
        );
}

/******************************************************************************
@brief  下を押したかどうか
******************************************************************************/

bool Player1Controller::IsDown()
{
    return (Manager::GetKeyboard()->Press('S') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_DOWN)
        );
}

/******************************************************************************
@brief  左を押したかどうか
******************************************************************************/

bool Player1Controller::IsLeft()
{
    return (Manager::GetKeyboard()->Press('A') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_LEFT)
        );
}

/******************************************************************************
@brief  右を押したかどうか
******************************************************************************/

bool Player1Controller::IsRight()
{
    return (Manager::GetKeyboard()->Press('D') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  ジャンプキーを押したかどうか
******************************************************************************/

bool Player1Controller::IsJump()
{
    return (Manager::GetKeyboard()->Trigger('J') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  格闘キーを押したかどうか
******************************************************************************/

bool Player1Controller::IsMelee()
{
    return (Manager::GetKeyboard()->Trigger('V') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  射撃キーを押したかどうか
******************************************************************************/

bool Player1Controller::IsShoot()
{
    return (Manager::GetKeyboard()->Trigger('B') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  スペシャルキーを押したかどうか
******************************************************************************/

bool Player1Controller::IsSpecial()
{
    return (Manager::GetKeyboard()->Trigger('N') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  攻撃キーを押したかどうか
******************************************************************************/

bool Player1Controller::IsAttack()
{
    return (Manager::GetKeyboard()->Trigger('F') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************** 実装ここまで *******************************/
