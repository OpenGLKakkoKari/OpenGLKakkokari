#pragma once
/******************************************************************************
/*!
@file   Sound.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <windows.h>


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Sound
    {
    public:
        Sound();
        virtual ~Sound();

        enum SoundFormat
        {
            SF_MONO8,
            SF_MONO16,
            SF_STEREO8,
            SF_STEREO16
        };

        void Release();


        int             format;
        int             freq;
        int             size;
        unsigned char*  pData;
        char            FileName[MAX_PATH];
    };
}


/******************************* ヘッダここまで ******************************/
