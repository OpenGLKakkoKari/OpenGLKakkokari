/*****************************************************************************/
/*!
@file   MainController.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "MainController.h"
#include "../Manager.h"
#include <math.h>

using namespace Windows;
using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  WM_CLOSE時の処理
@return int
******************************************************************************/

int MainController::close()
{
    ::EnumChildWindows(handle, (WNDENUMPROC)enumerateChildren, (LPARAM)WM_CLOSE);

    ::DestroyWindow(handle);
    return 0;
}

/******************************************************************************
@brief  小ウインドウ列挙
@param  childHandle
@param  lParam
@return bool
******************************************************************************/

bool CALLBACK MainController::enumerateChildren(HWND childHandle, LPARAM lParam)
{
    if (lParam == WM_CLOSE)
    {
        ::SendMessage(childHandle, WM_CLOSE, 0, 0);  // close child windows
    }

    return true;
}

/******************************************************************************
@brief  WM_DESTROY時の処理
@return int
******************************************************************************/

int MainController::destroy()
{
    PostQuitMessage(0);
    return 0;
}

/******************************************************************************
@brief  WM_COMMAND時の処理
@param  id
@param  command
@param  message
@return int
******************************************************************************/

int MainController::command(int id, int cmd, LPARAM message)
{
    return 0;
}

/******************************************************************************
@brief  WM_CREATE時の処理
@return int
******************************************************************************/

int MainController::create()
{
    return 0;
}

/******************************************************************************
@brief  WM_KEYDOWN時の処理
@param  key
@param  lParam
@return int
******************************************************************************/

int MainController::keyDown(int key, LPARAM lParam)
{

    switch (key) {
    case VK_ESCAPE:
        ::SendMessage(handle, WM_CLOSE, 0, 0);
        break;
    }

    return 0;
}

/******************************************************************************
@brief  WM_NOTIFY時の処理
@param  id
@param  lParam
@return int
******************************************************************************/

int MainController::notify(int id, LPARAM lParam)
{
    return 0;
}

/******************************************************************************
@brief  WM_CONTEXTMENU時の処理
@param  id
@param  lParam
@return int
******************************************************************************/

int MainController::contextMenu(HWND handle, int x, int y)
{
    return 0;
}

/******************************** 実装ここまで *******************************/
