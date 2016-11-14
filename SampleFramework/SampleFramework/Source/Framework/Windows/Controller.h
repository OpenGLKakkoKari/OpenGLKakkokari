#pragma once
/*****************************************************************************/
/*!
@file   Controller.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>


/*  クラス定義
******************************************************************************/


namespace Windows
{
    class Controller
    {
    public:
        Controller(){}
        virtual ~Controller(){}

        void setHandle(HWND handle);

        virtual int close();                                    // for WM_CLOSE
        virtual int command(int id, int cmd, LPARAM msg);       // for WM_COMMAND
        virtual int contextMenu(HWND handle, int x, int y);     // for WM_CONTEXTMENU
        virtual int create();                                   // for WM_CREATE
        virtual int destroy();                                  // for WM_DESTROY
        virtual int enable(bool flag);                          // for WM_ENABLE
        virtual int eraseBkgnd(HDC hdc);                        // for WM_ERASEBKGND
        virtual int hScroll(WPARAM wParam, LPARAM lParam);      // for WM_HSCROLL
        virtual int keyDown(int key, LPARAM lParam);            // for WM_KEYDOWN
        virtual int keyUp(int key, LPARAM lParam);              // for WM_KEYUP
        virtual int lButtonDown(WPARAM state, int x, int y);    // for WM_LBUTTONDOWN
        virtual int lButtonUp(WPARAM state, int x, int y);      // for WM_LBUTTONUP
        virtual int mButtonDown(WPARAM state, int x, int y);    // for WM_MBUTTONDOWN
        virtual int mButtonUp(WPARAM state, int x, int y);      // for WM_MBUTTONUP
        virtual int mouseMove(WPARAM state, int x, int y);      // for WM_MOUSEMOVE
        virtual int notify(int id, LPARAM lParam);              // for WM_NOTIFY
        virtual int paint();                                    // for WM_PAINT
        virtual int rButtonDown(WPARAM wParam, int x, int y);   // for WM_RBUTTONDOWN
        virtual int rButtonUp(WPARAM wParam, int x, int y);     // for WM_RBUTTONUP
        virtual int size(int w, int h, WPARAM wParam);          // for WM_SIZE
        virtual int timer(WPARAM id, LPARAM lParam);            // for WM_TIMER
        virtual int vScroll(WPARAM wParam, LPARAM lParam);      // for WM_VSCROLL


    protected:
        HWND handle;
    };

    inline void Controller::setHandle(HWND hwnd) { handle = hwnd; }
    inline int Controller::close() { ::DestroyWindow(handle); return 0; }
    inline int Controller::command(int id, int cmd, LPARAM msg) { return 0; }
    inline int Controller::contextMenu(HWND handle, int x, int y) { return 0; }
    inline int Controller::create() { return 0; }
    inline int Controller::destroy() { ::PostQuitMessage(0); return 0; }
    inline int Controller::enable(bool flag) { return 0; }
    inline int Controller::eraseBkgnd(HDC hdc) { return 0; }
    inline int Controller::hScroll(WPARAM wParam, LPARAM lParam) { return 0; }
    inline int Controller::keyDown(int key, LPARAM lParam) { return 0; }
    inline int Controller::keyUp(int key, LPARAM lParam) { return 0; }
    inline int Controller::lButtonDown(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::lButtonUp(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::mButtonDown(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::mButtonUp(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::mouseMove(WPARAM keyState, int x, int y) { return 0; }
    inline int Controller::notify(int id, LPARAM lParam) { return 0; }
    inline int Controller::paint() { return 0; }
    inline int Controller::rButtonDown(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::rButtonUp(WPARAM wParam, int x, int y) { return 0; }
    inline int Controller::size(int w, int h, WPARAM type) { return 0; }
    inline int Controller::timer(WPARAM id, LPARAM lParam) { return 0; }
    inline int Controller::vScroll(WPARAM wParam, LPARAM lParam) { return 0; }

}


/******************************* ヘッダここまで ******************************/

