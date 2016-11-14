#pragma once
/******************************************************************************
/*!
@file   CharacterStateShooting.h
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
    class CharacterStateShooting : public CharacterState
    {
    public:
        CharacterStateShooting(Character* pOwner);
        virtual ~CharacterStateShooting();

        virtual void Init();
        virtual void Uninit();
        virtual void Update();
    };
}


/******************************* ヘッダここまで ******************************/
