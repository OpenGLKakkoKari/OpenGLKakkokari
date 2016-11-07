#pragma once
/******************************************************************************
/*!
@file   Fps.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <windows.h>


/*  ライブラリリンク
******************************************************************************/


#pragma comment( lib, "winmm.lib" )


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Fps
    {
    public:
        static bool IsNextFrame();
        static void Calc(unsigned int DrawIntervalms);
        static void SetFPS(unsigned int fps);

        static float GetAverageFPS();
        static float GetFPS();

    private:
        static unsigned int     FPS;                // 設定FPS
        static float            cntFPS;             // FPSカウンタ
        static float            avgFPS;             // 現在の平均FPS
        static float            avgFPSOld;          // 1フレーム前の平均FPS
        static unsigned int     cntCalcFPS;         // FPSを計算した累計回数
        static unsigned int     cntFrame;           // フレーム数
        static unsigned int     currentTime;        // 現在の時間
        static unsigned int     execLastTime;       // 最後に実行した時間
        static unsigned int     showLastTime;       // FPSを最後に表示した時間
    };
}


/****************************** ヘッダここまで *******************************/