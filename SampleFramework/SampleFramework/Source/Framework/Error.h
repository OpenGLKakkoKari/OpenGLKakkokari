#pragma once
/******************************************************************************
/*!
@file   Error.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <Windows.h>


/*  �N���X��`
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


/******************************* �w�b�_�����܂� ******************************/
