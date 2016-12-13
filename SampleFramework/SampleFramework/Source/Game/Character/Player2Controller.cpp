/*****************************************************************************/
/*!
@file   Player2Controller.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Player2Controller.h"
#include "../../Framework/Manager.h"


using namespace Framework;
using namespace Framework::Input;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Player2Controller::Player2Controller()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Player2Controller::~Player2Controller()
{
}

/******************************************************************************
@brief  ������������ǂ���
******************************************************************************/

bool Player2Controller::IsUp()
{
    return (Manager::GetKeyboard()->Press(VK_UP) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_UP)
        );
}

/******************************************************************************
@brief  �������������ǂ���
******************************************************************************/

bool Player2Controller::IsDown()
{
	return (Manager::GetKeyboard()->Press(VK_DOWN) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_DOWN)
        );
}

/******************************************************************************
@brief  �������������ǂ���
******************************************************************************/

bool Player2Controller::IsLeft()
{
    return (Manager::GetKeyboard()->Press(VK_LEFT) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_LEFT)
        );
}

/******************************************************************************
@brief  �E�����������ǂ���
******************************************************************************/

bool Player2Controller::IsRight()
{
    return (Manager::GetKeyboard()->Press(VK_RIGHT) ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �W�����v�L�[�����������ǂ���
******************************************************************************/

bool Player2Controller::IsJump()
{
    return (Manager::GetKeyboard()->Trigger(VK_SPACE) ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �i���L�[�����������ǂ���
******************************************************************************/

bool Player2Controller::IsMelee()
{
    return (Manager::GetKeyboard()->Trigger('V') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �ˌ��L�[�����������ǂ���
******************************************************************************/

bool Player2Controller::IsShoot()
{
    return (Manager::GetKeyboard()->Trigger('B') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �X�y�V�����L�[�����������ǂ���
******************************************************************************/

bool Player2Controller::IsSpecial()
{
    return (Manager::GetKeyboard()->Trigger('N') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �U���L�[�����������ǂ���
******************************************************************************/

bool Player2Controller::IsAttack()
{
    return (Manager::GetKeyboard()->Trigger('K') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************** ���������܂� *******************************/
