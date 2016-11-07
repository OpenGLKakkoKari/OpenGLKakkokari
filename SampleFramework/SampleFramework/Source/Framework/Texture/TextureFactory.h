#pragma once
/******************************************************************************
/*!
@file   TextureFactory.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Texture.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class TextureFactory
    {

    public:
        TextureFactory() {}
        virtual ~TextureFactory() {}

        /// テクスチャ作成
        virtual Texture *Create(const Texture::Info *pInfo, void* pBuffer) = 0;
        virtual Texture *Load(const char *FileName) = 0;
    };
}


/****************************** ヘッダここまで *******************************/
