#pragma once
/*****************************************************************************/
/*!
@file   Window.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>
#include "Controller.h"


/*  クラス定義
******************************************************************************/


namespace Windows
{
    class Window
    {

    public:
        Window();
        virtual ~Window();

        HWND Create(HINSTANCE hInst, const char* name, HWND hParent, Controller* ctrl);
        void Show(int cmdShow = SW_SHOWDEFAULT);
        HWND GetHandle()                        { return handle; }

        int GetWidth()                             { return width; }
        int GetHeight()                            { return height; }

        void SetClassStyle(UINT style)          { winClass.style = style; }
        void SetIcon(int id)                    { winClass.hIcon = loadIcon(id); }
        void SetIconSmall(int id)               { winClass.hIconSm = loadIcon(id); }
        void SetCursor(int id)                  { winClass.hCursor = loadCursor(id); }
        void SetBackground(int color)           { winClass.hbrBackground = (HBRUSH)GetStockObject(color); }
        void SetMenuName(LPCTSTR name)          { winClass.lpszMenuName = name; }

        void SetWindowStyle(DWORD style)        { winStyle = style; }
        void SetPosition(int x, int y)          { this->x = x; this->y = y; }
        void SetSize(int w, int h)              { width = w; height = h; }
        void SetParent(HWND handle)             { parentHandle = handle; }
        void SetMenu(HMENU handle)              { menuHandle = handle; }

        static LRESULT CALLBACK Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    protected:
        enum { MAX_STRING = 256 };

        void registerClass();
        HICON loadIcon(int id);
        HCURSOR loadCursor(int id);

        HWND        handle;
        WNDCLASSEX  winClass;
        DWORD       winStyle;
        char        title[MAX_STRING];
        char        className[MAX_STRING];
        int         x;
        int         y;
        int         width;
        int         height;
        HWND        parentHandle;
        HMENU       menuHandle;
        HINSTANCE   instance;
        Controller* controller;
    };
}


/******************************* ヘッダここまで ******************************/
