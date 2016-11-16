#pragma once
/******************************************************************************
/*!
@file   CharacterStateWalking.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterState.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class CharacterStateWalking : public CharacterState
    {
    public:
        CharacterStateWalking(Character* pOwner);
        virtual ~CharacterStateWalking();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* ヘッダここまで ******************************/
