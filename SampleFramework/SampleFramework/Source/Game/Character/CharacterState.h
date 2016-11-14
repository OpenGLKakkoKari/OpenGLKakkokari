#pragma once
/******************************************************************************
/*!
@file   CharacterState.h
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
    class Character;
    class CharacterState : public Framework::State
    {
    public:
        enum StateName
        {
            STATE_NEUTRAL,
            STATE_WALKING,
            STATE_JUMPING,
            STATE_LANDING,
            STATE_MELEE,
            STATE_SHOOTING,
            STATE_SKILL,
        };

        CharacterState(Character* pOwner){ pOwner_ = pOwner; }
        virtual ~CharacterState(){}

        virtual void Init(){}
        virtual void Uninit(){}
        virtual void Update(){}

        bool IsSameState(StateName name){ return name == name_; }

    protected:
        Character*  pOwner_;
        StateName   name_;
    };
}


/******************************* ヘッダここまで ******************************/
