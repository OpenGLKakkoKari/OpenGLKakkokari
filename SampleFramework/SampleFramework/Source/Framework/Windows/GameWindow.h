#pragma once
/*****************************************************************************/
/*!
@file   GameWindow.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "../Windows/Window.h"


/*  クラス定義
******************************************************************************/


namespace Windows
{
    class GameWindow : public Window
    {
    public:
        GameWindow(){}
        GameWindow(HINSTANCE hInst, const char* name, HWND hParent, Controller* ctrl){}
        virtual ~GameWindow(){}

        bool Exists();
        bool CanProcess();
        void FullScreen(bool isEnable) { screen = isEnable; }
        bool IsFullScreen(){ return screen; }

    protected:
        bool screen;
    };
}


/******************************* ヘッダここまで ******************************/

