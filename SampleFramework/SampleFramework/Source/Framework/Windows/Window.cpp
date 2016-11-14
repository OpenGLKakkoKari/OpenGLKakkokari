/*****************************************************************************/
/*!
@file   Window.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Window.h"
using namespace Windows;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/


Window::Window()
    : handle(0), instance(0), controller(NULL), winStyle(WS_OVERLAPPEDWINDOW),
    x(CW_USEDEFAULT), y(CW_USEDEFAULT),
    width(CW_USEDEFAULT), height(CW_USEDEFAULT),
    parentHandle(NULL), menuHandle(0)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Window::~Window()
{
    ::UnregisterClass(className, instance);
}

/******************************************************************************
@brief  ウインドウ生成
@return HWND        ウインドウハンドル
******************************************************************************/

HWND Window::Create(HINSTANCE hInst, const char* name, HWND hParent, Controller* ctrl)
{
    instance = hInst;
    parentHandle = hParent;
    controller = ctrl;

    strcpy_s(this->title, MAX_STRING - 1, name);
    strcpy_s(this->className, MAX_STRING - 1, name);

    winClass.cbSize = sizeof(WNDCLASSEX);
    winClass.style = 0;
    winClass.lpfnWndProc = Procedure;
    winClass.cbClsExtra = 0;
    winClass.cbWndExtra = 0;
    winClass.hInstance = instance;
    winClass.hCursor = LoadCursor(0, IDC_ARROW);
    winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    winClass.lpszClassName = className;

    if (!::RegisterClassEx(&winClass)) return 0;
    RECT rect = {0, 0, width, height};
    if (winClass.lpszMenuName != NULL)
        AdjustWindowRect(&rect, winStyle, true);
    else
        AdjustWindowRect(&rect, winStyle, false);

    handle = ::CreateWindowEx(
        NULL,                   // ウインドウスタイル
        className,              // クラス名
        title,                  // タイトル
        winStyle,               // ウインドウスタイル
        x,                      // 位置(X)
        y,                      // 位置(Y)
        rect.right - rect.left,                  // 横幅
        rect.bottom - rect.top,                 // 縦幅
        parentHandle,           // 親ウインドウハンドル
        NULL,             // メニューハンドル
        instance,               // インスタンス
        (LPVOID)controller);    // ユーザー定義データ

    return handle;
}

/******************************************************************************
@brief  ウインドウの表示
@param  cmdShow     ウインドウ表示のフラグ
******************************************************************************/

void Window::Show(int cmdShow)
{
    ::ShowWindow(handle, cmdShow);
    ::UpdateWindow(handle);
}

/******************************************************************************
@brief  ウインドウプロシージャ
@param  hWnd        ウインドウハンドル
@param  uMsg        メッセージ
@param  wParam      メッセージの付加情報
@param  lParam      メッセージの付加情報
@return LRESULT     メッセージ
******************************************************************************/

LRESULT CALLBACK Window::Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT returnValue = 0;

    // ウインドウハンドルに関連付けられたコントローラを取得
    static Controller *ctrl;
    ctrl = (Controller*)::GetWindowLongPtr(hWnd, GWL_USERDATA);

    if (msg == WM_NCCREATE)
    {
        // 非クライアント領域のパーツが作られる前にWM_NCCREATEが呼ばれる。
        // このメッセージとともにCREATESTRUCT の lpCreateParams には
        // CreateWindowEX() の lpPraramが入っている。
        // まず、ウインドウが開始する際に、コントローラーを取得する。
        ctrl = (Controller*)(((CREATESTRUCT*)lParam)->lpCreateParams);
        ctrl->setHandle(hWnd);

        // GWL_USERDATAにコントローラーを設定する。
        // そうすることによって、他のメッセージはコントローラ経由で
        // メッセージを処理することができる。
        ::SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)ctrl);

        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    // GWL_USERDATAは最初0に初期化され、有効なポインタは
    // WM_NCCREATE時に保存されるためNULLチェックを行う
    if (!ctrl)
        return ::DefWindowProc(hWnd, msg, wParam, lParam);
    
    // コントローラーにメッセージを処理させる
    switch (msg)
    {
    case WM_CREATE:
        returnValue = ctrl->create();
        break;

    case WM_SIZE:
        returnValue = ctrl->size(LOWORD(lParam), HIWORD(lParam), (int)wParam);
        break;

    case WM_ENABLE:
    {
        bool flag;
        if (wParam) flag = true;
        else flag = false;
        returnValue = ctrl->enable(flag);
        break;
    }

    case WM_PAINT:
        ctrl->paint();
        returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
        break;

    case WM_COMMAND:
        returnValue = ctrl->command(LOWORD(wParam), HIWORD(wParam), lParam);
        break;

    case WM_MOUSEMOVE:
        returnValue = ctrl->mouseMove(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_CLOSE:
        returnValue = ctrl->close();
        break;

    case WM_DESTROY:
        returnValue = ctrl->destroy();
        break;

    case WM_SYSCOMMAND:
        //returnValue = ctrl->sysCommand(wParam, lParam);
        returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
        break;

    case WM_CHAR:
        //returnValue = ctrl->char(wParam, lParam);
        break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        returnValue = ctrl->keyDown((int)wParam, lParam);
        break;

    case WM_KEYUP:
    case WM_SYSKEYUP:
        returnValue = ctrl->keyUp((int)wParam, lParam);
        break;

    case WM_LBUTTONDOWN:
        returnValue = ctrl->lButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_LBUTTONUP:
        returnValue = ctrl->lButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_RBUTTONDOWN:
        returnValue = ctrl->rButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_RBUTTONUP:
        returnValue = ctrl->rButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MBUTTONDOWN:
        returnValue = ctrl->mButtonDown(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MBUTTONUP:
        returnValue = ctrl->mButtonUp(wParam, LOWORD(lParam), HIWORD(lParam));
        break;

    case WM_MOUSEWHEEL:
        break;

    case WM_HSCROLL:
        returnValue = ctrl->hScroll(wParam, lParam);
        break;

    case WM_VSCROLL:
        returnValue = ctrl->vScroll(wParam, lParam);
        break;

    case WM_TIMER:
        returnValue = ctrl->timer(LOWORD(wParam), HIWORD(wParam));
        break;

    case WM_NOTIFY:
        returnValue = ctrl->notify((int)wParam, lParam);
        break;

    case WM_CONTEXTMENU:
        returnValue = ctrl->contextMenu((HWND)wParam, LOWORD(lParam), HIWORD(lParam));

    default:
        returnValue = ::DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return returnValue;
}

/******************************************************************************
@brief  アイコンの読み込み
@param  id          アイコンID
@return HICON       アイコンハンドル
******************************************************************************/

HICON Window::loadIcon(int id)
{
    return (HICON)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE);
}

/******************************************************************************
@brief  カーソルの読み込み
@param  id          カーソルID
@return HICON       カーソルハンドル
******************************************************************************/

HCURSOR Window::loadCursor(int id)
{
    return (HCURSOR)::LoadImage(instance, MAKEINTRESOURCE(id), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE);
}

/******************************** 実装ここまで *******************************/
