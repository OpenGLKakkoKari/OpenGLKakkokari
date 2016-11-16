#pragma once
/******************************************************************************
/*!
@file   CharacterStateManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "CharacterState.h"
#include "../../Framework/StateManager.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class CharacterStateManager : public Framework::StateManager
    {
    public:
        CharacterStateManager(){}
        virtual ~CharacterStateManager(){}

        //bool IsSameState(CharacterState::StateName name){ return reinterpret_cast<CharacterState*>(nowState)->IsSameState(name); }
    };
}


/******************************* ヘッダここまで ******************************/
