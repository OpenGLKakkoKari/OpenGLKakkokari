#pragma once
/******************************************************************************
/*!
@file   CharacterStateLanding.h
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
    class CharacterStateLanding : public CharacterState
    {
    public:
        CharacterStateLanding(Character* pOwner);
        virtual ~CharacterStateLanding();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* �w�b�_�����܂� ******************************/
