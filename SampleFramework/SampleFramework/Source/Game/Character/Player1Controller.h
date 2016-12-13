#pragma once
/******************************************************************************
/*!
@file   Player1Controller.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterController.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
}
namespace Game
{
    class Player1Controller : public CharacterController
    {
    public:
        Player1Controller();
        ~Player1Controller();

        virtual bool IsUp();
        virtual bool IsDown();
        virtual bool IsLeft();
        virtual bool IsRight();
        virtual bool IsJump();
        virtual bool IsMelee();
        virtual bool IsShoot();
        virtual bool IsSpecial();
        virtual bool IsAttack();
    };
}


/******************************* �w�b�_�����܂� ******************************/
