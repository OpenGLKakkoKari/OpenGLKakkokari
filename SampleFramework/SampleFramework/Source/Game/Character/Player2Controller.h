#pragma once
/******************************************************************************
/*!
@file   Player2Controller.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterController.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
}
namespace Game
{
    class Player2Controller : public CharacterController
    {
    public:
        Player2Controller();
        ~Player2Controller();

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


/******************************* ヘッダここまで ******************************/
