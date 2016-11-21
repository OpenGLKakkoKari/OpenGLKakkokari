#pragma once
/******************************************************************************
/*!
@file   SoundManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <Windows.h>
#include "SoundPlayer.h"

#include "../../../lib/OpenAL/al.h"
#include "../../../lib/OpenAL/alc.h"


/*  ライブラリリンク
******************************************************************************/


#ifdef _DEBUG
#pragma comment ( lib, "lib/OpenAL/OpenAL32.lib" )
#else
#pragma comment ( lib, "lib/OpenAL/OpenAL32.lib" )
#endif


/*  マクロ定義
******************************************************************************/


#define SOUNDPLAYER_NUM (8)


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Sound;
    class SoundManager
    {
    public:
        SoundManager();
        virtual ~SoundManager(){}

        void Init();
        void Uninit();

        void Load(const char* tag, const char* FileName);

        void Play(const char* tag, bool loop = false);
        void Pause(const char* tag);
        void Pause();
        void Stop(const char* tag);
        void Stop();

        SoundPlayer::State GetState(const char* tag);

    private:
        ALCdevice*      pDevice;
        ALCcontext*     pContext;

        SoundPlayer*    pSoundPlayer[SOUNDPLAYER_NUM];
    };
}


/******************************* ヘッダここまで ******************************/
