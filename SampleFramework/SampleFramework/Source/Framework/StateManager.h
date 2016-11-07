/******************************************************************************
/*!
@file   StateManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "State.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class StateManager
    {
    public:
        StateManager();
        virtual ~StateManager();

        void Update();
        void SetState(State* newState);

    private:
        State*      nowState;
    };
}


/******************************* ヘッダここまで ******************************/
