#pragma once
/******************************************************************************
/*!
@file   CharacterStateNeutral.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\..\Framework\State.h"


/*  クラス定義
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


/******************************* ヘッダここまで ******************************/
