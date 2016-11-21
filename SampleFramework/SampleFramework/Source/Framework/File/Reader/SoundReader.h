#pragma once
/******************************************************************************
/*!
@file   SoundReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  マクロ定義
******************************************************************************/


#pragma warning(disable : 4996)


/*  インクルード
******************************************************************************/


#include "Reader.h"
#include "../../Sound/Sound.h"

/**
 * OpenAL
 */
#include "../../../../lib/OpenAL/al.h"
#include "../../../../lib/OpenAL/alc.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class SoundReader : public Reader
        {
        public:
            /// Riff Header
            typedef struct
            {
                unsigned int riff;
                int size;
                unsigned int type;
            }RiffHeader;

            /// fmt chunk
            typedef struct
            {
                unsigned int   id;
                int            size;
                short          format;
                unsigned short channels;
                unsigned int   samplerate;
                unsigned int   bytepersec;
                unsigned short blockalign;
                unsigned short bitswidth;
            }FormatChunk;

            /// Data chunk
            typedef struct
            {
                unsigned int   id;
                int            size;
                unsigned char *pData;
            }DataChunk;

            static Sound Load(const char *FileName, bool reverse = false);

        private:
            static Sound LoadWAV(const char *FileName);
        };
    }
}


/****************************** ヘッダここまで *******************************/