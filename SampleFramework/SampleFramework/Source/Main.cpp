/*****************************************************************************/
/*!
@file    Main.cpp
@author  Yuki Kogawara
@copy    Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Main.h"
#include "Framework\Manager.h"
#include <crtdbg.h>


using Framework::Manager;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  メイン関数
@param  hInstance       インスタンスハンドル
@param  hPrevInstance   過去のWindows用
@param  lpCmdLine       コマンドラインから受け取った引数へのポインタ
@param  nCmdShow        アプリケーションの初期ウィンドウ表示方法を設定
@retval 0               正常終了
@retval それ以外        異常終了
******************************************************************************/

int WINAPI WinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance,
     LPSTR lpCmdLine, int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
/**
 * 初期化
 */

    Manager::Init(hInstance);


/**
 * メインループ
 */

    Manager::Loop();

    
/**
 * 終了処理
 */

    Manager::Uninit();
    
    return 0;
}

/******************************* 実装ここまで ********************************/
