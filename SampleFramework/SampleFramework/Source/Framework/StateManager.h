#pragma once
/******************************************************************************
/*!
@file   StateManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  クラス定義
******************************************************************************/


namespace Framework
{
    class State;
    class StateManager
    {
    public:
        StateManager();
        virtual ~StateManager();

        virtual void Update();
        virtual void SetState(State* newState);

    protected:
        State*      nowState;
    };
}


/******************************* ヘッダここまで ******************************/
