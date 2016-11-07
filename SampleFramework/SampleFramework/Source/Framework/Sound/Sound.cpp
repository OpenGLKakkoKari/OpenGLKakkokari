/*****************************************************************************/
/*!
@file   Sound.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Sound.h"


using Framework::Sound;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  テクスチャ開放
******************************************************************************/

void Sound::Release()
{
    if (pData != NULL)
    {
        delete[] pData;
        pData = NULL;
    }
}

/******************************* 実装ここまで ********************************/
