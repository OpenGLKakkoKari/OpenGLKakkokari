/*****************************************************************************/
/*!
@file   MainController.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "MainController.h"
#include "../Manager.h"
#include <math.h>

using namespace Windows;
using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  WM_CLOSE���̏���
@return int
******************************************************************************/

int MainController::close()
{
    ::EnumChildWindows(handle, (WNDENUMPROC)enumerateChildren, (LPARAM)WM_CLOSE);

    ::DestroyWindow(handle);
    return 0;
}

/******************************************************************************
@brief  ���E�C���h�E��
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
@brief  WM_DESTROY���̏���
@return int
******************************************************************************/

int MainController::destroy()
{
    PostQuitMessage(0);
    return 0;
}

/******************************************************************************
@brief  WM_COMMAND���̏���
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
@brief  WM_CREATE���̏���
@return int
******************************************************************************/

int MainController::create()
{
    return 0;
}

/******************************************************************************
@brief  WM_KEYDOWN���̏���
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
@brief  WM_NOTIFY���̏���
@param  id
@param  lParam
@return int
******************************************************************************/

int MainController::notify(int id, LPARAM lParam)
{
    return 0;
}

/******************************************************************************
@brief  WM_CONTEXTMENU���̏���
@param  id
@param  lParam
@return int
******************************************************************************/

int MainController::contextMenu(HWND handle, int x, int y)
{
    return 0;
}

/******************************** ���������܂� *******************************/
