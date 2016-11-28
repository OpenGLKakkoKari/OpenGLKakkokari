#pragma once
/******************************************************************************
/*!
@file   Mouse.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>
#include "../Math/Vector2.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace Input
    {
        class Mouse
        {
        public:
            Mouse(HWND hWnd);
            virtual ~Mouse();

            void Update();
            Vector2 GetCursorPosition(){ return cursorPos_; }

        private:
            Vector2     cursorPos_;
            HWND        hWnd_;
        };
    }
}


/****************************** ヘッダここまで *******************************/
