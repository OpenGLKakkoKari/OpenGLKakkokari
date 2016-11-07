#pragma once
/******************************************************************************
/*!
@file   Viewport.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Viewport.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Viewport
    {
    public:
        Viewport() : X(0), Y(0), width(0), height(0), minZ(0.0f), maxZ(0) {}

        int   X;
        int   Y;
        int   width;
        int   height;
        float minZ;
        float maxZ;

        static Viewport* Set(Viewport *pOut, int X, int Y, int Width, int Height);
    };
}


/******************************* ヘッダここまで ******************************/
