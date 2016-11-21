#pragma once
/******************************************************************************
/*!
@file   CharacterStateNeutral.h
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
    class CharacterStateNeutral : public CharacterState
    {
    public:
        CharacterStateNeutral(Character* pOwner);
        virtual ~CharacterStateNeutral();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* �w�b�_�����܂� ******************************/