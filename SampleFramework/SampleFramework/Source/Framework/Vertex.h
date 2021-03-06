#pragma once
/******************************************************************************
/*!
@file   Vertex.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Math\Vector3.h"
#include "Math\Vector2.h"
#include "Color.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    struct Vertex
    {
        Vector3     pos;        // 位置情報
        Vector3     nor;        // 法線情報
        Color       col;        // 色情報
        Vector2     tex;        // テクスチャ座標
    };
}


/******************************* ヘッダここまで ******************************/
