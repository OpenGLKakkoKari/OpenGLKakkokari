/*****************************************************************************/
/*!
@file   Effect.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Effect.h"
#include "../Manager.h"


using namespace Framework;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

Effect::Effect() : 
startTime(0), endTime(120), timer(0),
isPlaying(false), isLoop(false),
emitterNum(0)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Effect::~Effect()
{
    if (pEmitterList)
    {
        for (int i = 0; i < EMITTER_MAX; i++)
        {
            if (pEmitterList[i])
            {
                SAFE_DELETE(pEmitterList[i])
            }
        }
        delete[] pEmitterList;
    }
}

/******************************************************************************
@brief  更新処理
******************************************************************************/

void Effect::Update(void)
{
    // エフェクト更新処理
    if (isPlaying)
    {
        for (int i = 0; i < EMITTER_MAX; i++)
        {
            pEmitterList[i]->Update();
        }

        // タイマー更新
        timer++;
        if (isLoop)
        {
            if (timer > endTime)
            {
                timer = startTime;
                for (int i = 0; i < EMITTER_MAX; i++)
                {
                    pEmitterList[i]->Reset();
                }
            }
        }
        else
        {
            if (timer >= endTime)
            {
                timer = endTime - 1;
                isPlaying = false;
            }
        }
    }
}

/******************************** 実装ここまで *******************************/
