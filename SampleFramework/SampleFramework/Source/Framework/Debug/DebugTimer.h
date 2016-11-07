#pragma once
/******************************************************************************
/*!
@file   DebugTimer.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class DebugTimer
    {
    public:
        DebugTimer();
        virtual ~DebugTimer();

        void Start();
        void End();

        float GetSecond();

    protected:
        LARGE_INTEGER start;
        LARGE_INTEGER end;
        LARGE_INTEGER freq;
    };
}


/****************************** ヘッダここまで *******************************/
