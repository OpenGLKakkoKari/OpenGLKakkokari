#pragma once
/******************************************************************************
/*!
@file   Error.h
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
    class Error
    {
    public:
        static void Init(HWND hWnd){ Error::hWnd = hWnd; }
        static void Uninit(){}
        static void Message(const char *ErrorMessage, ...);

    private:
        static HWND hWnd;
    };
}


/******************************* ヘッダここまで ******************************/
