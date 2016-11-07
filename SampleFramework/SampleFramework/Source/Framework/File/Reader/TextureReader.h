#pragma once
/******************************************************************************
/*!
@file   TextureReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  マクロ定義
******************************************************************************/


#pragma warning(disable : 4996)


/*  インクルード
******************************************************************************/


#include "Reader.h"
#include "..\..\Texture\Texture.h"

/**
 * libpng
 */
#include "../../../../lib/libpng/zlib.h"
#include "../../../../lib/libpng/zconf.h"
#include "../../../../lib/libpng/png.h"
#include "../../../../lib/libpng/pngconf.h"
#include "../../../../lib/libpng/pnglibconf.h"

/**
 * libjpeg
 */
#define XMD_H 
#include "../../../../lib/libjpeg/jpeglib.h"
#include "../../../../lib/libjpeg/jconfig.h"
#include "../../../../lib/libjpeg/jerror.h"
#include "../../../../lib/libjpeg/jmorecfg.h"


/*  ライブラリリンク
******************************************************************************/


#ifdef _DEBUG
#pragma comment( lib, "lib/libpng/zlibDeb.lib" )
#pragma comment( lib, "lib/libpng/libpngDeb.lib" )
#pragma comment( lib, "lib/libjpeg/libjpegDeb.lib" )
#else
#pragma comment( lib, "lib/libpng/zlibRel.lib" )
#pragma comment( lib, "lib/libpng/libpngRel.lib" )
#pragma comment( lib, "lib/libjpeg/libjpegRel.lib" )
#endif


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class TextureReader : public Reader
        {
        public:

            /// TGA Header
            typedef struct
            {
                unsigned char   ID;
                unsigned char   colorMapType;
                unsigned char   imageType;
                unsigned short  colorMapIndex;
                //unsigned short  colorMapLength;
                unsigned char   colorMapSize;
                unsigned short  imageOriginX;
                unsigned short  imageOriginY;
                unsigned short  imageWidth;
                unsigned short  imageHeight;
                unsigned char   bbp;
                unsigned char   discripter;
            }TGAHeader;

            static Texture* Load(const char *FileName, bool reverseColor = false);
        private:
            static Texture* LoadBMP(const char *FileName);
            static Texture* LoadTGA(const char *FileName);
            static Texture* LoadPNG(const char *FileName);
            static Texture* LoadJPG(const char *FileName);

            static void ReverseDataUV(Texture* pTex);
            static void ReverseDataColor(Texture* pTex);

            static bool reverse;                // 反転フラグ
        };
    }
}


/****************************** ヘッダここまで *******************************/