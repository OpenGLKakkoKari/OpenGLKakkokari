/******************************************************************************
/*!
@file   StateManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "State.h"


/*  �N���X��`
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


/******************************* �w�b�_�����܂� ******************************/
