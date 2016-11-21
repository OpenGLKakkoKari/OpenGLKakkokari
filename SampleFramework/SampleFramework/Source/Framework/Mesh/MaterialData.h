#pragma once
/******************************************************************************
/*!
@file   MaterialData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Color.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    struct MaterialData
    {

        ColorValue ambient;
        ColorValue diffuse;
        ColorValue specular;
        ColorValue emissive;
        float power;

        char fileName[256];
    };
}


/****************************** ヘッダここまで *******************************/
