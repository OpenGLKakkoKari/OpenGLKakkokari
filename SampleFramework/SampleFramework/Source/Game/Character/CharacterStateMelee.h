#pragma once
/******************************************************************************
/*!
@file   CharacterStateMelee.h
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
    class CharacterStateMelee : public CharacterState
    {
    public:
        CharacterStateMelee(Character* pOwner);
        virtual ~CharacterStateMelee();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* �w�b�_�����܂� ******************************/
