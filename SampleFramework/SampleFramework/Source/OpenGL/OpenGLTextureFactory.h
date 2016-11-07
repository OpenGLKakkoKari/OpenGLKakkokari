#pragma once
/******************************************************************************
/*!
@file   OpenGLTextureFactory.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "OpenGLTexture.h"
#include "..\Framework\Texture\TextureFactory.h"
#include "..\Framework\File\Reader\TextureReader.h"


/*  クラス定義
******************************************************************************/


namespace OpenGL
{
    class TextureFactory : public Framework::TextureFactory
    {
    public:
        TextureFactory() {}
        virtual ~TextureFactory() {}

        /// テクスチャ作成
        virtual Framework::Texture *Create(const Framework::Texture::Info *pInfo, void* pBuffer)
        {
            Texture *pNewTex = new Texture;
            pNewTex->Create(pInfo, pBuffer);
            return pNewTex;
        }

        /// テクスチャ読み込み
        virtual Framework::Texture *Load(const char *FileName)
        {
            OpenGL::Texture *pNewTex = new OpenGL::Texture;
            Framework::Texture* pTex = Framework::File::TextureReader::Load(FileName);
            pNewTex->Create(&pTex->info, pTex->pData);
            pTex->Release();
            pTex = NULL;
            return pNewTex;
        }
    };
}


/****************************** ヘッダここまで *******************************/
