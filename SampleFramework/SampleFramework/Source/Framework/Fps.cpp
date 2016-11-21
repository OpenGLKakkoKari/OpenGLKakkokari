/*****************************************************************************/
/*!
@file   Fps.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Fps.h"
using Framework::Fps;


/*  静的変数宣言
******************************************************************************/


unsigned int    Fps::FPS;               // 設定FPS
float           Fps::cntFPS;            // FPSカウンタ
float           Fps::avgFPS;            // 現在の平均FPS
float           Fps::avgFPSOld;         // 1フレーム前の平均FPS
unsigned int    Fps::cntCalcFPS;        // FPSを計算した累計回数
unsigned int    Fps::cntFrame;          // フレーム数
unsigned int    Fps::currentTime;       // 現在の時間
unsigned int    Fps::execLastTime;      // 最後に実行した時間
unsigned int    Fps::showLastTime;      // FPSを最後に表示した時間


/*  実装
******************************************************************************/

/******************************************************************************
@brief  次のフレームの処理時間に移行したかチェック
@retval true            可能
@retval false           不可能
******************************************************************************/

bool Fps::IsNextFrame()
{
    // 現在の時刻を取得
    currentTime = timeGetTime();

    // 1フレーム毎の処理
    if ((currentTime - execLastTime) >= (1000 / FPS))
    {
        execLastTime = currentTime;             // 最後の実行時刻を更新
        cntFrame++;                             // フレームカウントを進める
        return true;
    }
    else
    {
        return false;
    }
}

/******************************************************************************
@brief  平均を計算
@param  DrawIntervalms          描画間隔(ms)
******************************************************************************/

void Fps::Calc(unsigned int DrawIntervalms)
{
    // 時間間隔毎にFPSを算出
    if ((currentTime - showLastTime) >= DrawIntervalms)
    {
        // FPS算出
        cntFPS = (cntFrame * 1000.0f) / (currentTime - showLastTime);

        // FPSを表示した時刻を更新
        showLastTime = currentTime;
        // FPSを表示したので初期化
        cntFrame = 0;

        // 平均の算出
        if (cntCalcFPS == 0)
        {
            avgFPSOld = (float)FPS;
            avgFPS    = (float)FPS;
        }
        else
        {
            avgFPS = ((avgFPSOld * cntCalcFPS) + cntFPS) / (cntCalcFPS + 1);
            avgFPSOld = avgFPS;
        }
        cntCalcFPS++;
    }
}

/******************************************************************************
@brief  FPSを設定
@param  fps         設定するFPS
******************************************************************************/

void Fps::SetFPS(unsigned int fps)
{
    FPS = fps;
}

/******************************************************************************
@brief  平均FPSを取得
@return float       平均FPS
******************************************************************************/

float Fps::GetAverageFPS()
{
    return avgFPS;
}

/******************************************************************************
@brief  FPSを取得
@return int         FPS
******************************************************************************/

float Fps::GetFPS()
{
    return cntFPS;
}

/******************************* 関数ここまで ********************************/
