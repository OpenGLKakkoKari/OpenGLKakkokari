#pragma once
/******************************************************************************
/*!
@file   CharacterController.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  クラス定義
******************************************************************************/


namespace Framework
{
}
namespace Game
{
    class CharacterController
    {
    public:
        CharacterController(){}
        ~CharacterController(){}

        virtual bool IsUp()         { return false; }
        virtual bool IsDown()       { return false; }
        virtual bool IsLeft()       { return false; }
        virtual bool IsRight()      { return false; }
        virtual bool IsJump()       { return false; }
        virtual bool IsMelee()      { return false; }
        virtual bool IsShoot()      { return false; }
        virtual bool IsSpecial()    { return false; }
    };
}


/******************************* ヘッダここまで ******************************/
