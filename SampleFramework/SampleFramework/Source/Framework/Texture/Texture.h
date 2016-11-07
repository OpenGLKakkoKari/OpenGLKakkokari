#pragma once
/******************************************************************************
/*!
@file   Texture.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  クラス定義
******************************************************************************/


#include <stdio.h>
#include <string.h>


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class TextureFactory;
    class Texture
    {
    public:
        enum Format
        {
            RGBA8888,
            RGBX8888
        };
        struct Info
        {
            Format format;
            unsigned int width;
            unsigned int height;
            unsigned int bit;
            unsigned int pitch;
            unsigned int bufferSize;
            Info() : width(), height(), bit(), bufferSize(), pitch(), format(RGBA8888) {}
        };

        Texture();
        virtual ~Texture();

        static void RegisterFactory(TextureFactory *pTextureFactory) { pFactory = pTextureFactory; }

        static Texture* Create(const Info *pInfo, void *pBuffer);
        static Texture* Load(const char *FileName);

        virtual void Release();

        Info GetInfo() { return info; }

        void SetInfo
            (
            Texture::Format format,
            unsigned int    width,
            unsigned int    height,
            unsigned int    bit
            );


        void*                   pData;          // データへのポインタ
        Info                    info;           // テクスチャ情報

    protected:
        bool                    IsReleased()    // 開放される直前かどうか
        {
            return useNum - 1 <= 0;
        }

        static TextureFactory*  pFactory;
        int                     useNum;         // このテクスチャの参照数

    private:
        static Texture*         pFirst;         // テクスチャリストの最前列
        static Texture*         pLast;          // テクスチャリストの最後尾

        Texture*                pNext;
        Texture*                pPrev;
        char                    filePath[256];  // このテクスチャのファイルパス
    };
}


/****************************** ヘッダここまで *******************************/
