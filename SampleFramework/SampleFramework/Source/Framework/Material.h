#pragma once
/******************************************************************************
/*!
@file   Material.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Color.h"
#include "Texture\Texture.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Material
    {
    public:

        ColorValue ambient;
        ColorValue diffuse;
        ColorValue specular;
        ColorValue emissive;
        float power;

        Texture *pTexture;
    };
}


/****************************** ヘッダここまで *******************************/
