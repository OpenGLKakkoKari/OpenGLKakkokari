#pragma once
/******************************************************************************
/*!
@file   Player.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "Character.h"


/*  �N���X��`
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


/******************************* �w�b�_�����܂� ******************************/