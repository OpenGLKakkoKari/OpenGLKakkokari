#pragma once
/******************************************************************************
/*!
@file   CharacterStateJumping.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "CharacterState.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class CharacterStateJumping : public CharacterState
    {
    public:
        CharacterStateJumping(Character* pOwner);
        virtual ~CharacterStateJumping();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* �w�b�_�����܂� ******************************/
