#pragma once
/*****************************************************************************/
/*!
@file   MainController.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "../Windows/Controller.h"


/*  �N���X��`
******************************************************************************/


namespace Windows
{
    class MainController :public Controller
    {
    public:
        MainController(){}
        ~MainController(){}

        int command(int id, int cmd, LPARAM msg);
        int create();
        int close();
        int destroy();
        int keyDown(int key, LPARAM lParam);
        int notify(int id, LPARAM lParam);
        int contextMenu(HWND handle, int x, int y);


        static bool CALLBACK enumerateChildren(HWND childHandle, LPARAM lParam);
    };
}


/******************************* �w�b�_�����܂� ******************************/

