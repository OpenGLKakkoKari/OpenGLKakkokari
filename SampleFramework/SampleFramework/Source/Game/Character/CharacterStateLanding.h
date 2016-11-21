#pragma once
/******************************************************************************
/*!
@file   CharacterStateLanding.h
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


/******************************* ヘッダここまで ******************************/
