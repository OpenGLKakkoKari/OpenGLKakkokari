#pragma once
/******************************************************************************
/*!
@file   Player.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Character.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class Player : public Character
    {
    public:
        Player();
        ~Player();

        void Init(){}
        void Uninit(){}
        void Update();


    private:
        bool                      play;
        bool                      onGround;
        bool                      action;
    };
}


/******************************* ヘッダここまで ******************************/
