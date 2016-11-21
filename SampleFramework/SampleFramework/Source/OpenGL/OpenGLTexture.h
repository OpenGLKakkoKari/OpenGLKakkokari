#pragma once
/******************************************************************************
/*!
@file   OpenGLTexture.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "OpenGL.h"
#include "..\Framework\Texture\Texture.h"


/*  クラス定義
******************************************************************************/


namespace OpenGL
{
    class Texture : public Framework::Texture
    {
    public:
        Texture() : texture(0){}
        virtual ~Texture() {}

        /// リソース取得
        virtual const void *GetResource() { return pData; }

        /// テクスチャ作成
        void Create(const Info *pInfo, void *pBuffer)
        {
            this->info = *pInfo;
            unsigned char *pNewBuf = new unsigned char[pInfo->bufferSize];
            memcpy(pNewBuf, pBuffer, pInfo->bufferSize);
            this->pData = pNewBuf;

            // OpenGLのテクスチャ生成
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            // ミップマップ設定
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // 拡大時近傍
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // 縮小時近傍

            //　テクスチャの割り当て
            int internalFormat = (info.format == Texture::RGBA8888) ? (GL_RGBA) : (GL_RGBA);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,                  // mipmap
                internalFormat,
                info.width,         // width
                info.height,        // height
                0,                  // border
                internalFormat,
                GL_UNSIGNED_BYTE,
                GetResource()
                );
        }

        void Release()
        {
            if (IsReleased())
            {
                glDeleteTextures(1, &texture);
            }
            Framework::Texture::Release();
        }

        unsigned int texture;
    };
}


/******************************* ヘッダここまで ******************************/
