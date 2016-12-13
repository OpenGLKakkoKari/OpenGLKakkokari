/*****************************************************************************/
/*!
@file   Player2Controller.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Player2Controller.h"
#include "../../Framework/Manager.h"


using namespace Framework;
using namespace Framework::Input;
using namespace Game;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Player2Controller::Player2Controller()
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Player2Controller::~Player2Controller()
{
}

/******************************************************************************
@brief  上を押したかどうか
******************************************************************************/

bool Player2Controller::IsUp()
{
    return (Manager::GetKeyboard()->Press(VK_UP) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_UP)
        );
}

/******************************************************************************
@brief  下を押したかどうか
******************************************************************************/

bool Player2Controller::IsDown()
{
	return (Manager::GetKeyboard()->Press(VK_DOWN) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_DOWN)
        );
}

/******************************************************************************
@brief  左を押したかどうか
******************************************************************************/

bool Player2Controller::IsLeft()
{
    return (Manager::GetKeyboard()->Press(VK_LEFT) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_LEFT)
        );
}

/******************************************************************************
@brief  右を押したかどうか
******************************************************************************/

bool Player2Controller::IsRight()
{
    return (Manager::GetKeyboard()->Press(VK_RIGHT) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  ジャンプキーを押したかどうか
******************************************************************************/

bool Player2Controller::IsJump()
{
    return (Manager::GetKeyboard()->Trigger(VK_SPACE) ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  格闘キーを押したかどうか
******************************************************************************/

bool Player2Controller::IsMelee()
{
    return (Manager::GetKeyboard()->Trigger('V') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  射撃キーを押したかどうか
******************************************************************************/

bool Player2Controller::IsShoot()
{
    return (Manager::GetKeyboard()->Trigger('B') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  スペシャルキーを押したかどうか
******************************************************************************/

bool Player2Controller::IsSpecial()
{
    return (Manager::GetKeyboard()->Trigger('N') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  攻撃キーを押したかどうか
******************************************************************************/

bool Player2Controller::IsAttack()
{
    return (Manager::GetKeyboard()->Trigger('K') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************** 実装ここまで *******************************/
