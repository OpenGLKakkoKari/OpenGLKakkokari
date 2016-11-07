#pragma once
/*****************************************************************************/
/*!
@file   GameWindow.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "../Windows/Window.h"


/*  �N���X��`
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


/******************************* �w�b�_�����܂� ******************************/

