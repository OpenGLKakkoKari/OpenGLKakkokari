/*****************************************************************************/
/*!
@file   Player1Controller.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Player1Controller.h"
#include "../../Framework/Manager.h"


using namespace Framework;
using namespace Framework::Input;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Player1Controller::Player1Controller()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Player1Controller::~Player1Controller()
{
}

/******************************************************************************
@brief  ������������ǂ���
******************************************************************************/

bool Player1Controller::IsUp()
{
    return (Manager::GetKeyboard()->Press('W') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_UP)
        );
}

/******************************************************************************
@brief  �������������ǂ���
******************************************************************************/

bool Player1Controller::IsDown()
{
    return (Manager::GetKeyboard()->Press('S') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_DOWN)
        );
}

/******************************************************************************
@brief  �������������ǂ���
******************************************************************************/

bool Player1Controller::IsLeft()
{
    return (Manager::GetKeyboard()->Press('A') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_LEFT)
        );
}

/******************************************************************************
@brief  �E�����������ǂ���
******************************************************************************/

bool Player1Controller::IsRight()
{
    return (Manager::GetKeyboard()->Press('D') ||
        Manager::GetJoystick()->Press(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �W�����v�L�[�����������ǂ���
******************************************************************************/

bool Player1Controller::IsJump()
{
    return (Manager::GetKeyboard()->Trigger('J') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �i���L�[�����������ǂ���
******************************************************************************/

bool Player1Controller::IsMelee()
{
    return (Manager::GetKeyboard()->Trigger('V') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �ˌ��L�[�����������ǂ���
******************************************************************************/

bool Player1Controller::IsShoot()
{
    return (Manager::GetKeyboard()->Trigger('B') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �X�y�V�����L�[�����������ǂ���
******************************************************************************/

bool Player1Controller::IsSpecial()
{
    return (Manager::GetKeyboard()->Trigger('N') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************************************************************
@brief  �U���L�[�����������ǂ���
******************************************************************************/

bool Player1Controller::IsAttack()
{
    return (Manager::GetKeyboard()->Trigger('F') ||
        Manager::GetJoystick()->Trigger(Joystick::BUTTON_RIGHT)
        );
}

/******************************** ���������܂� *******************************/
