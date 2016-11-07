#pragma once
/******************************************************************************
/*!
@file   CharacterStateNeutral.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\..\Framework\State.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class CharacterStateNeutral : public Framework::State
    {
    public:
        CharacterStateNeutral();
        virtual ~CharacterStateNeutral();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* �w�b�_�����܂� ******************************/
